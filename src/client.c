#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdbool.h> // bool

#define MAX_SIZE 1024
#define DEBUG true

void informa_erro_e_termina_programa(char *mensagem){
    printf("%s", mensagem);
    exit(1);
}

// Cria e abre conexão TCP
int criar_e_abrir_conexao_tcp(char *endereco_ip, int numero_de_porta){
	int socket_cliente = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(socket_cliente < 0)
        informa_erro_e_termina_programa("Falha em iniciar conexao socket do cliente.\n");

	struct sockaddr_in endereco_servidor;					// Local address
	endereco_servidor.sin_family = AF_INET;					// IPv4 address family
	endereco_servidor.sin_addr.s_addr = htonl(INADDR_ANY);	// Any incoming interface
	endereco_servidor.sin_port = htons(numero_de_porta);	// Local port

	if(connect(socket_cliente, (struct sockaddr*) &endereco_servidor, sizeof(endereco_servidor)) == -1){
		informa_erro_e_termina_programa("Erro ao conectar o cliente.\n");
	}

	if(DEBUG == true)
		printf("Conexao criada.\n");

	return socket_cliente;
}

void* receber_dados(void* socket_id){
	int socket_do_cliente = *((int *) socket_id);

	while(true){

		char mensagem[MAX_SIZE];
		ssize_t num_bytes_recebidos = recv(socket_do_cliente, mensagem, MAX_SIZE, 0);
		if(num_bytes_recebidos < 0)
            informa_erro_e_termina_programa("Falha no recv() ao receber mensagem do servidor.\n");
        else if(num_bytes_recebidos == 0){
            if(DEBUG == true)
                printf("Falha no recv(). Conexao encerrada antencipadamente pelo servidor.\n");
				// informa_erro_e_termina_programa("Falha no recv(). Conexao encerrada antencipadamente pelo servidor.\n");
            close(socket_do_cliente);
            return;
        }
		mensagem[num_bytes_recebidos] = '\0';
		printf("%s\n", mensagem);

	}

}


int main(int argc, char* argv[]){
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
	int numero_de_porta = atoi(argv[2]);

	int socket_do_cliente = criar_e_abrir_conexao_tcp(endereco_ip, numero_de_porta);


    //Thread para receber mensagens
	pthread_t thread;
	pthread_create(&thread, NULL, receber_dados, (void *) &socket_do_cliente );

	while(true){

		char entrada[MAX_SIZE];
		printf("Digite: ");
		scanf("%s", entrada);

		if(strcmp(entrada, "SEND") == 0){
			printf("ENTROU AQUI\n");
			send(socket_do_cliente, entrada, MAX_SIZE,0); // TODO: checar se envio foi ok
			
			scanf("%s",entrada);
			send(socket_do_cliente, entrada, MAX_SIZE,0);
			
			scanf(" %[^\n]s",entrada);
			send(socket_do_cliente, entrada, MAX_SIZE,0);

		}

	}


}
