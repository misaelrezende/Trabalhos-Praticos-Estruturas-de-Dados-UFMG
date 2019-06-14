#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "MinhaBiblioteca.h"

/*
	COMECO dos Prototipos de funcoes relacionadas ao QUICKSORT CLASSICO
	e ao QUICKSORT MEDIANA DE TRES
*/
void Particao(int, int, int*, int*, Item*, int*, int*, char*);
void Ordena(int, int, Item*, int*, int*, char*);
void QuickSort(Item*, int, int*, int*, char*);
/*
	FIM dos Prototipos de funcoes relacionadas ao QUICKSORT CLASSICO
	e ao QUICKSORT MEDIANA DE TRES
*/

/* -----------------------//////////--------------------------- */

/*
	COMECO dos Prototipos de funcoes relacionadas ao QUICKSORT PRIMEIRO ELEMENTO
*/
int ParticaoPE(int, int, Item*, int*, int*);
void QuickSortPrimeiroElemento(Item*, int, int, int*, int*);
/*
	FIM dos Prototipos de funcoes relacionadas ao QUICKSORT PRIMEIRO ELEMENTO
*/

/* -----------------------//////////--------------------------- */

/*
	COMECO dos Prototipos de funcoes relacionadas ao QUICKSORT
*/

#endif