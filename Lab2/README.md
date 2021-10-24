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

<figure>
  <img src="https://github.com/lukaltk/lukaltk_CSW41/blob/29e997debc2b393ae807d36fd375898974550c33/Lab2/screenshots/OFF.jpeg" alt="led off" width="200" height="300">
</figure>

<figure>
  <img src="https://github.com/lukaltk/lukaltk_CSW41/blob/29e997debc2b393ae807d36fd375898974550c33/Lab2/screenshots/ON.jpeg" alt="led on" width="200" height="300">
</figure>

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

![portJConfig1](https://github.com/lukaltk/lukaltk_CSW41/blob/95db7ae307e9ed1e2575dcddfab2a8004d8d376c/Lab2/screenshots/portJConfig1.PNG)
![portJConfig1](https://github.com/lukaltk/lukaltk_CSW41/blob/95db7ae307e9ed1e2575dcddfab2a8004d8d376c/Lab2/screenshots/portJConfig2.PNG)

2. São declaradas **Flags** para a sinalização para o programa.

![flags](https://github.com/lukaltk/lukaltk_CSW41/blob/967071968930f481fa347862fa31960280291366/Lab2/screenshots/Flags.PNG)

Sendo que:
  - flag: Tempo em milissegundos do contador;
  - portJflag: Indicador de acionamento do botão;
  - startFlag: Indicador de início do jogo.

3. Da mesma forma que fazemos com o `Systick`, também criamos uma interrupção para o aperto do botão, onde ela configura `portJflag` como 1.

![portJHandler](https://github.com/lukaltk/lukaltk_CSW41/blob/6c012841bb644500fc71ffe43fe7fadb65a47000/Lab2/screenshots/portJInt.PNG)

4. Quando o programa é iniciado, depois de todas as configurações feitas,  após 1 segundo o LED ascende e impresso na tela: `Start!`, para indicar que o jogo iniciou.

![start](https://github.com/lukaltk/lukaltk_CSW41/blob/967071968930f481fa347862fa31960280291366/Lab2/screenshots/Start.PNG)

5. Quando o usuário apertar o botão, depois de iniciar jogo, o programa é finalizado, o tempo aparece no terminal de IO e o LED apaga.

![timeCode](https://github.com/lukaltk/lukaltk_CSW41/blob/967071968930f481fa347862fa31960280291366/Lab2/screenshots/timeCode.PNG)

![time](https://github.com/lukaltk/lukaltk_CSW41/blob/29e997debc2b393ae807d36fd375898974550c33/Lab2/screenshots/Time.PNG)

6. E quando passa de 3 segundo sem apertar o botão o programa finaliza, dizendo que o tempo foi esgotado e o LED apaga.

![timeoutCode](https://github.com/lukaltk/lukaltk_CSW41/blob/967071968930f481fa347862fa31960280291366/Lab2/screenshots/TimeoutCode.PNG)

![timeout](https://github.com/lukaltk/lukaltk_CSW41/blob/29e997debc2b393ae807d36fd375898974550c33/Lab2/screenshots/TimeOut.PNG).

#### Referências

  - Tiva™ TM4C1294NCPDT Microcontroller - DATA SHEET (Funcionamento do clock da placa);
  - SW-TM4C-DRL-UG-2.2.0.295 - TivaWare™ Peripheral Driver Library (Systick API Functions);
  - TM4C Series TM4C129E Crypto Connected EK-TM4C129EXL - User's Guide (Verificação dos pinos para o botão e para o LED).
