#include "Bibliotecas/MinhaBiblioteca.h"


// preenche o vetor de acordo com a ordenacao escolhida
void gerarVetor(Item *Itens, int tamanho, char *tipo, Item *Auxiliar,
				int parametroOpcional){
	char *Ale = {"Ale\0"}, *OrdC = {"OrdC\0"};
	int i;

	if(strcmp(Ale, tipo) == 0){ // ordem aleatoria
		for(i = 0; i < tamanho; i++){
			Itens[i].Chave = rand() % tamanho;
			if(parametroOpcional == 1)
				Auxiliar[i].Chave = Itens[i].Chave;
		}
	}else if(strcmp(OrdC, tipo) == 0){ // ordem crescente
		for(i = 0; i < tamanho; i++){
			Itens[i].Chave = i;
			if(parametroOpcional == 1)
				Auxiliar[i].Chave = Itens[i].Chave;
		}
	}else{ // ordem decresente
		int aux;
		for(i = 0, aux = tamanho - 1; i < tamanho; i++, aux--){
			Itens[i].Chave = aux;
			if(parametroOpcional == 1)
				Auxiliar[i].Chave = Itens[i].Chave;
		}
	}
}

void imprimeResultados(char *variacao, char *tipo, int tamanho,
											int mediaQtdeComparacao, int mediaqtdeMovimentacao){
		printf("%s %s %d %d %d\n", variacao, tipo, tamanho, mediaQtdeComparacao, mediaqtdeMovimentacao);
}