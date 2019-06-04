#ifndef QUICKSORT_H
#define QUICKSORT_H

typedef struct {
	int Chave;
} Item;

/*
	COMECO dos Prototipos de funcoes relacionadas ao QUICKSORT CLASSICO
*/
void Particao(int, int, int*, int*, Item*);

void Ordena(int, int, Item*);

void QuickSort(Item*, int);
/*
	FIM dos Prototipos de funcoes relacionadas ao QUICKSORT CLASSICO
*/



#endif