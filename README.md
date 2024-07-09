# Simulação de Cenários - Estacionamento do Shopping Iguatemi de Fortaleza

## Descrição do Projeto

Este projeto simula o funcionamento do estacionamento do Shopping Iguatemi de Fortaleza. A simulação inclui a entrada e saída de carros, contagem de vagas, e indicação de vagas livres ou ocupadas.

## Funcionalidades

- **Simulação da cancela de entrada e saída do estacionamento:**
  - A cancela de entrada é controlada por um servo motor.
  - O sensor que libera a cancela é simulado por um push button.

- **Simulação de um sensor de vaga de estacionamento:**
  - Um sensor ultrassônico detecta a presença de um carro na vaga.
  - LEDs indicam se a vaga está livre (verde) ou ocupada (vermelho).

- **Simulação de um contador de carros:**
  - Um display de 7 segmentos mostra o número de carros no estacionamento.
  - O contador é incrementado quando um carro entra e decrementado quando um carro sai.
  - O valor do contador é limitado a um máximo de 9 carros.

## Requisitos

### Hardware:

- ESP32 com suporte para controle de servo motor, leitura analógica e digital.
- Sensores ultrassônicos e push buttons.
- LEDs e display de 7 segmentos.

## Visualização do Projeto

[Link para o Wokwi](https://wokwi.com/projects/362912147059311617)
