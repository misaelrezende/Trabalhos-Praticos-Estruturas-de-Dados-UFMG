#include "biblioteca.hpp"

Cliente::Cliente(){}
Cliente::Cliente(int id, int idade, string estado_de_origem, string tipo_pgto, int x, int y){
    this->_id = id;
    this->_idade = idade;
    this->_estado_de_origem = estado_de_origem;
    this->_tipo_pgto = tipo_pgto;
    this->_x = x;
    this->_y = y;

    calculaTicket();
}
void Cliente::imprime(){
    cout << this->_id << " " << this->_idade << " " << this->_estado_de_origem << " " << this->_tipo_pgto << " " << this->_x << " " << this->_y << "ticket: " << this->_ticket << endl;
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
void Cliente::calculaTicket(){
    this->_ticket = ( abs(60 - this->_idade) + getScoreEstado(this->_estado_de_origem) ) / getScoreTipoPagamento(this->_tipo_pgto);
}
Cliente::~Cliente(){}


Loja::Loja(/* args */){}

Loja::Loja(int id, int estoque, int x, int y){
    this->_id = id;
    this->_estoque = estoque;
    this->_x = x;
    this->_y = y;
}
void Loja::imprime(){
    cout << this->_id << " " << this->_estoque << " " << this->_x << " " << this->_y << endl;
}

Loja::~Loja(){}
