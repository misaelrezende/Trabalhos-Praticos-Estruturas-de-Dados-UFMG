#include "Bibliotecas/arvore.h"

/*    MUDANÇAS RECENTES
  ** Criação da arvore esta funcionando corretamente
  ** Impressão em preordem funcionando corretamente
  ** retirada de alguns trechos de códigos de teste que não sao mais necessários
  ** legibilidade do código melhorada
  ** Desalocando a arvore corretamente

      PROBLEMAS/DÚVIDAS
  ** Como imprimir em préordem sem imprimir os nós vazios???
  ** 
*/

int main(int argc, char *argv[]) {
  FILE *apontadorArquivo = NULL;
  Registro auxiliar;

  apontadorArquivo = fopen("morse.txt", "r");
  if(apontadorArquivo == NULL){
    printf("ERRO ao abrir o arquivo\n");
    exit(1);
  }
  // teste para checar se a leitura do morse.txt está correta
  /* apontadorArquivo2 = fopen("leitura.txt", "w+");
  if(apontadorArquivo2 == NULL){
    printf("ERRO ao abrir o arquivo\n");
    exit(1);
  } */

  Apontador arvoreMorse = NULL;
  // Inicializa a árvore com um nó vazio (nó raiz)
  arvoreMorse = inicializaArvore(arvoreMorse);

  // enquanto não chega no fim do arquivo
  while( !(feof(apontadorArquivo)) ){

    fscanf(apontadorArquivo, "%s%s", auxiliar.caractere, auxiliar.codigoMorse);
    // condição criada para evitar um bug após a leitura da ultima linha
    if( !(feof(apontadorArquivo)) )
      Insere(auxiliar, arvoreMorse, 0);
      // fprintf(apontadorArquivo2, "%s %s\n", auxiliar.caractere, auxiliar.codigoMorse);
    else
      break;
  }

  // se foi passado o parâmetro -a
  if(argc > 1 && strcmp(argv[1], "-a") == 0){
    imprimePreOrdem(arvoreMorse);
  }

  // Desaloca os nós da arvore
  esvaziaArvore(arvoreMorse);
  arvoreMorse = NULL;

  fclose(apontadorArquivo);
  // fclose(apontadorArquivo2);

  return 0;
}
