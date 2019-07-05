#include "Bibliotecas/arvore.h"

Apontador criaNo(){
  Apontador aux = (Apontador) malloc (sizeof(No));
  aux->esquerda = NULL;
  aux->direita = NULL;
  return aux;
}

// fonte slide Raquel - Arvore de Pesquisa Binária
void Insere(Registro atual, Apontador no, int posicao){

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
      strcpy( no->esquerda->registro.caractere, atual.caractere );
      // printf("%s\n", no->esquerda->registro.caractere);
    }else{ // senao eh '-'
      if( no->direita == NULL ){
        // cria no na direita e insere atual
        no->direita = criaNo(); // no->esq passa a apontar para novo no
        no->direita->registro.simbolo = '-';
      }
      no->direita->registro.simbolo = atual.simbolo; // guarda o simbolo ( '.' ou '-' )
      strcpy( no->direita->registro.codigoMorse, atual.codigoMorse ); // guarda o codigo morse (ex: "-.--")
      strcpy( no->direita->registro.caractere, atual.caractere );
      // printf("%s\n", no->direita->registro.caractere);
    }

    // printf("cheguei no fim do codigoMorse ");
    // fflush(stdout);
    // no->registro.simbolo = atual.simbolo; // guarda o simbolo ( '.' ou '-' )
    // strcpy( no->registro.codigoMorse, atual.codigoMorse ); // guarda o codigo morse (ex: "-.--")
    // strcpy( no->registro.caractere, atual.caractere );
    return; // para não rodar o codigo de baixo

    // se o simbolo atual for .
    //     se nao tiver alguem na esquerda
    //          cria no na esquerda e insere atual
    //     se houver alguem na esquerda
    //          o item a ser inserido já está na árvore
    // se o simbolo atual for -
    //     se nao tiver alguem na direita
    //          cria no na direita e insere atual
    //     se houver alguem na direita
    //          o item a ser inserido já está na árvore


    // se 'atual.caractere' == 'no->registro.caractere',
    // significa que eu estou adicionando um registro que já
    // está na árvore

    // se não, o 'no->registro' tem que ir pra baixo na árvore
    // e o atual deve ser inserido no lugar de no->registro
    ////////////////////
    // se o simbolo atual for .
    //     se nao tiver alguem na esquerda
    //          cria no na esquerda e insere atual
    //     se houver alguem na esquerda
    //          o no->esquerda deve ir para no->esquerda->{esquerda ou direita}
    //          o atual deve ser inserido no no->esquerda
    // se o simbolo atual for -
    //     se nao tiver alguem na direita
    //          cria no na direita e insere atual
    //     se houver alguem na direita
    //          o no->direita deve ir para no->direita->{esquerda ou direita}
    //          o atual deve ser inserido no no->direita
  }

  // se posicao = '.'
  if (atual.codigoMorse[posicao] == '.'){ // vai para o no da esquerda
    // se o no NAO existe
    if( no->esquerda == NULL ){
      no->esquerda = criaNo(); // cria novo no
      no->esquerda->registro.simbolo = '.';
    }
    // printf("passei '.' ");
    // fflush(stdout);
    // se o no existe
    Insere(atual, no->esquerda, posicao+1);

  }
  // se posicao = '-'
  else if (atual.codigoMorse[posicao] == '-'){ // vai para o no da direita
    // se o no NAO existe
    // printf("passou aqui tmb\n");
    if( no->direita == NULL ){
      no->direita = criaNo(); // cria novo no
      no->direita->registro.simbolo = '-';
    }
    // printf("passei '-' ");
    // fflush(stdout);
    // se o no existe
    Insere(atual, no->direita, posicao+1);

  }

}

void imprimePreOrdem(Apontador arvoreMorse){
  // imprime assim que passa no nó
  if(arvoreMorse != NULL){

      printf("%s %s\n", arvoreMorse->registro.caractere,
      arvoreMorse->registro.codigoMorse);

    imprimePreOrdem(arvoreMorse->esquerda);
    imprimePreOrdem(arvoreMorse->direita);
  }
}
// //
// // void esvaziaArvore(No* arvore){
// //   if(arvore != NULL){
// //     esvaziaArvore(&(*arvore)->esquerda);
// //     esvaziaArvore(&(*arvore)->direita);
// //     free(arvore);
// //   }
// // }



// fonte slide Raquel - Arvore de Pesquisa Binária
// void Pesquisa(Registro *x, Apontador p) {
//   if(p == NULL) {
//     printf("Registro nao esta presente \n");
//   else if (x->Chave < p->Reg.Chave)
//     Pesquisa(x, p->esquerda);
//   else if (x->Chave > p->Reg.Chave)
//     Pesquisa(x, p->direita);
//   else
//     *x = p->Reg;
// }












