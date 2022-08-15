#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
using namespace std;

class Grafo{
    private:
        int _vertices;
        int _fileira, _qtde_fileira;
        int** _grafo;

    public:
        Grafo(int,int,int**);
        void Imprimir();
        ~Grafo();
};

#endif