#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // _Bool
#include <netinet/in.h>
#include <sys/socket.h>
/* Implementação do código que vai interagir com os equipamentos,
e receber os pedidos do cliente virá aqui.
Ter interface para:
- instalação
- desinstalação
- leitura de dados dos equipamentos

- Rack é uma TAD que armazena TADs do tipo Switch
- Switch é uma TAD que contém tipo, ...
*/

// Cria conexão TCP
int criar_conexao_tcp(char* tipo_de_endereco){
    int sock;
    _Bool ipv4 = false;
    if(strcmp(tipo_de_endereco, "V4") == 0)
        ipv4 = true;

    if(ipv4)
        sock = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
    else
        sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(sock < 0)
        printf("Falha em inicar conexão socket.\n");

    return sock;
}

int main(int argc, char *argv[]){

    // Args:
    // Tipo do endereço
    // Número de porta
    if(argc != 3){
        fprintf(stderr,
        "O servidor precisa de exatamente de 2 parametros de entrada:\n\
        ./server <tipo de endereço '<v4|v6>'> <número da porta>\n");
        exit(1);
    }

    char *tipo_de_endereco = argv[1];
    // int numero_de_porta = atoi(argv[2]);

    int socket_do_servidor = criar_conexao_tcp(tipo_de_endereco);

    return 0;
}