// struct no* cria_trie(Registro *reg){
//   struct no* auxiliar = (struct no*) malloc(sizeof(struct no));
//   auxiliar->esquerda = NULL;
//   auxiliar->direita = NULL;
//   auxiliar->registro = reg;
//   if(reg == NULL) fprintf(stderr,"reg null em cria_trie\n");
//   fprintf(stderr, "cria_trie: %s  %s\n", reg->item, reg->chave);
//   return auxiliar;
// }
//
// struct no* separa(struct no* no1, struct no* no2, int p){
//   struct no* novo = cria_trie(NULL);
//
//   fprintf(stderr, "continuando separa!\n");
//   char c1[6];
//   char c2[6];
//
//   strcpy(c1, no1->registro->chave);
//   strcpy(c2, no2->registro->chave);
//
//   if(c1[p] == '.' && c2[p] == '.'){ //
//     novo->esquerda = separa(no1, no2, p+1);
//   }else if(c1[p] == '.' && c2[p] == '-'){/* 0 1 */
//     novo->esquerda = no1; novo->direita = no2;
//   }else if(c1[p] == '-' && c2[p] == '.'){/* 1 0 */
//     novo->direita = no1; novo->esquerda = no2;
//   }else if(c1[p] == '-' && c2[p] == '-'){/* 1 1 */
//     novo->direita = separa(no1, no2, p+1);
//   }
//
//   return novo;
// }
//
// struct no* insereR(struct no* t, Registro *reg, int p){
//   char *chave = reg->chave;
//
//   if(t == NULL)
//     return cria_trie(reg);
//
//   if(t->esquerda == NULL && t->direita == NULL){
//     return separa(cria_trie(reg), t, p);
//   }
//   // if(chave[p] == '\0')
//   // if(p == (int) strlen(chave))
//   //   return separa(cria_trie(reg), t, p);
//
//   if(chave[p] == '.') /* insere sub-árvore esquerda */
//     t->esquerda = insereR(t->esquerda, reg, p+1);
//   else if(chave[p] == '-') /* insere na sub-árvore direita */
//     t->direita = insereR(t->direita, reg, p+1);
//   else{
//     if(t->registro->chave == NULL)
//     // {
//       t->registro = reg;
//     // }
//   }
//
//
//   /* se já inseri os . e - do caractere, então já posso colocar ele na arvore */
//   return t;
// }
//
// void insereNo(struct no** trie, Registro *reg) {
//   fprintf(stderr, "inserindo no: %s %s\n", reg->item , reg->chave);
//   *trie = insereR(*trie, reg, 0);
// }
//
//
//
// Registro* pesquisaRamos(struct no* t, char *chave, int p) {
//   if(t == NULL)
//     return NULL;
//
//   // if(chave[p] == '\0'){
//   //   char *regchave = t->registro->chave;
//   //
//   //   if(strcmp(regchave, chave) == 0)
//   //     return t->registro;
//   //   else
//   //     return NULL;
//   // }
//   //char *regchave = t->registro->chave;
//
//   if(t->esquerda == NULL && t->direita == NULL){
//     if(strcmp(t->registro->chave, chave) == 0)
//       return t->registro;
//     else
//       return NULL;
//   }
//
//   if(chave[p] == '.') /*busca sub-árvore esquerda */
//     return pesquisaRamos(t->esquerda, chave, p+1);
//   else if(chave[p] == '-')/* busca sub-árvore direita */
//     return pesquisaRamos(t->direita, chave, p+1);
//   else{
//     printf("%s %s\n", chave, t->registro->chave);
//     fflush(stdout);
//     if(strcmp(chave, t->registro->chave) == 0)
//       return t->registro;
//     else
//       return NULL;
//   }
//
// }
//
// Registro* pesquisa(struct no* trie, char *chave){
//   return pesquisaRamos(trie, chave, 0);
// }

//
// // void imprimePreOrdem(No* arvoreMorse){
// //   // imprime assim que passa no nó
// //   if(arvoreMorse != NULL){
// //     if(strlen(arvoreMorse->registro->item) > 0){
// //       printf("%s %s\n", arvoreMorse->registro->chave, arvoreMorse->registro->item);
// //       printf("t\n");}
// //     imprimePreOrdem(arvoreMorse->esquerda);
// //     imprimePreOrdem(arvoreMorse->direita);
// //   }
// // }
// //
// // void esvaziaArvore(No* arvore){
// //   if(arvore != NULL){
// //     esvaziaArvore(&(*arvore)->esquerda);
// //     esvaziaArvore(&(*arvore)->direita);
// //     free(arvore);
// //   }
// // }

/* ----       -----           ------          -----         ----- */


