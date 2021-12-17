#include "Grafo.hpp"

#define INFINITO  100000

// Encontra o vértice com menor valor de chave, do set de vértices fora da AGM
int EncontrarMenorPeso(float* chave, bool* corte_agm, int num_vertices){
	// Inicializa o menor valor
	float menor = INFINITO;
	int menor_indice;

	for(int v = 0; v < num_vertices; v++){
		if(corte_agm[v] == false && chave[v] < menor){
			menor = chave[v];
			menor_indice = v;
		}
	}
	return menor_indice;
}

// Encontra a árvore geradora mínima (AGM) com menor custo
int* AlgoritmoPrim(float** grafo, int num_vertices){
	// Armazena vertices raiz da AGM a ser construída
	int* vertices_raiz =new int[num_vertices];
	// int vertices_raiz[num_vertices];
	// Valores chave para guardar a aresta de menor peso em um corte
	float chave[num_vertices];
	// Conjunto de vértices incluídos na AGM
	bool corte_agm[num_vertices];

	for(int i = 0; i < num_vertices; i++){
		// Inicializa todas chaves para infinito
		chave[i] = INFINITO,
		// Conjunto de vertices na AGM começa vazio
		corte_agm[i] = false;
	}

	// Inicialize com um vértice arbitrário
	// Vamos escolher o vértice 0s
	chave[0] = 0;
	vertices_raiz[0] = -1;

	for(int i = 0; i < num_vertices - 1; i++){
		int m = EncontrarMenorPeso(chave, corte_agm, num_vertices);

		// Adicione o vértice escolhido ao set da AGM
		corte_agm[m] = true;

		// Atualize chave/valor e índice vertices_raiz dos vértices adj ao vértice escolhido
		// Considere apenas vértices fora da AGM
		for(int v = 0; v < num_vertices; v++)
			// grafo[m][v] é !=0 apenas para vértices adjacentes de m
			// corte_agm[v] é falso para vertices fora da AGM
			// Atualize a chave apenas se grafo[m][v] é menor que chave[v]
			if(grafo[m][v] && corte_agm[v] == false && grafo[m][v] < chave[v]){
				vertices_raiz[v] = m;
				chave[v] = grafo[m][v];
			}
	}

	return vertices_raiz;
}

/*
    # Depois de encontrar uma AGM:
    - Checar se é possível percorrer tudo com drones
        - Se não, setar os maiores caminhos aos drones
        - Procurar os menores caminhos para motos e caminhões
*/