#include "MinhaBiblioteca.hpp"

#define INFINITO  100000

MinhaBiblioteca::MinhaBiblioteca(float** grafo, int num_lojas, int limite_km_moto, int num_drones, int custo_moto, int custo_caminhao){
	_grafo = grafo;
	_num_lojas = num_lojas;
	_limite_km_moto = limite_km_moto;
	_num_drones = num_drones;
	_custo_moto = custo_moto;
	_custo_caminhao = custo_caminhao;
}

// Encontra o vértice com menor valor de chave, do set de vértices fora da AGM
int MinhaBiblioteca::EncontrarMenorPeso(float* chave, bool* corte_agm){
	// Inicializa o menor valor
	float menor = INFINITO;
	int menor_indice;

	for(int v = 0; v < _num_lojas; v++){
		if(corte_agm[v] == false && chave[v] < menor){
			menor = chave[v];
			menor_indice = v;
		}
	}
	return menor_indice;
}

// Encontra a árvore geradora mínima (AGM) com menor custo
void MinhaBiblioteca::AlgoritmoPrim(){
	// Armazena vertices raiz da AGM a ser construída
	int* vertices_raiz = new int[_num_lojas];
	// Valores chave para guardar a aresta de menor peso em um corte
	float chave[_num_lojas];
	// Conjunto de vértices incluídos na AGM
	bool corte_agm[_num_lojas];

	for(int i = 0; i < _num_lojas; i++){
		// Inicializa todas chaves para infinito
		chave[i] = INFINITO,
		// Conjunto de vertices na AGM começa vazio
		corte_agm[i] = false;
	}

	// Inicialize com um vértice arbitrário
	// Vamos escolher o vértice 0s
	chave[0] = 0;
	vertices_raiz[0] = -1;

	for(int i = 0; i < _num_lojas - 1; i++){
		int m = EncontrarMenorPeso(chave, corte_agm);

		// Adicione o vértice escolhido ao set da AGM
		corte_agm[m] = true;

		// Atualize chave/valor e índice vertices_raiz dos vértices adj ao vértice escolhido
		// Considere apenas vértices fora da AGM
		for(int v = 0; v < _num_lojas; v++)
			// grafo[m][v] é !=0 apenas para vértices adjacentes de m
			// corte_agm[v] é falso para vertices fora da AGM
			// Atualize a chave apenas se grafo[m][v] é menor que chave[v]
			if(_grafo[m][v] && corte_agm[v] == false && _grafo[m][v] < chave[v]){
				vertices_raiz[v] = m;
				chave[v] = _grafo[m][v];
			}
	}

	_vertices_raiz_agm = vertices_raiz;
}

// Função auxiliar para ordenar pelo segundo elemento (custo)
bool OrdenarPorCusto(pair< pair<int,int>, pair<float, bool>> a, pair< pair<int,int>, pair<float, bool>> b){
	return (a.second.first > b.second.first);
}

// Ordena a AGM pelo valor dos custos
void MinhaBiblioteca::ObterMaioresCustos(){

	// < <loja1, loja2>, <custo, ocupado?> >
	vector< pair< pair<int,int>, pair<float,bool> > >* agm_ordenada = new vector<pair<pair<int,int>,pair<float,bool>>>;
	for(int i = 1; i < _num_lojas; i++){
		agm_ordenada->push_back(
			make_pair(
				make_pair(_vertices_raiz_agm[i], i),
				make_pair(_grafo[i][_vertices_raiz_agm[i]], false)
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

	_agm_ordenada = agm_ordenada;
}

void MinhaBiblioteca::AlocarDrone(int* drones_alocados, int* lojas_conectadas){
	cout<<"Alocar Drones"<<endl;
	for(vector<pair< pair<int,int>, pair<float,bool>>>::iterator it = _agm_ordenada->begin(); it != _agm_ordenada->end(); ++it){
		if(it->second.second == false && *drones_alocados < _num_drones){
			cout<<it->first.first<<" "<<it->first.second<<" "<<it->second.first<<endl;
			it->second.second = true; (*lojas_conectadas) += 1;
			// if((*drones_alocados) + 1 == num_drones){
			// 	*drones_alocados += 1;
			// 	break;
			// }
			(*drones_alocados) += 2;
		}
	}
}

void MinhaBiblioteca::AlocarMoto(float* km_motos, int* lojas_conectadas){
	cout<<"Alocar Motos"<<endl;
	for(vector<pair< pair<int,int>, pair<float,bool>>>::iterator it = _agm_ordenada->begin(); it != _agm_ordenada->end(); ++it){
		if(it->second.second == false){
			if(_limite_km_moto >= it->second.first){
				cout<<it->first.first<<" "<<it->first.second<<" "<<it->second.first<<endl;
				it->second.second = true; (*lojas_conectadas) += 1;
				(*km_motos) += it->second.first;
			}
		}
	}
}

void MinhaBiblioteca::AlocarCaminhao(float* km_caminhoes, int* lojas_conectadas){
	cout<<"Alocar Caminhoes"<<endl;
	for(vector<pair< pair<int,int>, pair<float,bool>>>::iterator it = _agm_ordenada->begin(); it != _agm_ordenada->end(); ++it){
		if(it->second.second == false){
			cout<<it->first.first<<" "<<it->first.second<<" "<<it->second.first<<endl;
			it->second.second = true; (*lojas_conectadas) += 1;
			(*km_caminhoes) += it->second.first;
		}
	}
}

void MinhaBiblioteca::MinimizarCustoTrajeto(){
	cout<<fixed<<setprecision(3);
	if(_num_drones == _num_lojas){
		cout << 0.000 << " " << 0.000; // Custo zero para motos e caminhões
	}else{
		// Obter maiores custos
		ObterMaioresCustos();

		int drones_alocados = 0, lojas_conectadas = 0;
		float km_motos = 0, km_caminhoes = 0;

		// Alocar todos drones
		if(_num_drones >= 2){
			// for(int i = 0; i < ; i++){
				// agm_ordenada[i]->second->second = true;
			AlocarDrone(&drones_alocados, &lojas_conectadas);

			// Falta mais lojas para alocar
			if(lojas_conectadas < _num_lojas){
				if(_custo_moto <= _custo_caminhao){
					AlocarMoto(&km_motos, &lojas_conectadas);
					if(lojas_conectadas < _num_lojas)
						AlocarCaminhao(&km_caminhoes, &lojas_conectadas);
				}else
					AlocarCaminhao(&km_caminhoes, &lojas_conectadas);
			}
			
		}else{
			if(_custo_moto <= _custo_caminhao){
				AlocarMoto(&km_motos, &lojas_conectadas);
				if(lojas_conectadas < _num_lojas)
					AlocarCaminhao(&km_caminhoes, &lojas_conectadas);
			}
			else
				AlocarCaminhao(&km_caminhoes, &lojas_conectadas);
		}

		// Imprime custo total da utilização de motos e caminhões
		// cout<<_custo_moto*km_motos<<" "<<_custo_caminhao*km_caminhoes; // CORRETO
		cout<<endl<<_custo_moto*km_motos<<" "<<_custo_caminhao*km_caminhoes<<endl; // ERRADO
	}

}

MinhaBiblioteca::~MinhaBiblioteca(){}
