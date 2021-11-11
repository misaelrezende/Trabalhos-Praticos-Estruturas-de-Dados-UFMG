#include "Biblioteca/biblioteca.cpp"

int main(){
    int N, M, m, n;
    scanf("%d %d", &N, &M);
    scanf("%d", &m);
    Loja *lojas = new Loja[m];

    int estoque, x, y;
    for(int i = 0; i < m; i++){
        scanf("%d %d %d", &estoque, &x, &y);
        lojas[i] = Loja(i, estoque, x, y);
    }

    scanf("%d", &n);
    Cliente *clientes = new Cliente[n];

    char estado[3], pgto[9];
    int idade;
    for(int i = 0; i < n; i++){
        // clientes[i]->id = i;
        // clientes[i].setId(i);
        // fgets(entrada, 20, stdin);
        // char * pch = strtok (entrada, " ");
        // while (pch != NULL){
        //     printf ("%s\n",pch);
        //     pch = strtok (NULL, " ,.-");
        // }
        scanf("%d %s %s %d %d", &idade, estado, pgto, &x, &y);
        // printf("%d %s %s %d %d", idade, estado, pgto, x, y);
        clientes[i] = Cliente(i, idade, estado, pgto, x, y);
    }

    for (int i = 0; i < m; i++){
        lojas[i].imprime();
    }
    for (int i = 0; i < n; i++){
        clientes[i].imprime();
    }

    return 0;
}