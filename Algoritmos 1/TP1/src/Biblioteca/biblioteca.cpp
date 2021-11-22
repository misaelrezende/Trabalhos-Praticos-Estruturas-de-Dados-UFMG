#include "biblioteca.hpp"
// Função auxiliar para ordenar pelo segundo elemento
bool sortbysec(const pair<int,float> &a, const pair<int,float> &b){
    return (a.second < b.second);
}

Cliente::Cliente(){}
Cliente::Cliente(int id, int idade, string estado_de_origem, string tipo_pgto, int x, int y){
    this->_id = id;
    this->_idade = idade;
    this->_estado_de_origem = estado_de_origem;
    this->_tipo_pgto = tipo_pgto;
    this->_x = x;
    this->_y = y;

    CalcularTicket();
}
void Cliente::Imprimir(){
    // cout << this->_id << " " << this->_idade << " " << this->_estado_de_origem << " " << this->_tipo_pgto << " " << this->_x << " " << this->_y << " ticket: " << this->_ticket << endl;
    cout << this->_id << ":";
    for(vector<int>::iterator it = this->_lista_prioridade_distancias.begin(); it != _lista_prioridade_distancias.end(); ++it)
        cout << " " << *it;
    cout << endl;
}
int Cliente::getScoreEstado(string estado){
    if(estado.compare("MG\0") == 0)
        return 0;
    else if(estado.compare("PR\0") == 0)
        return 10;
    else if(estado.compare("SP\0") == 0)
        return 20;
    else if(estado.compare("SC\0") == 0)
        return 30;
    else if(estado.compare("RJ\0") == 0)
        return 40;
    else if(estado.compare("RN\0") == 0)
        return 50;
    else // (estado.compare("RS\0") == 0)
        return 60;
}
int Cliente::getScoreTipoPagamento(string pgto){
    if(pgto.compare("DINHEIRO\0") == 0)
        return 1;
    else if(pgto.compare("DEBITO\0") == 0)
        return 2;
    else // (pgto.compare("CREDITO\0") == 0)
        return 3;
}
float Cliente::GetTicket(){
    return this->_ticket;
}
void Cliente::CalcularTicket(){
    this->_ticket = ( abs(60 - this->_idade) + getScoreEstado(this->_estado_de_origem) ) / float(getScoreTipoPagamento(this->_tipo_pgto));
}
int Cliente::CalcularDistancia(pair<int,int> localizacao){
    int distancia = max( abs(this->_x - localizacao.first), abs(this->_y - localizacao.second) ) - 1;
    return distancia;
}
void Cliente::CriarListaPrioridade(vector<pair<int,int>> lista){   
    vector<pair<int,int>> lista_auxiliar;
    int i = 0;
    for(vector<pair<int,int>>::iterator it = lista.begin(); it != lista.end(); ++it, i++)
        lista_auxiliar.push_back( make_pair(i, CalcularDistancia(*it)) );

    stable_sort(lista_auxiliar.begin(), lista_auxiliar.end(), sortbysec);

    for(vector<pair<int,int>>::iterator it = lista_auxiliar.begin(); it != lista_auxiliar.end(); ++it)
        this->_lista_prioridade_distancias.push_back(it->first);
}
Cliente::~Cliente(){}


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
    stable_sort(lista.begin(), lista.end(), sortbysec);
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
