#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <iostream>
using namespace std;

class Cliente{
    private:
        int id, idade, x, y;
        char estado_de_origem[2], tipo_pgto[8];
    
    public:
        void setId(int);
        void setIdade(int);
        void setLocalizacao(int, int);
        void setEstado(char*);
        void setTipoPgto(char*);    
};

class Loja{
    private:
        int _id, _estoque, _x, _y;

    public:
        Loja();
        Loja(int, int, int, int);
        void setId(int);
        void setEstoque(int);
        void setLocalizacao(int, int);
};

#endif