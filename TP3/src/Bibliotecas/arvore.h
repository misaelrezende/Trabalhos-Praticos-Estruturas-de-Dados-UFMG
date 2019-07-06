#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
  // simbolo armazena um simbolo do codigo morse ( '.' ou '-' )
  char simbolo, caractere[2], codigoMorse[6];
} Registro;

typedef struct no *Apontador;

typedef struct no{
  Apontador esquerda;
  Apontador direita;
  Registro registro;
} No;


Apontador inicializaArvore(Apontador);
Apontador criaNo();

void Insere(Registro, Apontador, int);

void imprimePreOrdem(Apontador);
void esvaziaArvore(Apontador);

// Registro* pesquisaRamos(struct no* t, char *chave, int p);
// Registro* pesquisa(struct no* trie, char *chave);

#endif
