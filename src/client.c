#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdbool.h> // _Bool
#include <netdb.h>


#define BUFFER_SIZE 200


void informa_erro_e_termina_programa(char *mensagem){
    printf("%s", mensagem);
    exit(1);
}

// Cria e abre conexão TCP
int criar_e_abrir_conexao_tcp(char *endereco_ip, char *numero_de_porta){ 
    struct addrinfo endereco;
    memset(&endereco, 0, sizeof(endereco)); // Preenche estrutura com zeros
    endereco.ai_family = AF_UNSPEC; // Aceita qualquer endereco suportado pelo SO
    endereco.ai_socktype = SOCK_STREAM;
    endereco.ai_protocol = IPPROTO_TCP;

    struct addrinfo *enderecos_servidor; // Endereço do servidor
    // traduz para conjunto de enderecos socket
    int conjunto_enderecos_servidor = getaddrinfo(endereco_ip, numero_de_porta, &endereco, &enderecos_servidor);
    if(conjunto_enderecos_servidor != 0)
        informa_erro_e_termina_programa("Falha ao obter conjunto de enderecos do servidor\n");

    int socket_do_cliente;
    for(struct addrinfo *endereco = enderecos_servidor; endereco != NULL; endereco = endereco->ai_next){
        // Tenta criar uma conexao
        socket_do_cliente = socket(endereco->ai_family, endereco->ai_socktype, endereco->ai_protocol);
        // Se socket falhar, tentar proximo endereco do conjunto
        if(socket_do_cliente < 0)
            continue;

        // Se nao falhar, conecta ao servidor
        if(connect(socket_do_cliente, endereco->ai_addr, endereco->ai_addrlen) == 0)
            break; // Se conexao ter êxito, pausar e retornar socket

        // Se falhar, tentar  próximo endereco do conjunto
        close(socket_do_cliente);
        socket_do_cliente = -1;
    }

    freeaddrinfo(enderecos_servidor); // desaloca enderecos

    if(socket_do_cliente < 0)
        informa_erro_e_termina_programa("Falha na conexao do cliente.\n");

    return socket_do_cliente;
}

// Enviar mensagem para o servidor
void enviar_mensagem_para_servidor(int socket_do_cliente, char *message, size_t tamanho_mensagem){
    ssize_t bytes_enviados = send(socket_do_cliente, message, tamanho_mensagem, 0);
    if(bytes_enviados < 0)
        informa_erro_e_termina_programa("Falha do send() ao enviar mensagem.\n");

    else if(bytes_enviados != tamanho_mensagem)
        informa_erro_e_termina_programa("Falha do send()\nEnviado numero inesperado de bytes.\n");
}

// Recebe mensagem do servidor
void receber_resposta_do_servidor(int socket_do_cliente){
    char buffer[BUFFER_SIZE] = "";
    ssize_t bytes_recebidos;
    int total_de_bytes_recebidos = 0;

    // Recebe até BUFFER_SIZE - 1 bytes
    // Menos 1 para deixar espaço para o delimitador null
    bytes_recebidos = recv(socket_do_cliente, buffer, BUFFER_SIZE - 1, 0);

    if(bytes_recebidos < 0)
        informa_erro_e_termina_programa("Falha do recv() ao receber mensagem do servidor.\n");
    else if(bytes_recebidos == 0)
        informa_erro_e_termina_programa("Falha no recv(). Conexao encerrada antencipadamente pelo servidor.\n");

    total_de_bytes_recebidos += bytes_recebidos;
    buffer[bytes_recebidos] = '\0'; // delimitador final da string

    printf("<< %s", buffer); // imprime mensagem recebida do servidor
}

// Ler mensagem do cliente, enviar mensagem ao servidor e receber resposta do servidor
void comunicar_com_servidor(int socket_do_cliente){
    char *mensagem = NULL;
    size_t tamanho_mensagem;

    while(true){
        printf("> ");
        // ler solicitações do cliente
        getline(&mensagem, &tamanho_mensagem, stdin);

        tamanho_mensagem = strlen(mensagem);
        enviar_mensagem_para_servidor(socket_do_cliente, mensagem, tamanho_mensagem);
        receber_resposta_do_servidor(socket_do_cliente);
        mensagem = NULL;
    }
}

int main(int argc, char *argv[]){
    // Args:
    // Endereço IP
    // Número de porta
    if(argc != 3){
        fprintf(stderr,
        "O cliente precisa de exatamente de 2 parametros de entrada:\n\
        ./client <endereco ip <numero da porta>\n");
        exit(1);
    }

    char *endereco_ip = argv[1];
    char *numero_de_porta = argv[2];
    
    int tcp_socket = criar_e_abrir_conexao_tcp(endereco_ip, numero_de_porta);
    comunicar_com_servidor(tcp_socket);

    return 0;
}
