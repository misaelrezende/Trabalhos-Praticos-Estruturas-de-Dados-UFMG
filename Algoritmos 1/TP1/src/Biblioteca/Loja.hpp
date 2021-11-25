#ifndef LOJA_H
#define LOJA_H

#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

class Loja{
    private:
        int _id, _estoque, _x, _y;
        bool _tem_estoque = true;
        vector<int> _agendamentos;

    public:
        vector<pair<int, float>> _lista_prioridade;
        Loja();
        Loja(int, int, int, int);

        int GetId();
        int GetEstoque();
        bool TemEstoque();
        void SetTemEstoque();
        void InicializarAgendamentos();
        void AgendarCliente(int);
        void LiberarCliente(int);
        void Imprimir();
        pair<int,int> GetLocalizacao();
        void CriarListaPrioridade(vector<pair<int, float>>);
        ~Loja();
};

#endif