#ifndef MINHABIBLIOTECA_H
#define MINHABIBLIOTECA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
	int Chave;
} Item;


void gerarVetor(Item*, int, char*);

void imprimeResultados(char*, char*, int, int, int, int);

#endif

