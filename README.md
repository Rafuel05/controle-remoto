# Controle Remoto para Automação Residencial com PIC16F877A

Este é um projeto desenvolvido para a disciplina de Microcontroladores que implementa um controle remoto utilizando um microcontrolador PIC16F877A. O sistema permite controlar dois relés através de um controle remoto IR (Infravermelho), com feedback visual através de um display LCD.

## Sobre o Projeto

Este projeto foi desenvolvido em C (100% do código) e utiliza:
- Microcontrolador PIC16F877A
- Display LCD (comunicação I2C)
- Receptor IR (Infravermelho)
- 2 Relés para controle de cargas (como lâmpadas)

## Pré-requisitos

Para desenvolver e compilar este projeto, você precisará:

- CCS C Compiler (PIC-C) - Para compilar o código para o microcontrolador PIC
- Programador PIC (Hardware para gravar o microcontrolador)
- Git instalado (para obter o código fonte)

## Explicação do Código

O código implementa as seguintes funcionalidades:

### 1. Configurações Iniciais
```c
#include <16F877A.h>
#device ADC=16

#FUSES NOWDT                    //Desativa o Watch Dog Timer
#FUSES NOBROWNOUT              //Desativa o brownout reset
#FUSES NOLVP                   //Desativa a programação em baixa tensão
```

### 2. Definição de Pinos
```c
#define IR_PIN      PIN_B0      // Pino do receptor IR
#define RELE1_PIN   PIN_D0      // Pino do relé 1
#define RELE2_PIN   PIN_D1      // Pino do relé 2
```

### 3. Funcionamento
- O sistema permanece em loop aguardando sinais do controle remoto IR
- Quando um sinal é recebido, a função `read_ir_code()` decodifica o sinal
- Os códigos IR são comparados com valores predefinidos para:
  - Ligar/Desligar Lâmpada 1 (Relé 1)
  - Ligar/Desligar Lâmpada 2 (Relé 2)
  - Ligar/Desligar ambas as lâmpadas simultaneamente
- O display LCD mostra feedback das ações realizadas

### 4. Comunicação I2C
O projeto utiliza comunicação I2C para o display LCD, configurada com:
- Clock de 100kHz
- Pinos SDA (PIN_C4) e SCL (PIN_C3)

## Como obter o código

1. Clone o repositório:
```bash
git clone https://github.com/Rafuel05/controle-remoto.git
```

2. Entre no diretório do projeto:
```bash
cd controle-remoto
```

## Como compilar e executar

1. Abra o CCS C Compiler
2. Importe o projeto (`main.c`)
3. Configure o compilador para o PIC16F877A
4. Compile o projeto
5. Use um programador PIC para gravar o microcontrolador

## Hardware Necessário

- PIC16F877A
- Display LCD com módulo I2C
- Receptor IR (ex: TSOP1738)
- 2 Relés
- Cristal de 4MHz
- Componentes passivos (resistores, capacitores)
- Fonte de alimentação 5V

## Conexões

- RB0: Entrada do receptor IR
- RD0: Saída para Relé 1
- RD1: Saída para Relé 2
- RC3: SCL (I2C)
- RC4: SDA (I2C)
