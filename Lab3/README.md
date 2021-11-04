# Sistemas Embarcados

- Código: CSW41
- Professor: Douglas Paulo Bertrand Renaux
- Email: douglasrenaux@professores.utfpr.edu.br

- Aluno: Luka Takeshi Kato
- Email: luka@alunos.utfpr.edu.br


# Lab3 - Histograma
#### Objetivo
Elaborar uma rotina em assembly que será chamada de um programa em C++. A rotina deve gerar um histograma de uma imagem em tons de cinza.

# O histograma
Primeiro passo, no IAR foi criado o projeto do laboratório 3 e configurado conforme foi mostrado nos laboratórios anteriores. 
Um histograma é uma representação gráfica da distribuição de tons de uma imagem. Numa imagem em tons de cinza de 8-bits, cada pixel é representado por um valor de 8-bits, onde 0 seria a cor preta e 255 seria a cor branca. Logo, para o histograma o eixo horizontal apresenta os possíveis valores dos pixels (neste caso de 0 a 255) e o eixo vertical indica a quantidade pixels da imagem tem aquele valor. Com a definição do problema, foi elaborado o seguinte algoritmo:

## histogram.s

Primeiramente foi configurado para que o arquivo `.s` tivesse o acesso público, definido uma sessão e um alinhamento, e instruções do tipo `thumb`.

![config](https://github.com/lukaltk/lukaltk_CSW41/blob/2d91b92df84f77496b7022a42a246b9614887abd/Lab3/screenshots/EightBitHistogram.PNG)

#### EightBitHistogram         
Responsável por salvar o contexto e verificar se o número de elementos é maior que o que 64k (tamanho máximo da imagem), caso o número de elementos exceda o tamanho máximo, o programa desvia para o label **Return** que coloca 0 no Registrador R0 (indicação de erro) e restaura o contexto. Caso a função esteja dentro do limite permitido, o programa dará continuidade para um loop em que fará a contagem do histograma.

![config](https://github.com/lukaltk/lukaltk_CSW41/blob/2d91b92df84f77496b7022a42a246b9614887abd/Lab3/screenshots/Histogram.PNG)

#### Loop 
Nessa label será varrida a imagem, onde cada pixel da imagem será contabilizado com a label `Count`. Por exemplo, quando o pixel 0x13 é encontrado, é somado ele ao endereço base, nesse novo endereço serão contabilizadas todas as aparições desse pixel, que é realizado na label **Count**, para retornar ao endereço base a instrução SUB é chamada duas vezes já que existem alguns pixels que estouram a contagem caso apenas 1 byte fosse alocado, o próprio 0x13 aparece 402 duas vezes isso implica que 8 bits não seria o suficiente para contabilizar todas as aparições.

![Loop](https://github.com/lukaltk/lukaltk_CSW41/blob/2d91b92df84f77496b7022a42a246b9614887abd/Lab3/screenshots/Loop.PNG)

#### Count 
A cada pixel carregado, essa label é chamada, ela é responsável por carregar a contagem do pixel no registrador R6 e somar 1 e colocar novamente na memória RAM.

![Count](https://github.com/lukaltk/lukaltk_CSW41/blob/2d91b92df84f77496b7022a42a246b9614887abd/Lab3/screenshots/Count.PNG)

#### Return
Caso o tamanho da imagem for maior que os 64K, o programa coloca 0 no Registrador R0 (indicação de erro) e restaura o contexto.

![Return](https://github.com/lukaltk/lukaltk_CSW41/blob/2d91b92df84f77496b7022a42a246b9614887abd/Lab3/screenshots/Return.PNG)

## main.cpp
Com a lógica algoritmo pronta, podemos utilizar a nossa função para construção do histograma.
Com as variáveis declaradas para passar por parâmetro na função, inicializamos a memória com o valor 0, para que possa ser chamada a função `EightBitHistogram`.

![Main](https://github.com/lukaltk/lukaltk_CSW41/blob/ade33bc74f34b4bc9eea989070642c2c2319acd7/Lab3/screenshots/main.PNG)

E rodando o programa, para a imagem fornecida pelo professor, obtemos o seguinte saída no terminal de IO:

![Output](https://github.com/lukaltk/lukaltk_CSW41/blob/200cf762cce908cf2be56cdf5761f92240b5d25c/Lab3/screenshots/output.PNG)

Para validar a resposta, foi utilizado a função de pesquisa por expressões regulares (REGEX) de um editor de texto para contabilizar de maneira mais simples.

![0x0d](https://github.com/lukaltk/lukaltk_CSW41/blob/4751eeaa9533b8eb454d2b7f993c33dba298d5e1/Lab3/screenshots/0x0d.PNG)
![0x13](https://github.com/lukaltk/lukaltk_CSW41/blob/4751eeaa9533b8eb454d2b7f993c33dba298d5e1/Lab3/screenshots/0x13.PNG)
![0x1e](https://github.com/lukaltk/lukaltk_CSW41/blob/4751eeaa9533b8eb454d2b7f993c33dba298d5e1/Lab3/screenshots/0x1e.PNG)
![0x20](https://github.com/lukaltk/lukaltk_CSW41/blob/4751eeaa9533b8eb454d2b7f993c33dba298d5e1/Lab3/screenshots/0x20.PNG)

Se compararmos com os resultados gerados pelo programa, podemos concluir que está gerando um histograma corretamente.

# Referências

1. IAR Assembler User Guide - https://wwwfiles.iar.com/arm/webic/doc/EWARM_AssemblerReference.ENU.pdf

2. ARM Procedure Call Standard for the ARM Architecture https://developer.arm.com/documentation/ihi0042/latest

3. ISA Arm Cortex M4 https://developer.arm.com/documentation/ddi0439/b/CHDDIGAC
