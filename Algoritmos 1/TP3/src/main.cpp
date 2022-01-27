#include "Biblioteca/Grafo.cpp"

int main(){
    int F, W, Q;
    cin>>F>>W;
    int** grafo_aux = new int*[F];
    for(int i = 0; i < F; i++)
        grafo_aux[i] = new int[W];

    for(int i = 0; i < F; i++){
        for(int j = 0; j < W; j++){
            cin>>Q;
            grafo_aux[i][j] = Q;
        }
    }

    Grafo grafo(F, W, grafo_aux);
    // grafo.Imprimir();

    return 0;
}