#include "Biblioteca/biblioteca.hpp"

int main(){
    int N, M, m, n;
    scanf("%d %d", &N, &M);
    scanf("%d", &m);
    Loja *lojas = new Loja[m];

    int estoque, x, y;
    for(int i = 0; i < m; i++){
        // lojas[i].id = i;
        // scanf("%d %d %d", lojas[i].estoque, lojas[i]->x, lojas[i]->y);
        scanf("%d %d %d", &estoque, &x, &y);
        lojas[i] = Loja(i, estoque, x, y);
    }

    scanf("%d", &n);
    Cliente *clientes = new Cliente[n];

    for(int i = 0; i < n; i++){
        // clientes[i]->id = i;
        clientes[i].setId(i);
        // scanf("%")
    }

    return 0;
}