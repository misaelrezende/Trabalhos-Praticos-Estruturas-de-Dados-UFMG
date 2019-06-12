#include "Bibliotecas/Quicksort.h"

/*
	Aqui COMECA as funcoes relacionadas ao QUICKSORT CLASSICO
*/
// 
void Particao(int Esq, int Dir, int *i, int *j, Item *A, int *qtdeComparacao, int *qtdeMovimentacao){
	Item x, w;
	*i = Esq;
	*j = Dir;
	x = A[(*i + *j)/2]; /* obtem o pivo x */

	do{
		while (x.Chave > A[*i].Chave){
			(*i)++;
			(*qtdeComparacao)++;
		}
		(*qtdeComparacao)++; // adicao da comparacao do laco

		while (x.Chave < A[*j].Chave){
			(*j)--;
			(*qtdeComparacao)++;
		}
		(*qtdeComparacao)++; // adicao da comparacao do laco
		
		if (*i <= *j){
			w = A[*i];
			A[*i] = A[*j];
			A[*j] = w;
			(*qtdeMovimentacao)++;
			(*i)++;
			(*j)--;
		}
	}while(*i <= *j);
}
//
void Ordena(int Esq, int Dir, Item *A, int *qtdeComparacao, int *qtdeMovimentacao){
	int i, j;
	Particao(Esq, Dir, &i, &j, A, qtdeComparacao, qtdeMovimentacao);
	if(Esq < j)
		Ordena(Esq, j, A, qtdeComparacao, qtdeMovimentacao);
	if(i < Dir)
		Ordena(i, Dir, A, qtdeComparacao, qtdeMovimentacao);
}
//
void QuickSort(Item *A, int n, int *qtdeComparacao, int *qtdeMovimentacao){
	Ordena(0, n-1, A, qtdeComparacao, qtdeMovimentacao);
}

/*
	Aqui TERMINA as funcoes relacionadas ao QUICKSORT CLASSICO
*/


