# Sistemas Embarcados

- Código: CSW41
- Professor: Douglas Paulo Bertrand Renaux
- Email: douglasrenaux@professores.utfpr.edu.br

- Aluno: Luka Takeshi Kato
- Email: luka@alunos.utfpr.edu.br


# Lab2 - Jogo de Tempo de Reação
#### Objetivo
A partir da biblioteca TivaWare, desenvolver uma aplicação embarcada que faz uso de interrupções e interage com
dispositivos de I/O (botões e leds).

#### Introdução
1. Primeiro passo, no IAR foi criado o projeto do laboratório 2.

2. Obteve-se o TivaWare versão 2.2.0.295, o datasheet do processador e o manul do usuário. OBS: Kit utilizado EK-TM4C129EXL
link: https://www.ti.com/tool/EK-TM4C129EXL
![TivaWareDownload](https://github.com/lukaltk/lukaltk_CSW41/blob/cc225d353d9cfd87cfa59225412acf23e22c6ef5/Lab2/screenshots/TivaWare.PNG)

3. Com isso o projeto foi configurado para utilizar o kit, nas opções do projeto criado, foi selecionado o dispositivo.
![optionDevice](https://github.com/lukaltk/lukaltk_CSW41/blob/cc225d353d9cfd87cfa59225412acf23e22c6ef5/Lab2/screenshots/Device.PNG)

4. Em `C/C++ Compiler`, na aba `Preprocessor` foi incluído o diretório da TivaWare que foi instalado.
![optionPreprocessor](https://github.com/lukaltk/lukaltk_CSW41/blob/cc225d353d9cfd87cfa59225412acf23e22c6ef5/Lab2/screenshots/Preprocessor.PNG)

5. E para finalizar a configuração,  em `Debugger`, na aba `Setup`, foi escolhido o driver `TI Stellaris`.
![optionDriver](https://github.com/lukaltk/lukaltk_CSW41/blob/cc225d353d9cfd87cfa59225412acf23e22c6ef5/Lab2/screenshots/Driver.PNG)

6. Com isso, foi importado os arquivos disponibilizados pelo professor, que usa como base um programa para fazer um LED da placa piscar de tempo em tempo.
![ledOff](https://github.com/lukaltk/lukaltk_CSW41/blob/29e997debc2b393ae807d36fd375898974550c33/Lab2/screenshots/OFF.jpeg)
![ledOn](https://github.com/lukaltk/lukaltk_CSW41/blob/29e997debc2b393ae807d36fd375898974550c33/Lab2/screenshots/ON.jpeg)

7. O exemplo original do `blinky` utiliza um loop para gerar a temporização da piscada do LED. A variável `ui32Loop` é declarada como `volatile` dentro de `main()`, pois esse modificador de acesso é utilizado para indicar ao compilador que a variável especificada pode ser alterada por eventos externos, isto é, o conteúdo da variável pode ser alterado de forma não explícita. Por exemplo, uma rotina de interrupção pode alterar o valor de uma variável utilizada em outro procedimento.

8. Para fazer isso devemos primeiro inicializar o sistema com um clock conhecido. Para isso utilizamos a função `SysCtlClockFreqSet()`, então para configurar o clock para 120 MHz, podemos utilizar a função da seguinte maneira:
![clockConfig](https://github.com/lukaltk/lukaltk_CSW41/blob/29e997debc2b393ae807d36fd375898974550c33/Lab2/screenshots/ClockConfig.PNG)

9. Depois disso utilizamos uma função para configurar o Systick para ele chamar uma interrupção depois de uma certa contagem de clocks.
![systickSetup](https://github.com/lukaltk/lukaltk_CSW41/blob/29e997debc2b393ae807d36fd375898974550c33/Lab2/screenshots/SystickSetup.PNG)

10. Como o clock é de 120 MHz, quando utilizamos a função `SysTickPeriodSet(contagem_de_clocks)` passamos a quantidade de clocks que queremos para acontecer uma interrupção, porém segundo a documentação (SW-TM4C-DRL-UG-2.2.0.295), o número máximo de clocks que o Systick conta é de 16.777.216, ou seja, temos que fracionar em várias contagens de tempo, se quisermos contar 1 segundo. Por isso a interrupção faz um aumento em uma flag, e cada 10 adições temos 1 segundo.

![countFlag](https://github.com/lukaltk/lukaltk_CSW41/blob/main/Lab2/screenshots/flagCount.PNG)

11. E na `main()` é feito a lógica para o LED da placa piscar, a cada 3 segundos.

![blinky](https://github.com/lukaltk/lukaltk_CSW41/blob/main/Lab2/screenshots/blinky.PNG)

#### Jogo de Tempo de Reação

1. Da mesma maneira que foi feita na introdução fazemos para esse laboratório. Inicializamos o 'port J' para podermos usar o botão.

![portJEn](https://github.com/lukaltk/lukaltk_CSW41/blob/main/Lab2/screenshots/portJEnable.PNG)

2. A lógica é a mesma da introdução, a um contador de tempo (Systick) que quando passar 1 segundo o LED ascende, começando a contagem. 

3. Quando o usuário apertar o botão, o programa é finalizado e o tempo aparece no terminal de IO.

![time](https://github.com/lukaltk/lukaltk_CSW41/blob/29e997debc2b393ae807d36fd375898974550c33/Lab2/screenshots/Time.PNG)

4. E quando passa de 3 segundo sem apertar o botão o programa finaliza, dizendo que o tempo foi esgotado.

![timeout](https://github.com/lukaltk/lukaltk_CSW41/blob/29e997debc2b393ae807d36fd375898974550c33/Lab2/screenshots/TimeOut.PNG).

#### Referências

Tiva™ TM4C1294NCPDT Microcontroller - DATA SHEET (Funcionamento do clock da placa);
SW-TM4C-DRL-UG-2.2.0.295 - TivaWare™ Peripheral Driver Library (Systick API Functions);
TM4C Series TM4C129E Crypto Connected EK-TM4C129EXL - User's Guide (Verificação dos pinos para o botão e para o LED).
