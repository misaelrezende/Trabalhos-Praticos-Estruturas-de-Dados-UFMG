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
        int _num_vertices;
        Vertice* _vertices;
        float** _grafo_com_pesos;

    public:
        Grafo(/* args */);
        Grafo(Vertice*, int);
        int GetNumVertices();
        float** GetGrafo();
        void CalcularDistancias();
        void Imprimir();
        ~Grafo();
};

#endif
