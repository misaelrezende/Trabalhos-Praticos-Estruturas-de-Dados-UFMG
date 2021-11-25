#include "Loja.hpp"

// Função auxiliar para ordenar pelo segundo elemento
bool Lojasortbysec(const pair<int,float> &a, const pair<int,float> &b){
    return (a.second < b.second);
}

bool sortdesc(int i, int j){
  return (int(i) > int(j));
}

Loja::Loja(/* args */){}

Loja::Loja(int id, int estoque, int x, int y){
    this->_id = id;
    this->_estoque = estoque;
    this->_x = x;
    this->_y = y;

    InicializarAgendamentos();
    // cout<<"tam _agendamentos: "<<this->_agendamentos.size() << endl;
}
void Loja::InicializarAgendamentos(){
    for (int i = 0; i < this->_estoque; i++)
        // this->_agendamentos[i] = -1;
        this->_agendamentos.push_back(-1);
}
int Loja::GetId(){
    return this->_id;
}
int Loja::GetEstoque(){
    return this->_estoque;
}
bool Loja::TemEstoque(){
    if(this->_tem_estoque == true)
        return true;
    return false;
}

void Loja::AgendarCliente(int id){
    // cout<<"Loja::tem estoque (antes): "<<this->TemEstoque()<<endl;
    for(int i = 0; i < this->_estoque; i++){
        if(this->_agendamentos[i] == -1){
            this->_agendamentos[i] = id;
            break;
        }
    }
    // seta _tem_estoque para false se acabou o estoque
    // for(int i = 0; i < this->_estoque; i++)
    //     cout << this->_agendamentos[i] << " ";
    // cout<<endl;
    bool aux = false;
    for(int i = 0; i < this->_estoque; i++)
        if(this->_agendamentos[i] == -1)
            aux = true;
    this->_tem_estoque = aux;
    // cout<<"Loja::tem estoque (depois): "<<this->TemEstoque()<<endl;
}

void Loja::LiberarCliente(int id){
    for(int i = 0; i < this->_estoque; i++){
        if(this->_agendamentos[i] == id){
            this->_agendamentos[i] = -1;
            break;
        }
    }
    // Reordena a lista, caso necessário
    stable_sort(this->_agendamentos.begin(), this->_agendamentos.end(), sortdesc);
    // seta _tem_estoque para true
    this->_tem_estoque = true;
}

void Loja::Imprimir(){
    // cout << this->_id << " " << this->_estoque << " " << this->_x << " " << this->_y << endl;
    // cout << this->_id;
    // for (vector<pair<int, float>>::iterator it = this->_lista_prioridade.begin(); it != this->_lista_prioridade.end(); ++it){
    //     cout << " " << it->first;
    // }
    // cout << endl;
    
    cout << this->_id << endl;
    for(vector<int>::iterator it = this->_agendamentos.begin(); it != this->_agendamentos.end(); ++it){
        if(*it == this->_agendamentos.front() && *it != -1){
            cout << *it;
            if(*it == this->_agendamentos.back())
                cout << endl;
        }
        else if(*it != -1){
            cout << " " << *it;
            if(*it == this->_agendamentos.back())
                cout << endl;
        }
        else if(*it == -1){
            cout << endl;
            break;
        }
    }

}

void Loja::CriarListaPrioridade(vector<pair<int, float>> lista){
    stable_sort(lista.begin(), lista.end(), Lojasortbysec);   
    this->_lista_prioridade = lista;
}

pair<int,int> Loja::GetLocalizacao(){
    return make_pair(_x, _y);
}

Loja::~Loja(){}