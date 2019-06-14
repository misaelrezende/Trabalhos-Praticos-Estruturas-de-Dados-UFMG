#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "MinhaBiblioteca.h"

/*
	COMECO dos Prototipos de funcoes relacionadas ao QUICKSORT CLASSICO
*/
void Particao(int, int, int*, int*, Item*, int*, int*);

void Ordena(int, int, Item*, int*, int*);

void QuickSort(Item*, int, int*, int*);
/*
	FIM dos Prototipos de funcoes relacionadas ao QUICKSORT CLASSICO
*/

/*
	COMECO dos Prototipos de funcoes relacionadas ao QUICKSORT PRIMEIRO ELEMENTO
*/
int ParticaoPE(int, int, Item*, int*, int*);
void QuickSortPrimeiroElemento(Item*, int, int, int*, int*);
/*
	FIM dos Prototipos de funcoes relacionadas ao QUICKSORT PRIMEIRO ELEMENTO
*/

#endif