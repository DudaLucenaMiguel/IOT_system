# Contexto do Repositório: Smart Tennis Arena

Este documento (`AGENTS.md`) serve como guia de contexto para agentes de IA e desenvolvedores que atuarão no repositório do Projeto Interdisciplinar "Smart Tennis Arena" (6º Semestre de Ciência da Computação - 2026).

## Objetivo do Projeto
O projeto **Smart Tennis Arena** visa desenvolver uma solução integrada de IoT e Robótica para criação e execução de treinos gamificados de tênis. O ecossistema completo é composto por:
- **Aplicativo Mobile**: para seleção, configuração, execução e acompanhamento das sessões de treino.
- **Site/Dashboard Web**: para criação, gestão, publicação e análise dos treinos.
- **API**: para integração de dados, consumo de treinos e envio de resultados para a plataforma mãe.
- **Protótipo IoT/Robótico**: integrado com sensores e atuadores para produzir eventos, controlar máquinas lançadoras de bolas (ou simuladores) e dar feedback em tempo real.

## Estrutura de Diretórios e Regras

O repositório está organizado da seguinte forma:

### `documentos/`
Pasta destinada a comportar toda a documentação das **Entregas do Projeto Interdisciplinar (PI)**. 
- **Estrutura interna**: Deve possuir um diretório para cada entrega (ex: `Entrega 1`, `Entrega 2`, `Apresentação`). 
- **Subdiretórios de disciplinas**: Dentro da pasta de cada entrega, haverá um diretório específico para cada disciplina envolvida no semestre (ex: Inovação e Empreendedorismo, Redes de Computadores e Cibersegurança, Sistemas Embarcados e Robótica, Teoria da Computação e Linguagens Formais, PI: IoT e Robótica).

### `imagens/`
Pasta destinada a armazenar os **assets e imagens** que serão utilizados no repositório do GitHub (como ilustrações para o README, diagramas, fotos de protótipos, etc.).

### `src/`
Pasta principal do desenvolvimento. Aqui ficará todo o **código-fonte** da aplicação (Mobile, Web, API, IoT/Firmware) e também **documentos técnicos de desenvolvimento** do software (como arquitetura, PRD, logs de decisão, etc.).

### `README.md` (raiz)
Arquivo README principal do repositório. Ele já segue o **padrão definido pela própria faculdade** e servirá como a vitrine do projeto. Pequenos ajustes e atualizações serão feitos nele ao decorrer ou ao final do projeto para refletir o andamento e a conclusão da solução.

## Diretrizes Adicionais para Agentes
- Ao criar código, sempre utilize a pasta `src/`.
- Ao documentar artefatos para entregas acadêmicas, posicione-os na subpasta correta da disciplina dentro de `documentos/`.
- Não altere a estrutura base definida pelo `README.md` na raiz sem autorização, pois segue um template acadêmico.
- Entenda que a solução engloba regras complexas de gamificação, integração IoT segura e APIs estruturadas, portanto, mantenha a modularização no código dentro da pasta `src/`.
