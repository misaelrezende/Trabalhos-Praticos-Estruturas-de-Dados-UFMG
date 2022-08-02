#include "Grafo.hpp"

Grafo::Grafo(int fileira, int qtde_fileira, int** grafo){
    _vertices = fileira * qtde_fileira;
    _fileira = fileira;
    _qtde_fileira = qtde_fileira;

    _grafo = grafo;
}

void Grafo::Imprimir(){
    for(int i = 0; i < _fileira; i++){
        for(int j = 0; j < _qtde_fileira; j++)
            cout<<_grafo[i][j]<<" ";
        cout<<endl;
    }
}

Grafo::~Grafo(){}