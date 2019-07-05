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

Apontador criaNo();

void Insere(Registro atual, Apontador no, int posicao);

void imprimePreOrdem(Apontador arvoreMorse);

// Apontador criaNo(Registro*);

// struct no* separa(struct no* no1, struct no* no2, int p);
// struct no* insereR(struct no* t, Registro *reg, int p);
// void insereNo(struct no** trie, Registro *reg);
//
// Registro* pesquisaRamos(struct no* t, char *chave, int p);
// Registro* pesquisa(struct no* trie, char *chave);

// void esvaziaArvore(Apontador*);

#endif
