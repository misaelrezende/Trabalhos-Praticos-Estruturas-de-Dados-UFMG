#include "biblioteca.hpp"

Cliente::Cliente(){}
Cliente::Cliente(int id, int idade, string estado_de_origem, string tipo_pgto, int x, int y){
    this->_id = id;
    this->_idade = idade;
    this->_estado_de_origem = estado_de_origem;
    this->_tipo_pgto = tipo_pgto;
    this->_x = x;
    this->_y = y;
}
void Cliente::imprime(){
    cout << this->_id << " " << this->_idade << " " << this->_estado_de_origem << " " << this->_tipo_pgto << " " << this->_x << " " << this->_y << endl;
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
