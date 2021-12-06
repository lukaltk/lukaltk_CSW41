# Sistemas Embarcados

- Código: CSW41
- Professor: Douglas Paulo Bertrand Renaux
- Email: douglasrenaux@professores.utfpr.edu.br

- Aluno: Luka Takeshi Kato
- Email: luka@alunos.utfpr.edu.br

# Lab6 - Escalonamento
#### Objetivo
Criar um conjunto de 3 tarefas com temporizações conhecidas. Experimentar variações de algoritmos de escalonamento no ThreadX.

#### Projeto

O algoritmo para esse laboratório é basicamente uma medição de tempo, e para isso, podemos utilizar a função `tx_time_get()` para a obtenção do tempo. Assim, podemos utilizar a função para obter o tempo antes da execução da tarefa, após a execução da tarefa obtemos o tempo novamente. Com isso conseguimos saber o tempo de execução das tarefas.

![tx_get_time]()

Para criar uma thread, podemos utilizar a função `tx_thread_create()` passando os seguintes parâmetros:

![tx_create]()

Em uma aplicação que possui várias threads é necessário registrar o espaço de memória que estamos utilizando, caso não seja possível pegar espaços consecutivos, precisamos de um algoritmo para unir os espaços de memórias, a fim de formar um bloco. E para isso podemos utilizar a função `tx_byte_pool_create()`, que é um serviço que cria um bloco de memória em uma área especificada. O jeito mais seguro para criar threads no `ThreadX` é solicitar um bloco de memória onde serão armazenadas as pilhas das threads criadas.

![tx_byte_pool]()

#### Escalonamento

a) Escalonamento por time-slice de 50 ms. Todas as tarefas com mesma prioridade.

![Escalonamento_time-slice]()

b) Escalonamento sem time-slice e sem preempção. Prioridades estabelecidas no passo 3. A preempção pode ser evitada com o “
preemption threshold” do ThreadX.

![Escalonamento_sem_time-slice]()

c) Escalonamento preemptivo por prioridade.

![Escalonamento_preemptivo]()

d) Implemente um Mutex compartilhado entre T1 e T3. No início de cada job estas tarefas devem solicitar este mutex e liberá-lo no
final. Use mutex sem herança de prioridade. Observe o efeito na temporização das tarefas.

![Escalonamento_mutex compartilhado]()

e) Mutex com herança de prioridade.

![Escalonamento_mutex_herança_prioridade]()

# Referências

- Descrição dos serviços do Azure RTOS ThreadX SMP - https://docs.microsoft.com/pt-br/azure/rtos/threadx/threadx-smp/chapter4#tx_thread_create
- Medição de tempo das funções baseadas em ThreadX - https://en-support.renesas.com/knowledgeBase/18539139
