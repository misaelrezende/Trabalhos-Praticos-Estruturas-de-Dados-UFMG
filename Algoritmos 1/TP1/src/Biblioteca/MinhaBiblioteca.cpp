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
        if( !QualVemPrimeiro(clientes[c]._lista_prioridade_distancias, l, l1) ){
            // return false;
            // Se a loja a ser trocada tem estoque
            if(lojas[l].TemEstoque() == true)
                return false;
            else{
                // Se a loja, mesmo sem estoque disponı́vel, tiver um agendamento
                // de algum cliente q com ticket menor que c.                
                // Olhe todos clientes agendados de l, se houver algum com ticket
                // menor, libere esse cliente da lista de agendados de l
                for(vector<int>::iterator it = lojas[l]._agendamentos.begin(); it != lojas[l]._agendamentos.end(); ++it){
                    if(clientes[*it].GetTicket() < clientes[c].GetTicket()){
                        lojas[l].LiberarCliente(*it);
                        clientes[*it].SetClienteAgendado(-1);
                        return false;
                    }
                }
                return true;
            }
        }
    }
}

void EmparelhamentoEstavel(int num_lojas, int num_clientes, int capacidade_total, Loja* lojas, Cliente* clientes){
    // int estoque_disponivel = num_lojas;
    int estoque_disponivel = capacidade_total;
    cout<<"num_lojas: "<<num_lojas<<" num_clientes: "<<num_clientes<<flush<<endl<<endl;
    // Enquanto há lojas com estoque disponível
    while (estoque_disponivel > 0){
        // Escolha a primeira loja com estoque disponível
        int l;
        for (l = 0; l < num_lojas; l++)
            // if(lojas_disponiveis[l] == true)
            if(lojas[l].TemEstoque() == true)
                break;
        cout << "escolheu loja l: " << l << flush << endl;

        // Um a um, proponha a todos os clientes, de acordo com a lista de preferência da loja
        // Aqui, l é a loja escolhida com estoque
        // ----->>>> OBSERVAR QUE CADA LOJA TEM UM ESTOQUE DEFINIDO <<<<------
        for (int i = 0; i < num_clientes && lojas[l].TemEstoque() == true; i++){
            cout<<"l:"<<l<<" i: "<<i<<" tem estoque: "<<lojas[l].TemEstoque()<<flush<<endl;
            int c = lojas[l]._lista_prioridade_tickets[i].first; // um cliente (id) da lista de preferencias de l
            cout << "c: " << c << flush << endl;
            // O cliente da lista de preferência está disponível (?). Então c é agendado para l.
            if( clientes[c].GetClienteAgendado() == -1 ){
                lojas[l].AgendarCliente(c);
                clientes[c].SetClienteAgendado(l);
                estoque_disponivel--;
                cout << "agendou cliente c: " << c << flush << endl;
            }
            else{
                // Se c não está disponível,
                // Encontre onde ele está agendado
                int l1 = clientes[c].GetClienteAgendado();
                cout << "cliente c: " << c << " nao esta disponivel" << flush << endl;
 
                // Se c prefere l a l1, então troque o agendamento entre c e l1 e
                // faça o agendamento de c com l
                if( clienteAtualPrefereQuem(lojas, clientes, c, l, l1, num_lojas) == false ){
                    lojas[l].AgendarCliente(c);
                    lojas[l1].LiberarCliente(c);
                    clientes[c].SetClienteAgendado(l);
                    cout << "trocou cliente c: " << c << flush << endl;
                }
            }

        }

    }

}
