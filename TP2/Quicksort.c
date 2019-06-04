#include "Bibliotecas/Quicksort.h"

/*
	Aqui COMECA as funcoes relacionadas ao QUICKSORT CLASSICO
*/
// 
void Particao(int Esq, int Dir, int *i, int *j, Item *A){
	Item x, w;
	*i = Esq;
	*j = Dir;
	x = A[(*i + *j)/2]; /* obtem o pivo x */
	do{
		while (x.Chave > A[*i].Chave)
			(*i)++;
		while (x.Chave < A[*j].Chave)
			(*j)--;
		if (*i <= *j){
			w = A[*i];
			A[*i] = A[*j];
			A[*j] = w;
			(*i)++;
			(*j)--;
		}
	}while(*i <= *j);
}
//
void Ordena(int Esq, int Dir, Item *A){
	int i, j;
	Particao(Esq, Dir, &i, &j, A);
	if(Esq < j)
		Ordena(Esq, j, A);
	if(i < Dir)
		Ordena(i, Dir, A);
}
//
void QuickSort(Item *A, int n){
	Ordena(0, n-1, A);
}

/*
	Aqui TERMINA as funcoes relacionadas ao QUICKSORT CLASSICO
*/


