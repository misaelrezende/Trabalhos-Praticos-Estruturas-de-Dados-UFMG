#include "Cliente.hpp"

// Função auxiliar para ordenar pelo segundo elemento
bool Clientesortbysec(const pair<int,float> &a, const pair<int,float> &b){
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
void Cliente::CriarListaPrioridade(vector<pair<int,pair<int, int>>> lista){   
    vector<pair<int,int>> lista_auxiliar;
    for(vector<pair<int,pair<int, int>>>::iterator it = lista.begin(); it != lista.end(); ++it)
        lista_auxiliar.push_back( make_pair(it->first, CalcularDistancia(it->second)) );

    stable_sort(lista_auxiliar.begin(), lista_auxiliar.end(), Clientesortbysec);

    for(vector<pair<int,int>>::iterator it = lista_auxiliar.begin(); it != lista_auxiliar.end(); ++it)
        this->_lista_prioridade_distancias.push_back(it->first);
}

int Cliente::GetClienteAgendado(){
    return this->_cliente_agendado;
}

void Cliente::SetClienteAgendado(int id){
    this->_cliente_agendado = id;
}

Cliente::~Cliente(){}