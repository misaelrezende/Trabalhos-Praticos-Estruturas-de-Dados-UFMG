#include "MinhaBiblioteca.hpp"

bool QualVemPrimeiro(vector<int> distancias, int l, int l1){
    for(vector<int>::iterator it = distancias.begin(); it < distancias.end(); ++it){
        if(*it == l1)
            return true;
        else if(*it == l)
            return false;
    }
}

// Retornar true se o cliente c prefere l1 a l
bool clienteAtualPrefereQuem(Loja* lojas, Cliente* clientes, int c, int l, int l1, int num_lojas){
    // Cheque se c prefere l a loja já agendada l1
    for(int i = 0; i < num_lojas; i++){
        // Se l1 vem antes de l na lista de preferências de c, então c prefere l1 (loja já agendada)
        // Não faça nada
        if( QualVemPrimeiro(clientes[c]._lista_prioridade_distancias, l, l1) )
            return true;

        // Se l vem antes de l1 na lista de c, então libere o agendamento atual de c
        // e agora agende o cliente c a loja l
        if( !QualVemPrimeiro(clientes[c]._lista_prioridade_distancias, l, l1) )
            return false;
    }
}

void EmparelhamentoEstavel(int num_lojas, int num_clientes, int capacidade_total, Loja* lojas, Cliente* clientes){
    // agendamento_cliente[i] indica a loja agendada ao cliente i
    int agendamento_cliente[num_clientes];
    bool lojas_disponiveis[num_lojas];
    memset(agendamento_cliente, -1, sizeof(agendamento_cliente));
    memset(lojas_disponiveis, false, sizeof(lojas_disponiveis));

    // int estoque_disponivel = num_lojas;
    int estoque_disponivel = capacidade_total;
 
    // Enquanto há lojas com estoque disponível
    while (estoque_disponivel > 0){
        // Escolha a primeira loja com estoque disponível
        int l;
        for (l = 0; l < num_lojas; l++)
            if(lojas_disponiveis[l] == false)
                break;

        // Um a um, proponha a todos os clientes, de acordo com a lista de preferência da loja
        // Aqui, l é a loja escolhida com estoque
        // ----->>>> OBSERVAR QUE CADA LOJA TEM UM ESTOQUE DEFINIDO <<<<------
        for (int i = 0; i < num_lojas && lojas_disponiveis[l] == false; i++){

            int c = lojas[l]._lista_prioridade[i].first; // um cliente (id) da lista de preferencias
 
            // O cliente da lista de preferência está disponível (?). Então c é agendado para l.
            if(agendamento_cliente[c] == -1){
                agendamento_cliente[c] = l;
                lojas_disponiveis[l] = true; // Diminui uma vaga no estoque da loja
                estoque_disponivel--;
            }
            else{
                // Se c não está disponível,
                // Encontre onde ele está agendado
                int l1 = agendamento_cliente[c];
 
                // Se c prefere l a l1, então troque o agendamento entre c e l1 e
                // faça o agendamento de c com l
                if( clienteAtualPrefereQuem(lojas, clientes, c, l, l1, num_lojas) == false ){
                    agendamento_cliente[c] = l;
                    lojas_disponiveis[l] = true;
                    lojas_disponiveis[l1] = false;
                }
            }

        }

    }

}
