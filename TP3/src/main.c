#include "Bibliotecas/arvore.h"

/*    MUDANÇAS RECENTES
  ** leitura do arquivo morse.txt funcionando normalmente
  ** aparentemente criação da arvore esta ok
  ** falta testar a impressão em preordem

      PROBLEMAS/DÚVIDAS
  **

  ** Como INICIALIZAR a TRIE?
  ** testar a impressão em PREORDEM
  ** COMO DESALOCAR?
*/

int main(int argc, char *argv[]) {
  FILE *fp = NULL, *fp2 = NULL;
  Registro auxiliar;

  fp = fopen("morse.txt", "r");
  if(fp == NULL){
    printf("ERRO ao abrir o arquivo\n");
    exit(1);
  }
  // teste para checar se a leitura do morse.txt está correta
  fp2 = fopen("leitura.txt", "w+");
  if(fp2 == NULL){
    printf("ERRO ao abrir o arquivo\n");
    exit(1);
  }

  Apontador arvoreMorse = NULL; // ponteiro ou ponteiro de ponteiro?

  printf("%p\n", arvoreMorse);
  fflush(stdout);
  arvoreMorse = (Apontador) malloc (sizeof(No));
  arvoreMorse->esquerda = NULL;
  arvoreMorse->direita = NULL;
  printf("%p %lu\n", arvoreMorse, sizeof(arvoreMorse));
  fflush(stdout);

  // enquanto não chega no fim do arquivo
  while(!(feof(fp))){

    fscanf(fp, "%s%s", auxiliar.caractere, auxiliar.codigoMorse);
    //se não for fim do arquivo, faça...
    if(!(feof(fp))){
      Insere(auxiliar, arvoreMorse, 0);
      fprintf(fp2, "%s %s\n", auxiliar.caractere, auxiliar.codigoMorse);
      // printf("terminei de inserir");
      // fflush(stdout);
    }
    else
      break;
  }

  // se foi passado o parâmetro -a
  // if(argc == 2 && strcmp(argv[1], "-a") == 0){
  //   //imprimePreOrdem(arvoreMorse);
  // }

  /* Não esqueça de DESALOCAR A ÁRVORE NO FIM DO PROGRAMA */
  //esvaziaArvore(&arvoreMorse);

  fclose(fp);
  fclose(fp2);

  return 0;
}
