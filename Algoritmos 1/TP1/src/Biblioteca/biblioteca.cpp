#include "biblioteca.hpp"

class Cliente{
    private:

    public:
    Cliente();
    ~Cliente();
};

Cliente::Cliente(){}
Cliente::~Cliente(){}


Loja::Loja(/* args */){}

Loja::Loja(int id, int estoque, int x, int y){
    this->_id = id;
    this->_estoque = estoque;
    this->_x = x;
    this->_y = y;
}

Loja::~Loja(){}
