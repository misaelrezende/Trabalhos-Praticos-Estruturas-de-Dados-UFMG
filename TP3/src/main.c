#include "Bibliotecas/arvore.h"

/*    MUDANÇAS RECENTES
  ** Criação da função que decodifica mensagem encriptada inserida
  ** função decodificadora funcionando normalmente

      PROBLEMAS/DÚVIDAS
  ** Como imprimir em préordem sem imprimir os nós vazios???
  ** 
*/

int main(int argc, char *argv[]){
  int linha = 0, quantidadeMensagens = 0;
  Registro auxiliar;
  char matrizMensagemDecodificada[50][250];
  FILE *apontadorArquivo = NULL;

  apontadorArquivo = fopen("morse.txt", "r");
  if(apontadorArquivo == NULL){
    printf("ERRO ao abrir o arquivo\n");
    exit(1);
  }
  
  Apontador arvoreMorse = NULL;
  // Inicializa a árvore com um nó vazio (nó raiz)
  arvoreMorse = inicializaArvore(arvoreMorse);

  // enquanto não chega no fim do arquivo
  while( !(feof(apontadorArquivo)) ){

    fscanf(apontadorArquivo, "%s%s", auxiliar.caractere, auxiliar.codigoMorse);
    // condição criada para evitar um bug após a leitura da ultima linha
    if( !(feof(apontadorArquivo)) ){
      // insere o novo caractere lido em um nó da arvore
      insere(arvoreMorse, auxiliar, 0);
    }else
      break;
  }

  // implementação especial para satisfazer condições de uso da função getline
  char *mensagemCodificada;
  mensagemCodificada = (char *) malloc(200 * sizeof(char));
  size_t buffSize = (200 * sizeof(char));

  // enquanto não ler todas linhas da entrada
  while(getline(&mensagemCodificada, &buffSize, stdin) != EOF){
    
    decodificaMensagem(arvoreMorse, matrizMensagemDecodificada[linha], linha,
      mensagemCodificada);

    linha++;
    quantidadeMensagens++;
  }

  // imprime a mensagem decodificada
  for(int i = 0; i < quantidadeMensagens; i++)
    printf("%s", matrizMensagemDecodificada[i]);
  printf("\n");

  // se foi passado o parâmetro -a
  if(argc > 1 && strcmp(argv[1], "-a") == 0){
    imprimePreOrdem(arvoreMorse);
  }
  
  // Desaloca os nós da arvore
  esvaziaArvore(arvoreMorse);
  arvoreMorse = NULL;

  fclose(apontadorArquivo);

  return 0;
}
