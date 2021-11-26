#include "Biblioteca/MinhaBiblioteca.cpp"

int main(){
    int N, M, m, n, capacidade_total = 0;
    scanf("%d %d", &N, &M);
    scanf("%d", &m);
    Loja *lojas = new Loja[m];

    int estoque, x, y;
    for(int i = 0; i < m; i++){
        scanf("%d %d %d", &estoque, &x, &y);
        lojas[i] = Loja(i, estoque, x, y);
        capacidade_total += estoque;
    }

    scanf("%d", &n);
    Cliente *clientes = new Cliente[n];

    char estado[3], pgto[9];
    int idade;
    for(int i = 0; i < n; i++){
        scanf("%d %s %s %d %d", &idade, estado, pgto, &x, &y);
        clientes[i] = Cliente(i, idade, estado, pgto, x, y);
    }

    // Obtenha os tickets de cada cliente
    vector<pair<int, float>> lista_auxiliar;
    for(int i = 0; i < n; i++)
       lista_auxiliar.push_back( make_pair(i, clientes[i].GetTicket()) );

    // Cria a lista de prioridade para cada loja
    for(int i = 0; i < m; i++)
        lojas[i].CriarListaPrioridade(lista_auxiliar);

    // Obtenha a localização de cada loja
    vector<pair<int,pair<int, int>>> lista_localizacao_lojas;
    for(int i = 0; i < m; i++)
        lista_localizacao_lojas.push_back(make_pair(i, lojas[i].GetLocalizacao()));

    // Cria a lista de prioridade por distância
    for(int i = 0; i < n; i++)
       clientes[i].CriarListaPrioridade(lista_localizacao_lojas);

    // for(int i = 0; i < n; i++)
    //     clientes[i].Imprimir();

    EmparelhamentoEstavel(m, n, capacidade_total, lojas, clientes);
    
    for(int i = 0; i < m; i++)
        lojas[i].Imprimir();

    return 0;
}
