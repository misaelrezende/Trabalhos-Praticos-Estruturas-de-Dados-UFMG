#include "Bibliotecas/arvore.h"

// Retorna o nó raiz da árvore
Apontador inicializaArvore(Apontador arvore){
  arvore = (Apontador) malloc (sizeof(No));
  arvore->esquerda = NULL;
  arvore->direita = NULL;
  return arvore;
}

// Retorna um nó alocado dinamicamente
Apontador criaNo(){
  Apontador aux = (Apontador) malloc (sizeof(No));
  aux->esquerda = NULL;
  aux->direita = NULL;
  return aux;
}

// fonte de consulta slide Raquel - Arvore de Pesquisa Binária
// que é do livro do Nívio Ziviani
// Insere um nó na arvore
void insere(Apontador no, Registro atual, int posicao){

  // se estou no ultimo simbolo do codigo morse a ser inserido
  if(atual.codigoMorse[posicao+1] == '\0'){
    if(atual.codigoMorse[posicao] == '.'){
      if( no->esquerda == NULL ){
        // cria no na esquerda e insere atual
        no->esquerda = criaNo(); // no->esq passa a apontar para novo no
        no->esquerda->registro.simbolo = '.';
      }
      no->esquerda->registro.simbolo = atual.simbolo; // guarda o simbolo ( '.' ou '-' )
      strcpy( no->esquerda->registro.codigoMorse, atual.codigoMorse ); // guarda o codigo morse (ex: "-.--")
      strcpy( no->esquerda->registro.caractere, atual.caractere ); // guarda o caractere (ex: A, B, 8, etc)

    }else{ // senao eh '-'
      if( no->direita == NULL ){
        // cria no na direita e insere atual
        no->direita = criaNo(); // no->esq passa a apontar para novo no
        no->direita->registro.simbolo = '-';
      }
      no->direita->registro.simbolo = atual.simbolo; // guarda o simbolo ( '.' ou '-' )
      strcpy( no->direita->registro.codigoMorse, atual.codigoMorse ); // guarda o codigo morse (ex: "-.--")
      strcpy( no->direita->registro.caractere, atual.caractere ); // guarda o caractere (ex: A, B, 8, etc)

    }

    return; // para não rodar restante do código
  }

  // se a posicao = '.'
  if (atual.codigoMorse[posicao] == '.'){ // vai para o no da esquerda
    // se o no NAO existe
    if( no->esquerda == NULL ){
      no->esquerda = criaNo(); // no->esquerda aponta para novo nó criado
      no->esquerda->registro.simbolo = '.';
    }

    insere(no->esquerda, atual, posicao+1);
  }

  // se a posicao = '-'
  else if (atual.codigoMorse[posicao] == '-'){ // vai para o no da direita
    // se o no NAO existe
    if( no->direita == NULL ){
      no->direita = criaNo(); // no->direita aponta para novo nó criado
      no->direita->registro.simbolo = '-';
    }

    insere(no->direita, atual, posicao+1);
  }

}


void decodificaMensagem(Apontador arvoreMorse, char *matrizMensagemDecodificada,
     int linha, char *mensagemCodificada){

  Apontador percorreArvore = arvoreMorse; // recebe o endereço do nó raiz da arvore
  int i, j, tamanho = strlen(mensagemCodificada);

  for(i = 0, j = 0; i < tamanho; i++){

    percorreArvore = arvoreMorse; // recebe o endereço do nó raiz da arvore

    if(mensagemCodificada[i] != ' ' && mensagemCodificada[i] != '\n'){
      // percorre a string até encontrar um espaço ou barra
      while(mensagemCodificada[i] != ' ' && mensagemCodificada[i] != '\n'){
        if(mensagemCodificada[i] == '.')
          percorreArvore = percorreArvore->esquerda;
        else if(mensagemCodificada[i] == '-')
          percorreArvore = percorreArvore->direita;

        i++;
      }
      matrizMensagemDecodificada[j] = percorreArvore->registro.caractere[0];
      j++;
    }

    if(mensagemCodificada[i] == '\n'){
      matrizMensagemDecodificada[j] = '\n';
      matrizMensagemDecodificada[j+1] = '\0';
      j = 0;
    }

    if(mensagemCodificada[i+1] == '/'){
      matrizMensagemDecodificada[j] = ' ';
      j++;
      i += 2;
    }


  }// fim do laço for

} // fim da função decodifica


// Imprime a árvore com caminhamento em pré-ordem
void imprimePreOrdem(Apontador arvoreMorse){
  if(arvoreMorse != NULL){
    printf("%s %s\n", arvoreMorse->registro.caractere,
    arvoreMorse->registro.codigoMorse);

    imprimePreOrdem(arvoreMorse->esquerda);
    imprimePreOrdem(arvoreMorse->direita);
  }
}

// Desaloca os nós alocados dinamicamente
void esvaziaArvore(Apontador arvore){
  if(arvore != NULL){
    esvaziaArvore(arvore->esquerda);
    esvaziaArvore(arvore->direita);
    free(arvore);
  }
}