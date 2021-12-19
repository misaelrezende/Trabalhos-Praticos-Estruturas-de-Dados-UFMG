#ifndef MINHABIBLIOTECA_H
#define MINHABIBLIOTECA_H

#include "Grafo.cpp"
#include <vector>
#include <algorithm>

class MinhaBiblioteca{
    private:
        float** _grafo;
        int _num_lojas, _limite_km_moto, _num_drones, _custo_moto, _custo_caminhao;
    public:
        MinhaBiblioteca(float**,int,int,int,int,int);
        ~MinhaBiblioteca();
};

#endif
