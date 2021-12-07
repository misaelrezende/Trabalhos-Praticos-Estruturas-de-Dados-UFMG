#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <vector>
using namespace std;

struct {
    int id, x, y;
} typedef Vertice;

class Grafo{
    private:
        int _n;
        Vertice* _vertices;
        vector<vector<int>> grafo;

    public:
        Grafo(/* args */);
        Grafo(Vertice*, int);
        void Imprimir();
        ~Grafo();
};

/*
- Para calcular custo, tenho que checar a distância de um vértice para todos os outros
  - Posso salvar as distâncias em um vetor
- Posso criar uma matriz de adjacências com as distâncias
*/
#endif
