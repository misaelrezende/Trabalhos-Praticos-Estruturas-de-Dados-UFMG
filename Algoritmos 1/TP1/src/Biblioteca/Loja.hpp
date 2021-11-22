#ifndef LOJA_H
#define LOJA_H

#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

class Loja{
    private:
        int _id, _estoque, _x, _y;
        vector<pair<int, float>> _lista_prioridade;

    public:
        Loja();
        Loja(int, int, int, int);

        void Imprimir();
        void setId(int);
        void setEstoque(int);
        void setLocalizacao(int, int);
        pair<int,int> GetLocalizacao();
        void CriarListaPrioridade(vector<pair<int, float>>);
        ~Loja();
};

#endif