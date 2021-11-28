#include "MinhaBiblioteca.hpp"

bool QualVemPrimeiro(vector<int> distancias, int l, int l1){
    for(vector<int>::iterator it = distancias.begin(); it < distancias.end(); ++it){
        if(*it == l1)
            return false;
        else if(*it == l)
            return true;
    }
}

// Retornar true se o cliente c prefere l a l1
bool clienteAtualPrefereQuem(Loja* lojas, Cliente* clientes, int c, int l, int l1, int num_lojas){
    // Cheque se c prefere l a loja já agendada l1
    for(int i = 0; i < num_lojas; i++){
        // Se l1 vem antes de l na lista de preferências de c, então c prefere l1 (loja já agendada)
        // Não faça nada
        if( !QualVemPrimeiro(clientes[c]._lista_prioridade_distancias, l, l1) )
            return false;

        // Se l vem antes de l1 na lista de c, então libere o agendamento atual de c
        // e agora agende o cliente c a loja l
        if( QualVemPrimeiro(clientes[c]._lista_prioridade_distancias, l, l1) )
            return true;
    }
}

void EmparelhamentoEstavel(int num_lojas, int num_clientes, int capacidade_total, Loja* lojas, Cliente* clientes){
    int estoque_disponivel = capacidade_total;
    int l = 0;
    // Enquanto há lojas com estoque disponível
    while (estoque_disponivel > 0){
        // Escolha a primeira loja com estoque disponível
        if(l >= num_lojas)
            l = 0;
        for (; l < num_lojas; l++)
            if(lojas[l].TemEstoque())
                break;
        if(l >= num_lojas)
            l = 0;

        // Um a um, proponha a todos os clientes, de acordo com a lista de preferência da loja
        // Aqui, l é a loja escolhida com estoque
        for (int i = 0; i < num_clientes and lojas[l].TemEstoque(); i++){
            int c = lojas[l]._lista_prioridade_tickets[i].first; // um cliente (id) da lista de preferencias de l
            // O cliente da lista de preferência está disponível (?). Então c é agendado para l.
            if( clientes[c].GetClienteAgendado() == -1 ){
                lojas[l].AgendarCliente(c);
                clientes[c].SetClienteAgendado(l);
                estoque_disponivel--;
                l += 1;
                break;
            }
            else{
                // Se c não está disponível,
                // Encontre onde ele está agendado
                int l1 = clientes[c].GetClienteAgendado();
 
                // Se c prefere l a l1, então troque o agendamento entre c e l1 e
                // faça o agendamento de c com l
                if( clienteAtualPrefereQuem(lojas, clientes, c, l, l1, num_lojas) ){
                    lojas[l].AgendarCliente(c);
                    lojas[l1].LiberarCliente(c);
                    clientes[c].SetClienteAgendado(l);
                    l += 1;
                    break;
                }
            }

        }

    }

}
