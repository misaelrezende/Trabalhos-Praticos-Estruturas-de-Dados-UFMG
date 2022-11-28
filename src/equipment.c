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

// Recebe dados do servidor
void* receber_dados(void* socket_id){
	int socket_do_cliente = *((int *) socket_id);
	char mensagem_recebida[MAX_SIZE];

	while(true){
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
		if(DEBUG == true)
			printf("mensagem recebida pelo cliente: ");
		printf("%s\n", mensagem_recebida);
	}
}

// Envia dados para o servidor
void *enviar_dados(void* socket_id){
	int socket_do_cliente = *((int *) socket_id);
	size_t tamanho_mensagem;
	char *entrada = NULL;

	while(true){
		if(entrada != NULL){ // evita erro de comparação com NULL
			if(strcmp(entrada, "close connection\n") == 0){
				if(DEBUG == true)
					printf("Fechando conexao\n");

				close(socket_do_cliente);
				return NULL;
			}
		}

		getline(&entrada, &tamanho_mensagem, stdin); // lê com '\n'
		tamanho_mensagem = strlen(entrada);

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


    //Thread para receber e enviar mensagens
	pthread_t thread_recebimento, thread_envio;
	int valor_retorno_recebimento = pthread_create(&thread_recebimento, NULL, receber_dados, (void *) &socket_do_cliente);
	if(valor_retorno_recebimento != 0)
		printf("Thread 'receber_dados' falhou\n");

	int valor_retorno_envio = pthread_create(&thread_envio, NULL, enviar_dados, (void *) &socket_do_cliente);
	if(valor_retorno_envio != 0)
		printf("Thread 'enviar_dados' falhou\n");

	pthread_join(thread_recebimento, NULL);
	pthread_join(thread_envio, NULL);

	return 0;
}
