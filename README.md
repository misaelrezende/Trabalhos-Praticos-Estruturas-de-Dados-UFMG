# Trabalho Prático: Engenharia de Software II

O sistema deve conter um arquivo README com (1) os nomes dos membros do grupo, (2) explicação do sistema e (3) explicação das tecnologias utilizadas.

### Alunos:
- Lucas Sousa
- Misael Rezende

## Tema: Urna eletrônica*
O sistema deve fornecer as funcionalidades básicas de uma urna eletrônica para votação em um candidato a presidente e dois candidatos a senadores. Inicialização da urna e o término da votação devem ser feitos utilizando uma senha. Somente a pessoa credenciada pelo Tribunal Superior Eleitoral (TSE) tem a senha de início e término da eleição. Cada eleitor pode votar uma única vez, utilizando seu titulo de eleitor. Ao se apresentar para votar, o eleitor fornece o número de seu título. Pelo número do
título, a urna eletrônica apresenta o nome do eleitor e, após confirmação dos dados, inicia a votação daquele eleitor. Alguns eleitores podem se abster da votação. O eleitor deve votar em 3 candidatos: um presidente e dois senadores. O eleitor pode votar em branco ou nulo. Após o termino da eleição, a urna eletrônica apresenta estatísticas com o número de votos de cada candidato e as respectivas percentagens em relação ao total de votos válidos. A urna deve dizer os candidatos eleitos e derrotados. Considere uma eleição com apenas um turno, isto é, não há segundo turno e o candidato que recebe mais votos ganha.

## Tecnologias utilizadas
- Python

-------
* Inspirado em requisito de TP da matéria de Engenharia de Software 1, do professor Eduardo Figueiredo