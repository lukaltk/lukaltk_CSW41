# Sistemas Embarcados

- Código: CSW41
- Professor: Douglas Paulo Bertrand Renaux
- Email: douglasrenaux@professores.utfpr.edu.br

- Aluno: Luka Takeshi Kato
- Email: luka@alunos.utfpr.edu.br


# Lab1 - Infraestrutura de Laboratório

#### Objetivo
Validar a infraestrutura laboratorial necessária para os próximos experimentos: IAR e Github

#### Execução
1. Primeiro passo foi baixar a **_IDE IAR Embedded Workbench for ARM_** disponível em https://www.iar.com/products/architectures/arm/iar-embedded-workbench-for-arm/

2. Registrar como “Code size limited”.

3. Depois de instalado e devidamente licenciado a estrutura de diretório foi criada.

![CSW41 Repository Schema](https://github.com/lukaltk/CSW41/blob/df4e278997e2caf61aa80a5a2e31f03619c2433e/lukaltk_CSW41/Lab1/screenshots/folders.PNG)

4. Com isso no IAR foi criado o projeto do laboratório 1.

![IAR Creating Project](https://github.com/lukaltk/CSW41/blob/df4e278997e2caf61aa80a5a2e31f03619c2433e/lukaltk_CSW41/Lab1/screenshots/createProject.png)

5. Foi selecionado o projeto em C++.

![C++ project](https://github.com/lukaltk/CSW41/blob/df4e278997e2caf61aa80a5a2e31f03619c2433e/lukaltk_CSW41/Lab1/screenshots/projectType.png)

6. Após a criação do projeto foi configurado.

![IAR Project Config](https://github.com/lukaltk/CSW41/blob/df4e278997e2caf61aa80a5a2e31f03619c2433e/lukaltk_CSW41/Lab1/screenshots/configProject.png)

7. E configurado da seguinte forma:

![Cortex-M4 Config](https://github.com/lukaltk/CSW41/blob/df4e278997e2caf61aa80a5a2e31f03619c2433e/lukaltk_CSW41/Lab1/screenshots/cortexM4.PNG)
![Floating-point Settings](https://github.com/lukaltk/CSW41/blob/df4e278997e2caf61aa80a5a2e31f03619c2433e/lukaltk_CSW41/Lab1/screenshots/32-bit.PNG)
![Simulator Config](https://github.com/lukaltk/CSW41/blob/df4e278997e2caf61aa80a5a2e31f03619c2433e/lukaltk_CSW41/Lab1/screenshots/simulator.PNG)

8. Depois foi escrito o código inicial "Hello World" e para rodar o projeto é utilizado o botão **_Download and Debug_**.

![Run Project](https://github.com/lukaltk/CSW41/blob/df4e278997e2caf61aa80a5a2e31f03619c2433e/lukaltk_CSW41/Lab1/screenshots/runProject.PNG)

A janela Disassembly indica as instruções que o projeto está executando. E saída pode ser vista no Terminal I/O.

![Project Output](https://github.com/lukaltk/CSW41/blob/df4e278997e2caf61aa80a5a2e31f03619c2433e/lukaltk_CSW41/Lab1/screenshots/output.PNG)
