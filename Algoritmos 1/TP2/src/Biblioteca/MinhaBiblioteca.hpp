#ifndef MINHABIBLIOTECA_H
#define MINHABIBLIOTECA_H

#include "Grafo.cpp"
#include <vector>
#include <algorithm>

class MinhaBiblioteca{
    private:
        float** _grafo;
        int _num_lojas, _limite_km_moto, _num_drones, _custo_moto, _custo_caminhao;
        
        int* _vertices_raiz_agm;
        vector< pair< pair<int,int>, pair<float,bool> > >* _agm_ordenada;

    public:

        MinhaBiblioteca(float**,int,int,int,int,int);
        ~MinhaBiblioteca();

        void AlgoritmoPrim();
        int EncontrarMenorPeso(float*,bool*);
        void ObterMaioresCustos();
        void AlocarDrone(int*,int*);
        void AlocarMoto(float*,int*);
        void AlocarCaminhao(float*,int*);
        void MinimizarCustoTrajeto();
};

#endif
