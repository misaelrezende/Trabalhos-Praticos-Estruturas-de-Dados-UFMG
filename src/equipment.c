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
		informa_erro_e_termina_programa("Nao foi possivel estabelecer uma conexao com o servidor.\nErro ao conectar o cliente.\n");
	}

	if(DEBUG == true)
		printf("Conexao criada.\n");

	return socket_cliente;
}

// Recebe e envia dados do/para servidor
void* receber_e_enviar_dados(void* socket_id){
	int socket_do_cliente = *((int *) socket_id);
	size_t tamanho_mensagem;
	char mensagem_recebida[MAX_SIZE];
	char *entrada = NULL;

	while(true){
		// Recebimento de dados
		ssize_t num_bytes_recebidos = recv(socket_do_cliente, mensagem_recebida, MAX_SIZE, 0);
		if(num_bytes_recebidos < 0)
            informa_erro_e_termina_programa("Falha no recv() ao receber mensagem do servidor.\n");
        else if(num_bytes_recebidos == 0){
            if(DEBUG == true)
                printf("Falha no recv().\nConexao encerrada antecipadamente pelo servidor.\n");

            close(socket_do_cliente);
            return NULL;
        }

		mensagem_recebida[num_bytes_recebidos] = '\0';
		printf("mensagem recebida pelo cliente: %s\n", mensagem_recebida);

		// Envio de dados
		// printf("Digite: ");
		getline(&entrada, &tamanho_mensagem, stdin); // lê com '\n'
		tamanho_mensagem = strlen(entrada);

		if(strcmp(mensagem, "close connection\n") == 0){
			printf("Fechando conexao\n");
			return NULL;
		}

		ssize_t num_bytes_enviados = send(socket_do_cliente, entrada, strlen(entrada), 0);
		if(num_bytes_enviados < 0)
			informa_erro_e_termina_programa("Falha no send() ao enviar mensagem para servidor.\n");
		else if(num_bytes_enviados != strlen(entrada))
			informa_erro_e_termina_programa("Falha no send().\nEnviado numero inesperado de bytes.\n");
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
	int valor_de_retorno = pthread_create(&thread, NULL, receber_e_enviar_dados, (void *) &socket_do_cliente);
	if(valor_de_retorno != 0)
		printf("Thread 'receber_e_enviar_dados' falhou\n");

	pthread_join(thread, NULL);

	return 0;
}
