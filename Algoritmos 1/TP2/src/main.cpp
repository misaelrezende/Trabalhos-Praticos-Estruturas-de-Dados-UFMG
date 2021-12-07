#include "Biblioteca/Grafo.cpp"

int main(){
    int N, K, D, M, C;
    int X, Y;
    cin >> N >> K >> D >> M >> C;
    Vertice* vertices = new Vertice[N];

    for(int i = 0; i < N; i++){
        cin >> X >> Y;
        vertices[i].id = i;
        vertices[i].x = X;
        vertices[i].y = Y;
    }

    Grafo grafo(vertices, N);
    grafo.Imprimir();

    return 0;
}
