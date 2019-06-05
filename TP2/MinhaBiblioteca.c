#include "Bibliotecas/MinhaBiblioteca.h"


// preenche o vetor de acordo com a ordenacao escolhida
void gerarVetor(Item *Itens, int tamanho, char *ordemVetor){
	char *Ale = {"Ale\0"}, *OrdC = {"OrdC\0"};
	int i;

	if(strcmp(Ale, ordemVetor) == 0){ // ordem aleatoria
		srand(time(NULL));
		for(i = 0; i < tamanho; i++)
			Itens[i].Chave = rand() % tamanho;
	}else if(strcmp(OrdC, ordemVetor) == 0){ // ordem crescente
		for(i = 0; i < tamanho; i++)
			Itens[i].Chave = i;
	}else{ // ordem decresente
		for(i = tamanho - 1; i >= 0; i--)
			Itens[i].Chave = i;
	}
}

void imprimeResultados(char *variacao, char *tipo, int tamanho,
											int mediaQtdeComparacao, int mediaqtdeMovimentacao,
											int parametroOpcional){
	if(parametroOpcional == 0)
		printf("%s %s %d %d %d\n", variacao, tipo, tamanho, mediaQtdeComparacao, mediaqtdeMovimentacao);
}