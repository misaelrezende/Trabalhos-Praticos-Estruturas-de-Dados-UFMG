#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <iostream>
#include <cstring>
using namespace std;

class Cliente{
    private:
        int _id, _idade, _x, _y;
        string _estado_de_origem, _tipo_pgto;
    
    public:
        Cliente();
        Cliente(int, int, string, string, int, int);

        void imprime();
        void setId(int);
        void setIdade(int);
        void setLocalizacao(int, int);
        void setEstado(char*);
        void setTipoPgto(char*);
        ~Cliente();
};

class Loja{
    private:
        int _id, _estoque, _x, _y;

    public:
        Loja();
        Loja(int, int, int, int);

        void imprime();
        void setId(int);
        void setEstoque(int);
        void setLocalizacao(int, int);
        ~Loja();
};

#endif