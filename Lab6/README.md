# Sistemas Embarcados

- Código: CSW41
- Professor: Douglas Paulo Bertrand Renaux
- Email: douglasrenaux@professores.utfpr.edu.br

- Aluno: Luka Takeshi Kato
- Email: luka@alunos.utfpr.edu.br

# Lab4 - Comunicação Serial
#### Objetivo
Portar para a Tiva o projeto exemplo do ThreadX.

#### Projeto

Primeiramente foi compilado o ThreadX em uma biblioteca estática para que ele esteja disponível no nosso código. 
Para isso basta ir na pasta `/ThreadX/ports/cortex_m4` e escolher em qual compilador irá ser utilizado, como para essa atividade utilizaremos a IDE da IAR que utiliza um compilador próprio, na pasta `/ThreadX/ports/cortex_m4/iar`,  foi compilado o projeto `tx` e `sample_threadx`, e isso gerou o arquivo `tx.a`, que foi incluído no projeto do lab5.

![txA](https://github.com/lukaltk/lukaltk_CSW41/blob/0508bf7789d9267da4f6386d909aba2cd40f239b/Lab5/screenshots/txA.PNG)

Logo após isso foi mapeado o código do ThreadX para o `Preprocessor`.

![CPreprocessor](https://github.com/lukaltk/lukaltk_CSW41/blob/0508bf7789d9267da4f6386d909aba2cd40f239b/Lab5/screenshots/CPreprocessor.PNG)

E no Linker foi mapeada a biblioteca estática do ThreadX, que foi o arquivo gerado anteriormente (`tx.a`).

![Linker](https://github.com/lukaltk/lukaltk_CSW41/blob/0508bf7789d9267da4f6386d909aba2cd40f239b/Lab5/screenshots/Linker.PNG)

Por fim, foi habilitado o plugin ThreadX para a utilização de algumas funções na hora da depuração.

![plugin](https://github.com/lukaltk/lukaltk_CSW41/blob/0508bf7789d9267da4f6386d909aba2cd40f239b/Lab5/screenshots/PluginPNG.PNG)

Podemos observar os nomes das Threads definidos logo no começo do código, assim é possível preencher todos os campos `entry function` da tabela.

![entryFunction](https://user-images.githubusercontent.com/48101913/143154331-84211292-44be-41b8-bd7b-900f863f793d.png)

Para preencher o `stack size` e `priority` basta utilizarmos o  plugin da `ThreadX`, podemos obter informações sobre as threads durante a depuração com o `pause` que permite ver as informações de cada thread. Por esse motivo, ocorre a pausa da execução do programa e selecionamos o plugin `Thread List`.

![threadList](https://user-images.githubusercontent.com/48101913/143154692-0404c5ba-5122-45f7-a2eb-c02b719b6cc7.png)

Para preencher o `auto start` da tabela, basta observar o último parâmetro da função `tx_thread_create()` que é responsável por configurar a thread.

Para preencher o `time slicing` da primeira tabela, foi consultada a documentação do ThreadX, onde podemos consultar qual parâmetro é utilizado para o `time-slice` (tempo que a tarefa executa sem ser interrompida). Conforme mostram as figuras abaixo.

![timeSlice](https://github.com/lukaltk/lukaltk_CSW41/blob/0508bf7789d9267da4f6386d909aba2cd40f239b/Lab5/screenshots/timeSlice.PNG)

Parâmetros da **tx_thread_create()**.

![tx_create_1](https://github.com/lukaltk/lukaltk_CSW41/blob/0508bf7789d9267da4f6386d909aba2cd40f239b/Lab5/screenshots/tx_create_1.PNG)

![tx_create_2](https://github.com/lukaltk/lukaltk_CSW41/blob/0508bf7789d9267da4f6386d909aba2cd40f239b/Lab5/screenshots/tx_create_2.PNG)

![tx_create_3](https://github.com/lukaltk/lukaltk_CSW41/blob/0508bf7789d9267da4f6386d909aba2cd40f239b/Lab5/screenshots/tx_create_3.PNG)

Com os isso, podemos preencher os dados das tabelas:

![tabela1](https://github.com/lukaltk/lukaltk_CSW41/blob/0508bf7789d9267da4f6386d909aba2cd40f239b/Lab5/screenshots/tabela1.PNG)

![tabela2](https://github.com/lukaltk/lukaltk_CSW41/blob/0508bf7789d9267da4f6386d909aba2cd40f239b/Lab5/screenshots/tabela2.PNG)

# Referências

- Descrição dos serviços do Azure RTOS ThreadX SMP - https://docs.microsoft.com/pt-br/azure/rtos/threadx/threadx-smp/chapter4#tx_thread_create

