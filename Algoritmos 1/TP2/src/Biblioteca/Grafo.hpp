#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <cmath>
using namespace std;

struct {
    int id, x, y;
} typedef Vertice;

class Grafo{
    private:
        int _n;
        Vertice* _vertices;
        float** _distancias;

    public:
        Grafo(/* args */);
        Grafo(Vertice*, int);
        void CalcularDistancias();
        void Imprimir();
        ~Grafo();
};

/*
- Para calcular custo, tenho que checar a distância de um vértice para todos os outros
  - Posso salvar as distâncias em um vetor
- Posso criar uma matriz de adjacências com as distâncias
*/
#endif
