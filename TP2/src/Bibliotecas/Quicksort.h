#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "MinhaBiblioteca.h"

/*
	COMECO dos Prototipos de funcoes relacionadas ao QUICKSORT CLASSICO
	e ao QUICKSORT MEDIANA DE TRES
*/
// O(n log n)
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
// O(n^2)
int ParticaoPE(int, int, Item*, int*, int*);
void QuickSortPrimeiroElemento(Item*, int, int, int*, int*);
/*
	FIM dos Prototipos de funcoes relacionadas ao QUICKSORT PRIMEIRO ELEMENTO
*/

/* -----------------------//////////--------------------------- */

/*
	COMECO do Prototipo de funcao relacionada ao QUICKSORT NAO RECURSIVO
*/
// O (n log n) caso medio e O(n^2) pior caso
void QuickSortNaoRecursivo(Item*, int, int*, int*);
/*
	FIM do Prototipo de funcao relacionada ao QUICKSORT NAO RECURSIVO
*/
#endif