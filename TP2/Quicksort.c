#include "Bibliotecas/Quicksort.h"
#define Troca(A, B) {Item c = A; A = B; B = c; }


/*
	Aqui COMECA as funcoes relacionadas ao QUICKSORT CLASSICO 
	e ao QUICKSORT MEDIANA DE TRES
*/
// ** referencia ** (slide Raquel)
void Particao(int Esq, int Dir, int *i, int *j, Item *A, int *qtdeComparacao, int *qtdeMovimentacao, char *variacao){
	Item pivo, auxiliar;
	char QC[3] = {"QC\0"};
	*i = Esq;
	*j = Dir;

	// se QuickSort Clássico
	if(strcmp(variacao, QC) == 0){
		pivo = A[(*i + *j)/2]; // obtem o pivo
	}
	// se QuickSort Mediana de Tres
	else{
		int meio = (Esq + Dir) / 2;
		if(A[meio].Chave < A[Dir].Chave)
		  Troca(A[Dir], A[meio]);
		if(A[Esq].Chave < A[Dir].Chave)
		  Troca(A[Dir], A[Esq]);
		if(A[meio].Chave < A[Esq].Chave)
		  Troca(A[meio], A[Esq]);
		pivo = A[Esq];
	}

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
void Ordena(int Esq, int Dir, Item *A, int *qtdeComparacao, int *qtdeMovimentacao, char *variacao){
	int i, j;
	Particao(Esq, Dir, &i, &j, A, qtdeComparacao, qtdeMovimentacao, variacao);
	if(Esq < j)
		Ordena(Esq, j, A, qtdeComparacao, qtdeMovimentacao, variacao);
	if(i < Dir)
		Ordena(i, Dir, A, qtdeComparacao, qtdeMovimentacao, variacao);
}
// ** referencia ** (slide Raquel)
// O(n log n)
void QuickSort(Item *A, int n, int *qtdeComparacao, int *qtdeMovimentacao, char *variacao){
	Ordena(0, n-1, A, qtdeComparacao, qtdeMovimentacao, variacao);
}
/*
	Aqui TERMINA as funcoes relacionadas ao QUICKSORT CLASSICO
	e ao QUICKSORT MEDIANA DE TRES
*/



/* -----------------------//////////--------------------------- */



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



/* -----------------------//////////--------------------------- */



