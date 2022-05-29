# Trabalho Prático: Engenharia de Software II

> Este é um trabalho da disciplina de Engenharia de Software II, do curso de Sistemas de Informação, na Universidade Federal de Minas Gerais (UFMG).

### Alunos:
- Lucas Sousa
- Misael Rezende

## Tema: Urna eletrônica*
O sistema da Urna eletrônica fornece algumas funcionalidades básicas de uma urna eletrônica para votação em um candidato a presidente e dois candidatos a senadores. As funcionalidades são:

- Inicialização da urna e o término da votação devem ser feitos utilizando uma senha.
- Somente a pessoa credenciada pelo Tribunal Superior Eleitoral (TSE) tem a senha de início e término da eleição.
- Cada eleitor pode votar uma única vez, utilizando seu titulo de eleitor.
- Ao se apresentar para votar, o eleitor fornece o número de seu título. Caso os dados estejam corretos, o eleitor está apto a votar.
- O eleitor deve votar em 2 candidatos: um presidente e um senador.
- O eleitor pode votar nulo.
- Se o eleitor escolher um candidato inexistente e apertar a tecla CONFIRMA, o voto será nulo.
- Após o termino da eleição, a urna eletrônica apresenta estatísticas com o número de votos de cada candidato e as respectivas percentagens em relação ao total de votos válidos.
- A urna deve dizer os candidatos eleitos e derrotados.
- Considere uma eleição com apenas um turno, isto é, não há segundo turno e o candidato que recebe mais votos ganha.

## Tecnologias utilizadas
- O sistema foi escrito usando a linguagem _Python_. Como arquitetura, foi usado a _MVC_ (Model View Controller). Para armazenamento de dados, foi utilizado um arquivo _.txt_ simples.

-------
\* Inspirado em requisito de Trabalho Prático da matéria de Engenharia de Software I, do curso de Sistemas de Informação (UFMG), do professor Eduardo Figueiredo.