// Apontador separa(Apontador no1, Apontador no2, int p){
//   Apontador novo = cria_trie(NULL);
//   char c1[6];   //strcpy(c1, caractere(no1->registro->chave, p));
//   char c2[6];   //strcpy(c2, caractere(no2->registro->chave, p));
//
//   strcpy(c1, no1->registro->chave);
//   strcpy(c2, no2->registro->chave);
//
//   if(c1[p] == '.' && c2[p] == '.'){ // vou ter que trocar isso para comparar CARACTERES
//     novo->esquerda = separa(no1, no2, p+1);
//   }else if(c1[p] == '.' && c2[p] == '-'){/* 0 1 */ // vou ter que trocar isso para comparar CARACTERES
//     novo->esquerda = no1; novo->direita = no2;
//   }else if(c1[p] == '-' && c2[p] == '.'){/* 1 0 */ // vou ter que trocar isso para comparar CARACTERES
//     novo->direita = no1; novo->esquerda = no2;
//   }else if(c1[p] == '-' && c2[p] == '-'){/* 1 1 */ // vou ter que trocar isso para comparar CARACTERES
//     novo->direita = separa(no1, no2, p+1);
//   }
//
//   // if(strcmp(c1, ".\0") == 0 && strcmp(c2, ".\0") == 0){ // vou ter que trocar isso para comparar CARACTERES
//   //   novo->esquerda = separa(no1, no2, p+1);
//   // }else if(strcmp(c1, ".\0") == 0 && strcmp(c2, "-\0") == 0){/* 0 1 */ // vou ter que trocar isso para comparar CARACTERES
//   //   novo->esquerda = no1; novo->direita = no2;
//   // }else if(strcmp(c1, "-\0") == 0 && strcmp(c2, ".\0") == 0){/* 1 0 */ // vou ter que trocar isso para comparar CARACTERES
//   //   novo->direita = no1; novo->esquerda = no2;
//   // }else if(strcmp(c1, "-\0") == 0 && strcmp(c2, "-\0") == 0){/* 1 1 */ // vou ter que trocar isso para comparar CARACTERES
//   //   novo->direita = separa(no1, no2, p+1);
//   // }
//   return novo;
// }
//
// Apontador insereR(Apontador t, Registro *reg, int p){
//   // printf("Teste-");
//   // fflush(stdout);
//   char *chave = reg->chave;      //strcpy(chave, reg->chave);
//   if(t == NULL)
//     return cria_trie(reg);
//   // if(t->esquerda == NULL && t->direita == NULL){// nó folha
//   //   return separa(cria_trie(reg), t, p);
//   // }
//   if(chave[p] == '\0')
//     return separa(cria_trie(reg), t, p);
//
//   // checa se o caractere eh o '.'
//   if(strcmp(caractere(chave, p), ".\0") == 0) /* insere sub-árvore esquerda */
//     t->esquerda = insereR(t->esquerda, reg, p+1);
//   // outra possível(?) implementação
//   // chave[p] == '.'
//   else  /* insere na sub-árvore direita */
//     t->direita = insereR(t->direita, reg, p+1);
//   /* se já inseri os . e - do caractere, então já posso colocar ele na arvore */
//   return t;
// }
//
// void insereNo(Apontador *trie, Registro *reg){
//   *trie = insereR(*trie, reg, 0);
// }
//
// void imprimePreOrdem(Apontador arvoreMorse){
//   // imprime assim que passa no nó
//   if(arvoreMorse != NULL){
//     if(strlen(arvoreMorse->registro->item) > 0){
//       printf("%s %s\n", arvoreMorse->registro->chave, arvoreMorse->registro->item);
//       printf("t\n");}
//     imprimePreOrdem(arvoreMorse->esquerda);
//     imprimePreOrdem(arvoreMorse->direita);
//   }
// }
//
//
// void esvaziaArvore(Apontador *arvore){
//   if(arvore != NULL){
//     esvaziaArvore(&(*arvore)->esquerda);
//     esvaziaArvore(&(*arvore)->direita);
//     free(arvore);
//   }
// }
//
//
//
// char* pesquisaRamos(Apontador t, char *chave, int p){
//   if(t == NULL)
//     return NULL;
//
//   // if(t->esquerda == NULL && t->direita == NULL){
//   //   char regchave = t->registro->chave;
//   //   if(regchave == chave){
//   //     return t->registro;
//   //   }else {
//   //     return NULL;
//   //   }
//   // }
//
//   if(chave[p] == '\0'){
//     char *regchave = t->registro->chave;
//
//     //printf("%s %s\n", t->registro->chave, t->registro->item);
//     // fflush(stdout);
//
//     // strcpy(regchave, t->registro->chave);
//
//     if(strcmp(regchave, chave) == 0){
//       return t->registro->chave;
//     }else {
//       return NULL;
//     }
//   }
//   // vou ter que trocar isso para comparar CARACTERES
//   if(strcmp(caractere(chave, p), ".\0") == 0) /*busca sub-árvore esquerda */
//     return pesquisaRamos(t->esquerda, chave, p+1);
//
//   else /* busca sub-árvore direita */
//     return pesquisaRamos(t->direita, chave, p+1);
//   // printf("TesteTT-");
//   // fflush(stdout);
// }
//
// char* pesquisaArvore(Apontador trie, char *chave){
//   // printf("Teste- ");
//   fflush(stdout);
//   return pesquisaRamos(trie, chave, 0);
// }
