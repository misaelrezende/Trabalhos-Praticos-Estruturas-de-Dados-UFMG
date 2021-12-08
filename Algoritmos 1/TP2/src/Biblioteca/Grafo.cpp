#include "Grafo.hpp"

Grafo::Grafo(Vertice* entrada, int n){
    this->_vertices = entrada;
    this->_n = n;

    CalcularDistancias();
}

void Grafo::CalcularDistancias(){
    this->_distancias = new float*[this->_n];
    for(int i = 0; i < this->_n; i++)
        this->_distancias[i] = new float[this->_n];
    
    float distancia;
    for(int i = 0; i < this->_n; i++){
        for(int j = 0; j < this->_n; j++){
            if(j < i) // para não calcular duas vezes
                continue;
            distancia = sqrt( pow(this->_vertices[i].x -this->_vertices[j].x, 2) + pow(this->_vertices[i].y - this->_vertices[j].y, 2) );
            this->_distancias[i][j] = distancia;
            this->_distancias[j][i] = distancia;
        }
    }

    for(int i = 0; i < this->_n; i++){
        cout<<"id: "<<i<<" ";
        for(int j = 0; j < this->_n; j++)
            cout<<this->_distancias[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl<<endl;
}

void Grafo::Imprimir(){
    for(int i = 0; i < this->_n; i++){
        cout<<this->_vertices[i].id<<" "<<this->_vertices[i].x<<" "<<this->_vertices[i].y<<endl;
    }
    cout<<endl;
}


Grafo::~Grafo(){}
