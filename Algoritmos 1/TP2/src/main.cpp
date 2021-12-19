#include "Biblioteca/MinhaBiblioteca.cpp"

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
    // grafo.Imprimir();

    MinhaBiblioteca biblioteca = MinhaBiblioteca(grafo.GetGrafo(), N, K, D, M, C);
    // Encontra AGM no grafo
    biblioteca.AlgoritmoPrim();
    // Encontra a melhor combinação de meios de transporte para cada rota
    biblioteca.MinimizarCustoTrajeto();

    return 0;
}
