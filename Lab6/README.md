# Sistemas Embarcados
- Código: CSW41
- Créditos: 4
- Professor: Douglas Paulo Bertrand Renaux
- Email: douglasrenaux@professores.utfpr.edu.br
- Aluno: Gabriel Alexandre Linhares Calper Seabra
- Email: gabrielseabra@alunos.utfpr.edu.br


# Lab5

#### Introdução
Portar para a Tiva o projeto exemplo do ThreadX.
# Ambiente

Neste laboratório a configuração do ambiente mudou, isso implica que teremos que configurar novamente o ambiente de desenvolvimento para a nova plataforma de RTOS(ThreadX), Antes estávemos desenvolvendo em Bare Metal, o novo diretório deve parecer como pode ser visto logo abaixo.
```shell
  $ tree
  .
  ├── Debug
  ├── settings
  ├── README.md
  ├── tx.a
  └── src
      ├── cstartup_M.s
      ├── sample_threadx.c
      └── tx_initialize_low_level.s
```

Mapeie o código do Threadx de acordo com as mensagens de erros geradas no console de log, ou simplesmente mapeie igual a imagem abaixo, tanto para o projeto tx quanto para o sample_threadx.

![image](https://user-images.githubusercontent.com/48101913/143146428-c57d46d5-eaee-470c-ac13-c1a0bc2319c1.png)


Agora é necessário comppilar o ThreadX em uma biblioteca estática para que ele esteja disponível no nosso código., para compilar para arquitetura ARM Cortex M4 é só ir na pasta /ThreadX/ports/cortex_m4 e escolher em qual compilador você irá compilar, note que existem várias além de ser possível compilar usando as ferramentas GNU, entretanto para esse lab usaremos a IDE da iar que vem com seu compilador proprietário, para isso navegue até a pasta \ThreadX\ports\cortex_m4\iar e abra o projeto e compile-o, Isso irá gerar o arquivo abaixo. Para saber o que foi compilado basta você verificar com a ferramenta de linha de comando **arm-none-eabi-nm tx.a** ou **arm-none-eabi-ar t tx.a**.

![image](https://user-images.githubusercontent.com/48101913/143145717-07d7a922-875b-493d-b501-7d99f3ba918f.png)

Agora copie os arquivos sample_threadx.c, cstartup.c e tx_initialize_low_level.c para pasta src além de também copiar para a pasta Lab5 o tx.a.

![image](https://user-images.githubusercontent.com/48101913/143147874-acf8689c-f19f-4d3a-81d7-27a5e37a0e3f.png)


Mapeie o projeto igual a imagem abaixo.

![image](https://user-images.githubusercontent.com/48101913/143148117-32c4d4ce-702b-4bd2-a6ec-1f3ab8f98840.png)

No Linker mapeie a biblioteca estática do ThreadX, que foi o arquivo inicialmente compilado nos dois primeiros passos, conforme a imagem abaixo.

![image](https://user-images.githubusercontent.com/48101913/143148369-d688d0d5-b40c-49ad-aa00-d49e5b2d2f43.png)

Agora habilite o plugin ThreadX para que na hora do debug algumas funções estejam disponíveis

![image](https://user-images.githubusercontent.com/48101913/143149282-24a67bc4-fecf-4bea-885c-a122021687eb.png)

O plugin de ThreadX é muito importante pois ele dá informaações sobre as threads durante o debug, basta apenas apertar o botão **pause** que é possível ver as informações de cada thread, existem várias funções que podem ser exploradas, mas para este lab vamos nos ater as que são necessária para preencher a tabela solicitada pelo professor(Abaixo foto da função thread list do plugin).

![image](https://user-images.githubusercontent.com/48101913/143153919-001d8277-913d-4be9-8233-3e52f0dedee5.png)

Todos os nomes de Threads estão definidos logo no começo do código , assim é possível preencher todos os campos "entry function " da tabela

![image](https://user-images.githubusercontent.com/48101913/143154331-84211292-44be-41b8-bd7b-900f863f793d.png)

Para preencher o stack size e priority é so pausar a execução do programa e selecionar o plugin Thread List.

![image](https://user-images.githubusercontent.com/48101913/143154692-0404c5ba-5122-45f7-a2eb-c02b719b6cc7.png)

Para preencher o auto start da planilha basta olhar o último parâmtro da função **tx_thread_create()** que é responsável por configurar a thread. Uma informação adicional é que o threadx possui um TCB (task control block) e esse TCB é o primeiro parâmetro que é passado para a função **tx_thread_create()** veja que cada thread possui seu próprio TCB, que é comum em sistemas operacionais ele possui muitas informações sobre a thread, no linux por exemplo esse TCB no kernel atual possui mais de 1000 propriedades, a imagem abaixo mostra a definição TCB do ThreadX, veja que ele possui muitas informações importantes.

![image](https://user-images.githubusercontent.com/48101913/143163575-fc62b32e-4031-4ed0-95b7-cd85ed9e8a90.png)

Para preencher a a última coluna da primeira tabela a documentação do ThreadX foi consultada, a documentação diz o quarto parâmetro é o time-slice(tempo que a tarefa executa sem ser interrompida).

![image](https://user-images.githubusercontent.com/48101913/143167449-805113a8-71f7-4376-9c32-f160f3218f04.png)

Descrição dos parâmetros da **tx_thread_create()**.
![image](https://user-images.githubusercontent.com/48101913/143167625-1c9fecad-c522-4001-a2b3-b7d40519220c.png)



Explorado todos os campos, a tabela final fica assim:

| Thread Name 	| entry function       	| stack size 	| priority 	| auto start 	| time slicing     	|
|-------------	|----------------------	|------------	|----------	|------------	|------------------	|
| Thread 0    	| threthread_0_entry   	| 1024       	| 1        	| yes        	| TX_NO_TIME_SLICE 	|
| Thread 1    	| thread_1_entry       	| 1024       	| 16       	| yes        	| 4                	|
| Thread 2    	| thread_2_entry       	| 1024       	| 16       	| yes        	| 4                	|
| Thread 3    	| thread_3_and_4_entry 	| 1024       	| 8        	| yes        	| TX_NO_TIME_SLICE 	|
| Thread 4    	| thread_3_and_4_entry 	| 1024       	| 8        	| yes        	| TX_NO_TIME_SLICE 	|
| Thread 5    	| thread_5_entry       	| 1024       	| 4        	| yes        	| TX_NO_TIME_SLICE 	|
| Thread 6    	| thread_6_and_7_entry 	| 1024       	| 8        	| yes        	| TX_NO_TIME_SLICE 	|
| Thread 7    	| thread_6_and_7_entry 	| 1024       	| 8        	| yes        	| TX_NO_TIME_SLICE 	|

|      Name     	| control structure 	| size 	|   location   	|
|:-------------:	|:-----------------:	|:----:	|:------------:	|
|  byte pool 0  	|    byte_pool_0    	| 9120 	|  0x2000.0004 	|
|  block pool 0 	|    block_pool_0   	|  100 	|  0x2000.21e4 	|
| event flags 0 	|   event_flags_0   	|  1 bit|  0x2000.30c0 	|
|    mutex 0    	|      mutex_0      	|  1 bit|  0x2000.3028 	|
|  semaphore 0  	|    semaphore_0    	|   -  	|  0x2000.30e8 	|
|    queue 0    	|      queue_0      	|  100 	| 0xx2000.2fec 	|



Note que todas essas estruturas de controle, na verdade são **STRUCTS** da linguagem C e podem ser assististidas pela ferramenta de live watcha da IAR, note que as structs possuem vários campos que podem ser futuramente utilizados(abaixo um exemplo assistindo comportamento da etrutura no live watch).

![image](https://user-images.githubusercontent.com/48101913/143171778-72935d01-db2c-4a3c-aa74-7c1c527ebfb8.png)



# Referências

1.  Descrição de funções do ThreadX - https://docs.microsoft.com/en-us/azure/rtos/threadx/chapter4#tx_byte_pool_create

