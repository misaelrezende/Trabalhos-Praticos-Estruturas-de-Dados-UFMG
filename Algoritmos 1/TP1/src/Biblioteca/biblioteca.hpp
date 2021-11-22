#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

class Cliente{
    private:
        int _id, _idade, _x, _y;
        vector<int> _lista_prioridade_distancias;
        float _ticket;
        string _estado_de_origem, _tipo_pgto;
    
    public:
        Cliente();
        Cliente(int, int, string, string, int, int);

        void Imprimir();
        void setId(int);
        void setIdade(int);
        void setLocalizacao(int, int);
        void setEstado(char*);
        void setTipoPgto(char*);
        int getScoreEstado(string);
        int getScoreTipoPagamento(string);
        float GetTicket();
        void CalcularTicket();
        int CalcularDistancia(pair<int,int>);
        void CriarListaPrioridade(vector<pair<int,int>>);
        ~Cliente();
};

class Loja{
    private:
        int _id, _estoque, _x, _y;
        vector<pair<int, float>> _lista_prioridade;

    public:
        Loja();
        Loja(int, int, int, int);

        void Imprimir();
        void setId(int);
        void setEstoque(int);
        void setLocalizacao(int, int);
        pair<int,int> GetLocalizacao();
        void CriarListaPrioridade(vector<pair<int, float>>);
        ~Loja();
};

#endif