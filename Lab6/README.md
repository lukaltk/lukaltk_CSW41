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

![tx_get_time](https://github.com/lukaltk/lukaltk_CSW41/blob/84d4cca2e40b2b1885cda34082bb5b9224be5240/Lab6/screenshots/tx_time_get.PNG)

Para criar uma thread, podemos utilizar a função `tx_thread_create()` passando os seguintes parâmetros:

![tx_create](https://github.com/lukaltk/lukaltk_CSW41/blob/84d4cca2e40b2b1885cda34082bb5b9224be5240/Lab6/screenshots/tx_thread_create.PNG)

Em uma aplicação que possui várias threads é necessário registrar o espaço de memória que estamos utilizando, caso não seja possível pegar espaços consecutivos, precisamos de um algoritmo para unir os espaços de memórias, a fim de formar um bloco. E para isso podemos utilizar a função `tx_byte_pool_create()`, que é um serviço que cria um bloco de memória em uma área especificada. O jeito mais seguro para criar threads no `ThreadX` é solicitar um bloco de memória onde serão armazenadas as pilhas das threads criadas.

![tx_byte_pool](https://github.com/lukaltk/lukaltk_CSW41/blob/84d4cca2e40b2b1885cda34082bb5b9224be5240/Lab6/screenshots/tx_byte_pool.PNG)

---

### Escalonamento

a) Escalonamento por time-slice de 50 ms. Todas as tarefas com mesma prioridade.

![Escalonamento_time-slice](https://github.com/lukaltk/lukaltk_CSW41/blob/84d4cca2e40b2b1885cda34082bb5b9224be5240/Lab6/screenshots/Escalonamento_time-slice.PNG)

b) Escalonamento sem time-slice e sem preempção. Prioridades estabelecidas no passo 3. A preempção pode ser evitada com o “
preemption threshold” do ThreadX.

![Escalonamento_sem_time-slice](https://github.com/lukaltk/lukaltk_CSW41/blob/84d4cca2e40b2b1885cda34082bb5b9224be5240/Lab6/screenshots/Escalonamento_sem_time-slice.PNG)

c) Escalonamento preemptivo por prioridade.

![Escalonamento_preemptivo](https://github.com/lukaltk/lukaltk_CSW41/blob/84d4cca2e40b2b1885cda34082bb5b9224be5240/Lab6/screenshots/Escalonamento_preemptivo.PNG)

d) Implemente um Mutex compartilhado entre T1 e T3. No início de cada job estas tarefas devem solicitar este mutex e liberá-lo no
final. Use mutex sem herança de prioridade. Observe o efeito na temporização das tarefas.

![Escalonamento_mutex compartilhado](https://github.com/lukaltk/lukaltk_CSW41/blob/84d4cca2e40b2b1885cda34082bb5b9224be5240/Lab6/screenshots/Escalonamento_mutex%20compartilhado.PNG)

# Referências

- Descrição dos serviços do Azure RTOS ThreadX SMP - https://docs.microsoft.com/en-us/azure/rtos/threadx/chapter4
- Medição de tempo das funções baseadas em ThreadX - https://en-support.renesas.com/knowledgeBase/18539139
- Descrição do serviço tx_thread_create - https://docs.microsoft.com/en-us/azure/rtos/threadx/chapter4#tx_thread_create
- Descrição do serviço tx_byte_pool_create - https://docs.microsoft.com/en-us/azure/rtos/threadx/chapter4#tx_byte_pool_create
