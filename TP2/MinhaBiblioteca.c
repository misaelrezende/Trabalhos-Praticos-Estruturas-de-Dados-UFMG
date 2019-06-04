#include "Bibliotecas/MinhaBiblioteca.h"


// preenche o vetor de acordo com a ordenacao escolhida
void gerarVetor(int *vetorEntrada, int tamanho, char *ordemVetor){
	char *Ale = {"Ale\0"}, *OrdC = {"OrdC\0"};
	int i;

	if(strcmp(Ale, ordemVetor) == 0){ // ordem aleatoria
		srand(time(NULL));
		for(i = 0; i < tamanho; i++)
			vetorEntrada[i] = rand();
	}else if(strcmp(OrdC, ordemVetor) == 0){ // ordem crescente
		for(i = 0; i < tamanho; i++)
			vetorEntrada[i] = i;
	}else{ // ordem decresente
		for(i = tamanho - 1; i >= 0; i--)
			vetorEntrada[i] = i;
	}
}