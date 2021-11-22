#include "Loja.hpp"

// Função auxiliar para ordenar pelo segundo elemento
bool Lojasortbysec(const pair<int,float> &a, const pair<int,float> &b){
    return (a.second < b.second);
}

Loja::Loja(/* args */){}

Loja::Loja(int id, int estoque, int x, int y){
    this->_id = id;
    this->_estoque = estoque;
    this->_x = x;
    this->_y = y;
}
void Loja::Imprimir(){
    // cout << this->_id << " " << this->_estoque << " " << this->_x << " " << this->_y << endl;
    cout << this->_id;
    for (vector<pair<int, float>>::iterator it = this->_lista_prioridade.begin(); it != this->_lista_prioridade.end(); ++it){
        cout << " " << it->first;
    }
    cout << endl;
}

// void ordenarPorId(pair<int,float> &it, pair<int,float> aux){
//     pair<int,float> temp = it;
//     it = aux;
//     aux = temp;
// }

void Loja::CriarListaPrioridade(vector<pair<int, float>> lista){
    stable_sort(lista.begin(), lista.end(), Lojasortbysec);
    // pair<int, float> anterior = lista[0];
    // for (vector<pair<int, float>>::iterator it = lista.begin(); it != lista.end(); ++it){
    //     if(it->second == anterior.second){
    //         if(it->first > anterior.first){
    //             ordenarPorId(*it, anterior);
    //         }
    //     }
    // }
    // Faz o desempate por ID
    // for(int tamanho = lista.size(), i = 1; i < tamanho; i++){
    //     if(lista[i].second == anterior.second)
    //         if(lista[i].first > anterior.first){
    //             pair<int, float> temp = lista[i];
    //             lista[i] = anterior;
    //             lista[i-1] = temp;
    //         }
    //     anterior = lista[i];
    // }
    
    this->_lista_prioridade = lista;
}

pair<int,int> Loja::GetLocalizacao(){
    return make_pair(_x, _y);
}

Loja::~Loja(){}