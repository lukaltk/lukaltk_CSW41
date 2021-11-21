# Sistemas Embarcados

- Código: CSW41
- Professor: Douglas Paulo Bertrand Renaux
- Email: douglasrenaux@professores.utfpr.edu.br

- Aluno: Luka Takeshi Kato
- Email: luka@alunos.utfpr.edu.br


# Lab4 - Comunicação Serial
#### Objetivo
Elaborar um projeto no IAR cuja funcionalidade é receber dados pela porta serial (UART) do processador da Tiva, processar estes dados e enviá-los pela mesma porta serial.
A comunicação será feito com um emulador de terminal (TeraTerm ou similar) executando no PC.
O processamento de dados consiste em converter os caracteres maiúsculos (A-Z) nos correspondentes minúsculos (a-z) sem alterar os demais bytes recebidos.
A taxa de comunicação deve ser de 115200 bps no formato 8N1.

# UART
O UART (Universal Asynchronous Receiver-Transmitter) como seu nome sugere, serve para realizar comunicação serial assíncrona em que o formato dos dados e as velocidades de transmissão são configuráveis.

O UART pega bytes de dados e transmite os bits individuais de forma sequencial. No destino, um segundo UART remonta os bits em bytes completos. Cada UART contém um registrador de deslocamento, que é o método fundamental de conversão entre formas seriais e paralelas. A comunicação serial pode ocorrer por meio de um único fio ou por transmissão paralela utilizando vários fios.

A comunicação pode ser simplex (em uma direção apenas), full duplex (ambos os dispositivos enviam e recebem ao mesmo tempo) ou half duplex (os dispositivos se revezam na transmissão e recepção).

## Projeto

Para esse projeto usaremos a UART0, pois ela é mapeada com a interface USB, conforme mostra a documentação: TM4C Series TM4C129E Crypto Connected EK-TM4C129EXL.
Para converter uma letra maiúscula para minúscula, utilizamos a tabela ASCII para sabermos a codificação dos caracteres em forma  número decimal.

![ASCII](https://github.com/lukaltk/lukaltk_CSW41/blob/c3e28ae202649a0a478da7aa412af5682e9484bc/Lab4/screenshots/ascii-7bits-v2.png)

Com a tabela, podemos concluir uma letra maiúscula e seu equivalente em minúsculo, possui uma diferença de 32. Logo para convertermos uma letra maiúscula para uma minúscula devemos somar 32 ao valor que é recebido do UART. E para converter de minúscula para maiúscula devemos subtrair 32.

Para receber os dados da UART, uma interrupção de UART será utilizada toda vez que houver algum caractere sendo recebido, para registrar uma interrupção no vetor de interrupções, no arquivo `startup_ewarm.c`  foi alterado o nome da função referente a interrupção do UART.

![UARTHandler](https://github.com/lukaltk/lukaltk_CSW41/blob/c3e28ae202649a0a478da7aa412af5682e9484bc/Lab4/screenshots/UARTHandler.PNG)

Como explicitado anteriormente, o algoritmo consiste no trecho de código abaixo. Sendo que parte do código que não foi explicada, consiste apenas nas configurações dos periféricos.

![UARTConverter](https://github.com/lukaltk/lukaltk_CSW41/blob/c3e28ae202649a0a478da7aa412af5682e9484bc/Lab4/screenshots/UARTConverter.PNG)

# Referências

1. TM4C Series TM4C129E Crypto Connected EK-TM4C129EXL

2. Universal asynchronous receiver-transmitter https://en.wikipedia.org/wiki/Universal_asynchronous_receiver-transmitter

3. UART https://paginas.fe.up.pt/~hsm/docencia/comp/uart/
