#include "Grafo.cpp"
#include <vector>
#include <algorithm>

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

// Função auxiliar para ordenar pelo segundo elemento (custo)
bool OrdenarPorCusto(pair< pair<int,int>, pair<float, bool>> a, pair< pair<int,int>, pair<float, bool>> b){
	return (a.second.first > b.second.first);
}

// Ordena a AGM pelo valor dos custos
vector<pair<pair<int,int>,pair<float,bool>>>* ObterMaioresCustos(float** grafo, int* vertices_raiz, int num_vertices){

	// < <loja1, loja2>, <custo, ocupado?> >
	vector< pair< pair<int,int>, pair<float,bool> > >* agm_ordenada = new vector<pair<pair<int,int>,pair<float,bool>>>;
	for(int i = 1; i < num_vertices; i++){
		agm_ordenada->push_back(
			make_pair(
				make_pair(vertices_raiz[i], i),
				make_pair(grafo[i][vertices_raiz[i]], false)
				)
						  );
	}

	sort(agm_ordenada->begin(), agm_ordenada->end(), OrdenarPorCusto);
	cout<<fixed<<setprecision(3);
	cout<<"Ordenado:"<<endl;
	for(vector<pair< pair<int,int>, pair<float,bool>>>::iterator it = agm_ordenada->begin(); it != agm_ordenada->end(); ++it){
		cout<<it->first.first<<" "<<it->first.second<<" "<<it->second.first<<endl;
	}
	cout<<endl;
	return agm_ordenada;
}

void AlocarDrone(vector< pair<pair<int,int>, pair<float,bool>> >* agm_ordenada, int* drones_alocados, int num_drones, int* lojas_conectadas){
	cout<<"Alocar Drones"<<endl;
	for(vector<pair< pair<int,int>, pair<float,bool>>>::iterator it = agm_ordenada->begin(); it != agm_ordenada->end(); ++it){
		if(it->second.second == false && (*drones_alocados) < num_drones){
			cout<<it->first.first<<" "<<it->first.second<<" "<<it->second.first<<endl;
			it->second.second = true; *lojas_conectadas += 1;
			// if((*drones_alocados) + 1 == num_drones){
			// 	*drones_alocados += 1;
			// 	break;
			// }
			*drones_alocados += 2;
		}
	}
}

void AlocarMoto(vector< pair<pair<int,int>, pair<float,bool>> >* agm_ordenada, float* km_motos, int limite_km_moto, int* lojas_conectadas){
	cout<<"Alocar Motos"<<endl;
	for(vector<pair< pair<int,int>, pair<float,bool>>>::iterator it = agm_ordenada->begin(); it != agm_ordenada->end(); ++it){
		if(it->second.second == false){
			if(limite_km_moto >= it->second.first){
				cout<<it->first.first<<" "<<it->first.second<<" "<<it->second.first<<endl;
				it->second.second = true; *lojas_conectadas += 1;
				*km_motos += it->second.first;
			}
		}
	}
}

void AlocarCaminhao(vector< pair<pair<int,int>, pair<float,bool>> >* agm_ordenada, float* km_caminhoes, int* lojas_conectadas){
	cout<<"Alocar Caminhoes"<<endl;
	for(vector<pair< pair<int,int>, pair<float,bool>>>::iterator it = agm_ordenada->begin(); it != agm_ordenada->end(); ++it){
		if(it->second.second == false){
			cout<<it->first.first<<" "<<it->first.second<<" "<<it->second.first<<endl;
			it->second.second = true; *lojas_conectadas += 1;
			*km_caminhoes += it->second.first;
		}
	}
}

void MinimizarCustoTrajeto(float** grafo, int* vertices_raiz, int num_lojas, int limite_km_moto, int num_drones, int custo_moto, int custo_caminhao){
	cout<<fixed<<setprecision(3);
	if(num_drones == num_lojas){
		cout << 0.000 << " " << 0.000; // Custo zero para motos e caminhões
	}else{
		// Obter maiores custos
		vector< pair<pair<int,int>, pair<float,bool>> >* agm_ordenada;
		agm_ordenada = ObterMaioresCustos(grafo, vertices_raiz, num_lojas);

		int drones_alocados = 0, lojas_conectadas = 0;
		float km_motos = 0, km_caminhoes;

		// Alocar todos drones
		if(num_drones >= 2){
			// for(int i = 0; i < ; i++){
				// agm_ordenada[i]->second->second = true;
			AlocarDrone(agm_ordenada, &drones_alocados, num_drones, &lojas_conectadas);

			// Falta mais lojas para alocar
			if(lojas_conectadas < num_lojas){
				if(custo_moto <= custo_caminhao){
					AlocarMoto(agm_ordenada, &km_motos, limite_km_moto, &lojas_conectadas);
					if(lojas_conectadas < num_lojas)
						AlocarCaminhao(agm_ordenada, &km_caminhoes, &lojas_conectadas);
				}else
					AlocarCaminhao(agm_ordenada, &km_caminhoes, &lojas_conectadas);
			}
			
		}else{
			if(custo_moto <= custo_caminhao){
				AlocarMoto(agm_ordenada, &km_motos, limite_km_moto, &lojas_conectadas);
				if(lojas_conectadas < num_lojas)
					AlocarCaminhao(agm_ordenada, &km_caminhoes, &lojas_conectadas);
			}
			else
				AlocarCaminhao(agm_ordenada, &km_caminhoes, &lojas_conectadas);
		}

		// Imprime custo total da utilização de motos e caminhões
		// cout<<custo_moto*km_motos<<" "<<custo_caminhao*km_caminhoes; // CORRETO
		cout<<endl<<custo_moto*km_motos<<" "<<custo_caminhao*km_caminhoes<<endl; // ERRADO
	}

}
