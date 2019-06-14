#include "Bibliotecas/Quicksort.h"

/*
	Aqui COMECA as funcoes relacionadas ao QUICKSORT CLASSICO
*/
// ** referencia ** (slide Raquel)
void Particao(int Esq, int Dir, int *i, int *j, Item *A, int *qtdeComparacao, int *qtdeMovimentacao){
	Item pivo, auxiliar;
	*i = Esq;
	*j = Dir;
	pivo = A[(*i + *j)/2]; // obtem o pivo

	do{
		while (pivo.Chave > A[*i].Chave){
			(*i)++;
			(*qtdeComparacao)++;
		}
		(*qtdeComparacao)++; // adicao da comparacao do laco

		while (pivo.Chave < A[*j].Chave){
			(*j)--;
			(*qtdeComparacao)++;
		}
		(*qtdeComparacao)++; // adicao da comparacao do laco
		
		if (*i <= *j){
			auxiliar = A[*i];
			A[*i] = A[*j];
			A[*j] = auxiliar;
			(*qtdeMovimentacao)++;
			(*i)++;
			(*j)--;
		}
	}while(*i <= *j);
}
// ** referencia ** (slide Raquel)
void Ordena(int Esq, int Dir, Item *A, int *qtdeComparacao, int *qtdeMovimentacao){
	int i, j;
	Particao(Esq, Dir, &i, &j, A, qtdeComparacao, qtdeMovimentacao);
	if(Esq < j)
		Ordena(Esq, j, A, qtdeComparacao, qtdeMovimentacao);
	if(i < Dir)
		Ordena(i, Dir, A, qtdeComparacao, qtdeMovimentacao);
}
// ** referencia ** (slide Raquel)
// O(n log n)
void QuickSort(Item *A, int n, int *qtdeComparacao, int *qtdeMovimentacao){
	Ordena(0, n-1, A, qtdeComparacao, qtdeMovimentacao);
}

/*
	Aqui TERMINA as funcoes relacionadas ao QUICKSORT CLASSICO
*/

/*
	Aqui COMECA as funcoes relacionadas ao QUICKSORT PRIMEIRO ELEMENTO
*/
int ParticaoPE(int Esq, int Dir, Item *A, int *qtdeComparacao, int *qtdeMovimentacao){
	Item pivo, auxiliar;
	pivo = A[Esq]; // obtem o pivo como o primeiro elemento do vetor

	do{
		while(pivo.Chave > A[Esq].Chave){
			Esq++;
			(*qtdeComparacao)++;
		}
		(*qtdeComparacao)++; // adicao da comparacao do laco

		while(pivo.Chave < A[Dir].Chave){
			Dir--;
			(*qtdeComparacao)++;
		}
		(*qtdeComparacao)++; // adicao da comparacao do laco
		
		if(Esq <= Dir){
			auxiliar = A[Esq];
			A[Esq] = A[Dir];
			A[Dir] = auxiliar;
			(*qtdeMovimentacao)++;
			Esq++;
			Dir--;
		}
	}while(Esq <= Dir);
	return Esq;
}
// ** referencia de ajuda**  https://stackoverflow.com/a/51284766
// O(n^2)
void QuickSortPrimeiroElemento(Item *A, int esq, int dir, int *qtdeComparacao, int *qtdeMovimentacao){
	//Ordena(0, n-1, A, qtdeComparacao, qtdeMovimentacao);
	int auxiliar = ParticaoPE(esq, dir, A, qtdeComparacao, qtdeMovimentacao);
	if(esq < auxiliar - 1){
    QuickSortPrimeiroElemento(A, esq, auxiliar - 1, qtdeComparacao, qtdeMovimentacao);
  }
  if(dir > auxiliar){
    QuickSortPrimeiroElemento(A, auxiliar, dir, qtdeComparacao, qtdeMovimentacao);
  }
}

/*
	Aqui TERMINA as funcoes relacionadas ao QUICKSORT PRIMEIRO ELEMENTO
*/