# Product Requirements Document (PRD)
**Projeto / Empresa:** Flux - Wearable & AI Movement Detection (Plataforma Multiesporte)
**Data:** Agosto de 2026
**Status:** Rascunho / Em Definição

---

## 1. Visão Geral do Produto

O projeto consiste no desenvolvimento de um ecossistema focado na análise de movimento e desempenho esportivo através de dispositivos IoT. A visão final do produto da **Flux** é ser uma plataforma **agnóstica e multiesportiva**, capaz de integrar múltiplos wearables (podendo ser alocados em diferentes partes do corpo, criando um "esqueleto" de sensores) e carregar diferentes modelos de Inteligência Artificial dependendo do exercício selecionado pelo usuário (ex: Musculação, Vôlei, etc.).

### 1.1. Escopo do MVP (Minimum Viable Product)
Para alinhar-se aos requisitos acadêmicos da faculdade e à parceria estratégica com a **SmartTennis**, o MVP será estritamente focado no Tênis. 
Nesta primeira fase, o hardware consistirá em um único dispositivo **Flux Wearable (estilo relógio/bracelete de pulso)** e o modelo de IA será treinado exclusivamente para detectar e classificar golpes de tênis (ex: *forehand, backhand, saque, voleio*). 
No entanto, toda a engenharia de software (Banco de dados, APIs, App e Dashboard) deve ser arquitetada desde o início de forma genérica, tratando o Tênis apenas como o "Esporte 1" de um catálogo escalável.

## 2. Arquitetura do Sistema e Componentes

A solução será dividida em quatro pilares fundamentais de desenvolvimento:

### 2.1. Dispositivo IoT (Hardware de Prototipação)
O wearable captará os dados brutos de movimentação em tempo real.
- **Microcontrolador:** ESP32-C3 (Possui suporte nativo a Wi-Fi/Bluetooth, sendo ideal para baixo consumo de energia e comunicação sem fio).
- **Sensor de Movimento:** MPU-6050 (Acelerômetro e Giroscópio de 6 eixos, responsável por obter os vetores de força e rotação do braço do atleta).

### 2.2. Inteligência Artificial (Modelo de Classificação)
- **Função:** Receber os dados de série temporal (aceleração e rotação nos eixos X, Y e Z) e utilizar algoritmos de Machine Learning / Deep Learning para detectar e categorizar o movimento do jogador.
- **Treinamento:** Exigirá uma etapa prévia de coleta de dados (*dataset*) executando movimentos reais para treinar o modelo.

### 2.3. Front-end 1: App Mobile
- **Público-alvo:** Jogador (usuário final).
- **Funções Principais:** Pareamento via Bluetooth/Wi-Fi com o wearable, visualização rápida de estatísticas do treino, iniciar/encerrar sessões de treino, e feedback imediato de movimentos.

### 2.4. Front-end 2: Dashboard Web
- **Público-alvo:** Treinadores, Analistas ou visualização avançada pelo jogador.
- **Funções Principais:** Análise aprofundada de longo prazo, gráficos de desempenho, gestão de histórico de treinos e métricas de consistência dos golpes.

### 2.5. Back-end: Servidor
- **Funções Principais:** Recepção de dados sincronizados pelo aplicativo mobile (ou diretamente pelo ESP32 via Wi-Fi), armazenamento no banco de dados, servir a API para o App e para o Dashboard, e, possivelmente, executar a inferência de IA (caso o processamento não seja feito *Edge* no próprio wearable ou celular).

## 3. Pilha de Tecnologias (Tech Stack)

A arquitetura do sistema seguirá o padrão de **Microsserviços**, simulando o ecossistema maduro de uma grande corporação (ex: sistema legado principal consumindo IA moderna e fornecendo dados para plataformas secundárias).

- **IoT / Firmware:** C/C++ (Arduino IDE ou ESP-IDF) *[Sugerido]*
- **Core / Back-end Principal:** PHP (Laravel) - Atuará como o motor principal do negócio (Sistema Legado/Core). Responsável por receber dados vitais, gerenciar usuários, orquestrar a persistência no banco de dados e fornecer a API primária.
- **Microsserviço de IA:** Python (FastAPI/Flask) - API REST dedicada exclusivamente à inferência. O Laravel enviará os dados dos sensores para esta API, que processará os modelos de *Machine Learning* e devolverá a classificação dos golpes.
- **Microsserviço B2B (Dashboard):** Node.js - Um servidor independente focado no Front-end executivo. Ele consumirá os endpoints do Core em PHP para gerar KPIs e inteligência de negócios. 
- **Bancos de Dados & Cache:**
  - **Relacional:** SQLite (Dev) e PostgreSQL (Produção) no Core PHP.
  - **NoSQL:** MongoDB para eventos temporários de telemetria.
  - **Filas:** Redis para processamento de background e comunicação assíncrona entre os serviços.
- **App Mobile (Atleta):** Flutter (Dart) - Focado na experiência do usuário final, com o próprio painel de evolução do atleta embutido.
- **Dashboard Web (Executivos):** Vue.js (servido pelo Node.js) - Interface focada na visão administrativa da empresa Flux.

## 4. Personas e Atores do Sistema
- **Usuário (Atleta):** Utiliza o *Flux Wearable* e o App Mobile. Todo o seu acompanhamento de progresso, histórico de treinos e gamificação acontece internamente dentro do próprio aplicativo.
- **Executivos (Business/Administrativo):** Usuários do Dashboard Web (B2B). Acessam métricas agregadas da base de atletas, rentabilidade, uso da plataforma e engajamento. O acesso é segmentado através de um sistema **RBAC** rigoroso (Marketing, Financeiro, Comercial, etc.).
