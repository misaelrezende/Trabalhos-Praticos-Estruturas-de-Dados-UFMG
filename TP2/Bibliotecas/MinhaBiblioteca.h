#ifndef MINHABIBLIOTECA_H
#define MINHABIBLIOTECA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
	int dir, esq;
} TipoItem;

typedef struct Celula_str *Apontador;

typedef struct Celula_str{
	TipoItem item;
	Apontador Prox;
} Celula;

typedef struct {
	Apontador Fundo, Topo;
	int Tamanho;
} TipoPilha;



typedef struct {
	int Chave;
} Item;

void Insercao(long int*);
void escolheMediana(long int*, long int*);

void gerarVetor(Item*, int, char*, Item*, int);

void imprimeResultados(char*, char*, int, int, int, long int);


/*
	COMECO dos Prototipos de funcoes relacionadas a Pilha
*/
void FPVazia(TipoPilha*);
int Vazia(const TipoPilha*);
void Empilha(TipoItem, TipoPilha*);
int Desempilha(TipoPilha*, TipoItem*);
int Tamanho(const TipoPilha*);
/*
	FIM dos Prototipos de funcoes relacionadas a Pilha
*/
#endif
