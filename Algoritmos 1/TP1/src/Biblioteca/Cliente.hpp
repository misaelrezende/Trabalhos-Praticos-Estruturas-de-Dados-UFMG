#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

class Cliente{
    private:
        int _id, _idade, _x, _y;
        int _cliente_agendado = -1;
        float _ticket;
        string _estado_de_origem, _tipo_pgto;
    
    public:
        vector<int> _lista_prioridade_distancias; // lista de prioridade (proximidade) para cada cliente
        Cliente();
        Cliente(int, int, string, string, int, int);

        int getScoreEstado(string);
        int getScoreTipoPagamento(string);
        float GetTicket();
        int GetClienteAgendado();
        void SetClienteAgendado(int);
        void Imprimir();
        void CalcularTicket();
        int CalcularDistancia(pair<int,int>);
        void CriarListaPrioridade(vector<pair<int,pair<int, int>>>);
        ~Cliente();
};

#endif