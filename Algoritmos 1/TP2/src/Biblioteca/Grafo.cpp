#include "Grafo.hpp"

Grafo::Grafo(Vertice* entrada, int n){
    this->_vertices = entrada;
    this->_n = n;
}

void Grafo::Imprimir(){
    for(int i = 0; i < this->_n; i++){
        cout<<this->_vertices[i].id<<" "<<this->_vertices[i].x<<" "<<this->_vertices[i].y<<endl;
    }
    cout<<endl;
}


Grafo::~Grafo(){}
