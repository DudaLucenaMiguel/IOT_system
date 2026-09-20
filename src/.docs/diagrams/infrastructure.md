# Arquitetura de Infraestrutura - Flux

O diagrama abaixo ilustra a macro-arquitetura do ecossistema Flux, demonstrando a separação de responsabilidades através do padrão de microsserviços e a comunicação orientada a eventos.

```mermaid
graph TD
    %% Estilos
    classDef edge fill:#f9f9f9,stroke:#333,stroke-width:2px,color:#000;
    classDef frontend fill:#d4edda,stroke:#28a745,stroke-width:2px,color:#000;
    classDef backend fill:#cce5ff,stroke:#007bff,stroke-width:2px,color:#000;
    classDef data fill:#fff3cd,stroke:#ffc107,stroke-width:2px,color:#000;
    classDef ai fill:#f8d7da,stroke:#dc3545,stroke-width:2px,color:#000;

    subgraph "1. Camada Edge (IoT)"
        W[Flux Wearable<br/>ESP32 + MPU-6050]:::edge
    end

    subgraph "2. Camada de Apresentação"
        APP[App Mobile do Atleta<br/>Flutter]:::frontend
        DASH[Dashboard Web Executivo<br/>Vue.js]:::frontend
    end

    subgraph "3. Camada BFF (Backend For Frontend)"
        NODE[Servidor Executivo<br/>Node.js]:::backend
        NODEDB[(Banco Executivo<br/>Métricas Agregadas)]:::data
    end

    subgraph "4. Camada Core"
        PHP[Core Engine API<br/>PHP Laravel]:::backend
    end

    subgraph "5. Camada de Inteligência"
        PY[Microsserviço de IA<br/>Python FastAPI]:::ai
    end

    subgraph "6. Camada de Dados e Filas"
        PG[(PostgreSQL<br/>Dados Estruturados)]:::data
        MONGO[(MongoDB<br/>Logs e Telemetria temporária)]:::data
        REDIS[(Redis Message Broker<br/>Eventos e Filas)]:::data
    end

    %% Fluxos de Comunicação
    W -- "Conexão BLE/Wi-Fi" --> APP
    
    APP -- "Sincronização de Telemetria" --> MONGO
    APP -- "Requisições REST" --> PHP
    
    DASH -- "Requisições HTTP" --> NODE
    NODE -- "Leitura de KPI Rápida" --> NODEDB
    
    PHP -- "Publica Eventos (Pub/Sub) / Dispara Jobs" --> REDIS
    REDIS -- "Ouve Eventos e Salva Métricas" --> NODE
    REDIS -- "Puxa Tarefas Assíncronas" --> PY
    PY -- "Retorno de Inferência REST" --> PHP
    
    PHP -- "Persistência/Leitura" --> PG
    PHP -- "Agregação de Dados" --> MONGO
```

## Descrição do Fluxo Atualizado (Orientado a Eventos)
1. O **Flux Wearable** transmite dados de movimento para o **App Mobile**.
2. O App Mobile envia as avalanches de telemetria direto para o **MongoDB** e avisa o **Core PHP** do início/fim do treino.
3. O **Core PHP** usa o **Redis** para colocar a análise dos movimentos em uma fila assíncrona.
4. O **Microsserviço de IA (Python)** puxa a tarefa da fila, classifica os golpes e devolve para o PHP.
5. O PHP consolida o treino no banco relacional final (**PostgreSQL**).
6. Após salvar no PostgreSQL, o PHP "grita" um evento de novo treino no **Redis (Pub/Sub)**.
7. O **Servidor Executivo (Node.js)** escuta o Redis passivamente. Ao receber o aviso, ele salva uma métrica resumida e anônima (ex: +1 treino realizado) no seu próprio **Banco Executivo**.
8. Os diretores acessam o **Dashboard (Vue.js)** que consome apenas o Banco Executivo do Node.js, garantindo velocidade instantânea (OLAP) e proteção de que, se o PHP cair, o painel de diretoria segue intacto.
