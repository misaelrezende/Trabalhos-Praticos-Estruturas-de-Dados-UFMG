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
#define MAXCONNECTED 10 // Quantidade máxima de conexões
static const int MAXPENDING = 10; // Pedidos de conexão pendentes máximos

void informa_erro_e_termina_programa(char *mensagem){
    printf("%s", mensagem);
    exit(1);
}


int contador_clientes = 0;
// static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

typedef struct{
	int id;
	float temperatura; // Entre 0 e 10, com duas casas decimais
	int indice;
	int socket_id;
	struct sockaddr_in endereco_equipamento;
	unsigned int tamanho;
} Equipamento;

Equipamento vetor_de_equipamentos[MAXCONNECTED];
pthread_t vetor_de_threads[MAXCONNECTED];

// Inicializa os equipamentos com valores padrão
// Inicializa id, indice e socket_id com valor '-1'
void inicializar_equipamentos(Equipamento *equipamentos){
	for(int i = 0; i < MAXCONNECTED; i++){
		equipamentos->id = -1;
		equipamentos->indice = -1;
		equipamentos->socket_id = -1;
	}
}

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

// Verifica se houve erro no envio de mensagem.
// Termina o programa em caso de erro.
void verificar_erro_envio_de_mensagem(ssize_t numero_bytes_enviados, int tamanho_mensagem){
	if(numero_bytes_enviados < 0)
		informa_erro_e_termina_programa("Falha no send() ao enviar mensagem para equipamento.\n");
	else if(numero_bytes_enviados != tamanho_mensagem)
		informa_erro_e_termina_programa("Falha no send().\nEnviado numero inesperado de bytes.\n");
}

char* processar_comando(char *mensagem){
	if(DEBUG == true)
		printf("Processando comando: %s", mensagem);

	if(strcmp(mensagem, "close connection\n") == 0){
		return "close connection";
	}else if(strcmp(mensagem, "list equipment\n") == 0){
		return "list equipment";
	}

	return NULL;
}

void* comunicar(void* equipamento){
	Equipamento* equipamento_atual = (Equipamento*) equipamento;
	int indice = equipamento_atual->indice;
	int socket_do_cliente = equipamento_atual->socket_id;
	char *mensagem_para_retornar = NULL;
	char mensagem[MAX_SIZE];

	// Envia número de id a equipamento recentemente conectado
	char msg[10] = "New ID: ", id[2];
	sprintf(id, "%d", indice);  // converte id (int to char)
	strcat(msg, id);

	ssize_t num_bytes_enviados = send(socket_do_cliente, msg, strlen(msg), 0);
	verificar_erro_envio_de_mensagem(num_bytes_enviados, strlen(msg));

	// printf("Equipamento %d conectado.\n", indice);

	while(true){
		ssize_t num_bytes_recebidos = recv(socket_do_cliente, mensagem, MAX_SIZE, 0);

		if(num_bytes_recebidos < 0)
            informa_erro_e_termina_programa("Falha no recv() ao receber mensagem do equipamento.\n");
        else if(num_bytes_recebidos == 0){
            if(DEBUG == true)
                printf("Conexao encerrada pelo equipamento %d.\n", indice);

			printf("Equipment %d removed\n", indice);
            close(socket_do_cliente);
            return NULL;
        }


		mensagem[num_bytes_recebidos] = '\0';
		printf("recebido no servidor: %s", mensagem); // mensagem[strlen(mensagem) - 1] == '\n'

		char resposta_para_cliente[MAX_SIZE]; // TODO: resposta para o equipamento?

		mensagem_para_retornar = processar_comando(mensagem);
		if(mensagem_para_retornar == NULL){
			printf("Mensagem desconhecida enviada por equipamento.\nA conexao com cliente sera encerrada.\n");
			close(socket_do_cliente);
			return NULL;
		}

		if(strcmp(mensagem_para_retornar, "close connection") == 0){
			if(DEBUG == true)
				printf("Comando 'close connection' recebido.\nA conexao com o equipamento sera encerrada.\n");

			strcpy(resposta_para_cliente, "Sucess");

			// TODO: Enviar mensagem também a outros equipamentos conectados

			ssize_t num_bytes_enviados = send(socket_do_cliente, resposta_para_cliente, strlen(resposta_para_cliente), 0);
			verificar_erro_envio_de_mensagem(num_bytes_enviados, strlen(resposta_para_cliente));

			close(socket_do_cliente);
			return NULL;
		}

		ssize_t num_bytes_enviados = send(socket_do_cliente, mensagem_para_retornar, strlen(mensagem_para_retornar), 0);
		verificar_erro_envio_de_mensagem(num_bytes_enviados, strlen(mensagem_para_retornar));
	}	

	close(socket_do_cliente);

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

	// Inicializa os equipamentos com valores padrão
	inicializar_equipamentos(vetor_de_equipamentos);

	// TODO: Como limitar o número de equipamentos conectados?
	while(true){
		if(contador_clientes == 10)
			continue;
		else if(contador_clientes <= 9){
			// Espera conexão de equipamento
			socket_do_cliente = accept(socket_do_servidor,
				(struct sockaddr*) &vetor_de_equipamentos[contador_clientes].endereco_equipamento,
				&vetor_de_equipamentos[contador_clientes].tamanho);
			if(socket_do_cliente < 0)
				informa_erro_e_termina_programa("Falha no accept().\nEquipamento nao conectado\n");

			vetor_de_equipamentos[contador_clientes].socket_id = socket_do_cliente;
			vetor_de_equipamentos[contador_clientes].indice = contador_clientes;

			printf("Equipment %d added\n", contador_clientes);
			// TODO: BROADCAST que equipamento foi adicionado (2.b.1)
			// TODO: Enviar a este equipamento a lista de equip. conectados na rede

			int valor_de_retorno = pthread_create(&vetor_de_threads[contador_clientes], NULL, comunicar,
				(void *) &vetor_de_equipamentos[contador_clientes]);
			if(valor_de_retorno != 0){
				printf("Thread %lu: ", (unsigned long int) vetor_de_threads[contador_clientes]);
				informa_erro_e_termina_programa("Falha no pthread_create().\n");
			}

			contador_clientes++;
		}
 
	}

	for(int i = 0; i < contador_clientes; i++)
		pthread_join(vetor_de_threads[i], NULL);

	return 0;
}