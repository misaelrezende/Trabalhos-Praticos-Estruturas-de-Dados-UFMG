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
static const int MAXPENDING = 10; // Pedidos de conexão pendentes máximos

void informa_erro_e_termina_programa(char *mensagem){
    printf("%s", mensagem);
    exit(1);
}


int contador_clientes = 0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

typedef struct cliente{
	int indice;
	int socket_id;
	struct sockaddr_in endereco_cliente;
	unsigned int tamanho;
} Cliente;

Cliente clientes[MAX_SIZE];
pthread_t thread[MAX_SIZE];

// Cria conexão TCP
int criar_conexao_tcp(){
	int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sock < 0)
        informa_erro_e_termina_programa("Falha em iniciar conexao socket do servidor.\n");

	return sock;
}

// Abre conexão TCP
void abrir_conexao_tcp(int socket_do_servidor, int numero_de_porta){
	struct sockaddr_in endereco_servidor;						// Local address
	memset(&endereco_servidor, 0, sizeof(endereco_servidor));	// Zero out structure
	endereco_servidor.sin_family = AF_INET;						// IPv4 address family
	endereco_servidor.sin_addr.s_addr = htons(INADDR_ANY);		// Any incoming interface
	endereco_servidor.sin_port = htons(numero_de_porta);		// Local port

	// Bind ao endereço local
	if(bind(socket_do_servidor, (struct sockaddr *) &endereco_servidor, sizeof(endereco_servidor)) < 0){
		// Fecha a conexão devido a erro
		close(socket_do_servidor);
		informa_erro_e_termina_programa("Falha no bind().\nEncerrando servidor.\n");
	}

	// Abrir escuta para conexão de cliente
	if(listen(socket_do_servidor, MAXPENDING) < 0){
		// Fecha a conexão devido a erro
        close(socket_do_servidor);
        informa_erro_e_termina_programa("Falha no listen().\nEncerrando servidor.\n");
	}

	if(DEBUG == true)
        printf(">> Servidor escutando na porta %i\n", numero_de_porta);
}

void* comunicar(void* cliente){
	Cliente* cliente_atual = (Cliente*) cliente;
	int indice = cliente_atual->indice;
	int socket_do_cliente = cliente_atual->socket_id;

	printf("Cliente %d conectado.\n", indice + 1);

	while(true){

		char mensagem[MAX_SIZE];
		ssize_t num_bytes_recebidos = recv(socket_do_cliente, mensagem, MAX_SIZE, 0);
		if(num_bytes_recebidos < 0)
            informa_erro_e_termina_programa("Falha no recv() ao receber mensagem do cliente.\n");
        else if(num_bytes_recebidos == 0){
            if(DEBUG == true)
                printf("Conexao encerrada pelo cliente.\n");
            close(socket_do_cliente);
            return;
        }
		mensagem[num_bytes_recebidos] = '\0';

		char resposta_para_cliente[MAX_SIZE]; // TODO: resposta para o cliente?

		if(strcmp(mensagem, "SEND") == 0){

			num_bytes_recebidos = recv(socket_do_cliente, mensagem, MAX_SIZE, 0);
			mensagem[num_bytes_recebidos] = '\0';
			printf("Recebido: %s", mensagem);
			int id = atoi(mensagem) - 1;

			num_bytes_recebidos = recv(socket_do_cliente, mensagem, MAX_SIZE, 0); // TODO: checar erros
			mensagem[num_bytes_recebidos] = '\0';

			ssize_t num_bytes_enviados = send(clientes[id].socket_id, mensagem, MAX_SIZE, 0);
			// TODO: tratar caso de mensagem não enviada.
			// 		 Se houver falha, servidor está sendo encerrado.
			// // Se nada foi enviado
			// if (num_bytes_enviados < 0)
			// 	informa_erro_e_termina_programa("Falha no send() ao enviar mensagem para cliente.\n");

		}

	}

	return NULL;
}


int main(int argc, char* argv[]){
	// Args:
    // Número de porta
    if(argc != 2){
        fprintf(stderr,
        "O servidor precisa de exatamente de 1 parametro de entrada:\n\
        ./server <numero da porta>\n");
        exit(1);
    }
	int numero_de_porta = atoi(argv[1]);

	int socket_do_servidor = criar_conexao_tcp();
	abrir_conexao_tcp(socket_do_servidor, numero_de_porta);
	int socket_do_cliente;

	while(true){

		// Espera conexão de cliente
		socket_do_cliente = accept(socket_do_servidor,
			(struct sockaddr*) &clientes[contador_clientes].endereco_cliente,
			&clientes[contador_clientes].tamanho);
		if(socket_do_cliente < 0)
            informa_erro_e_termina_programa("Falha no accept().\nCliente nao conectado\n");

		clientes[contador_clientes].socket_id = socket_do_cliente;
		clientes[contador_clientes].indice = contador_clientes;
        if(DEBUG == true)
            printf("Cliente agora esta conectado.\n");

		pthread_create(&thread[contador_clientes], NULL, comunicar,
			(void *) &clientes[contador_clientes]);

		contador_clientes++;
 
	}

	for(int i = 0 ; i < contador_clientes ; i++)
		pthread_join(thread[i],NULL);

	return 0;
}