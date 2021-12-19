#include "Grafo.hpp"

Grafo::Grafo(Vertice* entrada, int n){
    this->_vertices = entrada;
    this->_num_vertices = n;

    CalcularDistancias();
}

// Retorna o número de vértices (lojas)
int Grafo::GetNumVertices(){
    return this->_num_vertices;
}

// Retorna o grafo completo construído
// com as respectivas distâncias das lojas
float ** Grafo::GetGrafo(){
    return this->_grafo_com_pesos;
}

// Calcula distâncias de cada loja as outras lojas
void Grafo::CalcularDistancias(){
    this->_grafo_com_pesos = new float*[this->_num_vertices];
    for(int i = 0; i < this->_num_vertices; i++)
        this->_grafo_com_pesos[i] = new float[this->_num_vertices];
    
    float distancia;
    for(int i = 0; i < this->_num_vertices; i++){
        for(int j = 0; j < this->_num_vertices; j++){
            if(j < i) // para não calcular duas vezes
                continue;
            distancia = sqrt( pow(this->_vertices[i].x -this->_vertices[j].x, 2) + pow(this->_vertices[i].y - this->_vertices[j].y, 2) );
            this->_grafo_com_pesos[i][j] = distancia;
            this->_grafo_com_pesos[j][i] = distancia;
        }
    }

    for(int i = 0; i < this->_num_vertices; i++){
        cout<<"id: "<<i<<"-> ";
        for(int j = 0; j < this->_num_vertices; j++)
            cout<<setw(8)<<this->_grafo_com_pesos[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
}

// Imprime o grafo gerado
void Grafo::Imprimir(){
    for(int i = 0; i < this->_num_vertices; i++){
        cout<<this->_vertices[i].id<<" "<<this->_vertices[i].x<<" "<<this->_vertices[i].y<<endl;
    }
    cout<<endl;
}


Grafo::~Grafo(){}
