#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

struct {
    int id, x, y;
} typedef Vertice;

class Grafo{
    private:
        int _num_vertices;
        // Armazena os vertices do grafo
        Vertice* _vertices;
        // Grafo gerado com as distâncias de cada loja
        float** _grafo_com_pesos;

    public:
        Grafo(Vertice*, int);
        ~Grafo();

        float** GetGrafo();
        void CalcularDistancias();
        void Imprimir();
};

#endif
