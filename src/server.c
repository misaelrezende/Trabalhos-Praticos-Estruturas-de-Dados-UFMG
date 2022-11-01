#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // _Bool
#include <time.h> // rand()
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_RACK   4 // número máximo de racks
#define MAX_SWITCH 3 // número máximo de switchs
#define BUFFER_SIZE 200  // message max size
static const int MAXPENDING = 1; // Pedidos de conexão pendentes máximos
#define DEBUG false

typedef struct{
    int id_switch; // switch id
} Switch;

typedef struct{
    int quantidade_switches_alocados;
    Switch switchs[MAX_SWITCH];
} Rack;

void informa_erro_e_termina_programa(char *mensagem){
    printf("%s", mensagem);
    exit(1);
}

/* Inicializa racks
   Assume que racks tem ids de 1 a 4.
*/
void inicializar_racks(Rack *racks){
    for(int i = 0; i < MAX_RACK; i++){
        racks[i].quantidade_switches_alocados = 0;
        for(int j = 0; j < MAX_SWITCH; j++)
            racks[i].switchs[j].id_switch = -1;
    }
}

// Cria conexão TCP
int criar_conexao_tcp(char *tipo_de_endereco){
    int sock;
    bool ipv4 = false;
    if(strcmp(tipo_de_endereco, "v4") == 0)
        ipv4 = true;

    if(ipv4 == true)
        // Cria um socket IPv4 usando TCP
        sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    else
        // Cria um socket IPv6 usando TCP
        sock = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);

    if(sock < 0)
        informa_erro_e_termina_programa("Falha em iniciar conexao socket.\n");

    return sock;
}

// Abre conexão TCP
void abrir_conexao_tcp(int tcp_socket, int numero_de_porta, char *tipo_de_endereco){
    if(strcmp(tipo_de_endereco, "v4") == 0){
        // Construct local address structure
        struct sockaddr_in endereco_servidor;                       // Local address
        memset(&endereco_servidor, 0, sizeof(endereco_servidor));   // Zero out structure
        endereco_servidor.sin_family = AF_INET;                     // IPv4 address family
        endereco_servidor.sin_addr.s_addr = htonl(INADDR_ANY);      // Any incoming interface
        endereco_servidor.sin_port = htons(numero_de_porta);        // Local port

        // Bind to the local address
        if(bind(tcp_socket, (struct sockaddr*) &endereco_servidor, sizeof(endereco_servidor)) < 0){
            // Fecha a conexão devido a erro
            close(tcp_socket);
            informa_erro_e_termina_programa("Falha no bind()\n");
        }
    }else if(strcmp(tipo_de_endereco, "v6") == 0){
        // Construct local address structure
        struct sockaddr_in6 endereco_servidor;                      // local address
        memset(&endereco_servidor, 0, sizeof(endereco_servidor));   // Zero out structure
        endereco_servidor.sin6_family = AF_INET6;                   // IPv6 address family
        endereco_servidor.sin6_addr = in6addr_any;                  // Any incoming interface
        endereco_servidor.sin6_port = htons(numero_de_porta);       // Local port

        // Bind to the local address
        if(bind(tcp_socket, (struct sockaddr*) &endereco_servidor, sizeof(endereco_servidor)) < 0){
            // Fecha a conexão devido a erro
            close(tcp_socket);
            informa_erro_e_termina_programa("Falha no bind()\n");
        }
    }

    // Abrir escuta para conexão de cliente
    if(listen(tcp_socket, MAXPENDING) < 0){
        // Fecha a conexão devido a erro
        close(tcp_socket);
        informa_erro_e_termina_programa("Falha no listen()\n");
    }

    if(DEBUG == true)
        printf(">> Servidor escutando na porta %i\n", numero_de_porta);
}

// Adiciona switch(es) no rack
char* adicionar_switch(Rack *racks, int rack_da_operacao, int *switches_para_operar, int contador_switches){
    char mensagem_de_retorno[BUFFER_SIZE] = "", *ptr_msg_retorno;

    if(racks[rack_da_operacao - 1].quantidade_switches_alocados + contador_switches > MAX_SWITCH){
        strcat(mensagem_de_retorno, "error rack limit exceeded\n");
        ptr_msg_retorno = mensagem_de_retorno;
        return ptr_msg_retorno;
    }

    int switches_alocados = 0;
    char switch_id[2], rack_id[2];

    for(int i = 0; i < contador_switches; i++){
        if(switches_para_operar[i] != 0){

            // Checa se switch já está instalado neste rack
            if(racks[rack_da_operacao - 1].switchs[ switches_para_operar[i] ].id_switch == switches_para_operar[i]){
                strcat(mensagem_de_retorno, "error switch ");
                sprintf(switch_id, "%d", switches_para_operar[i]);  // converte id (int to char)
                sprintf(rack_id, "%d", rack_da_operacao);           // converte id (int to char)

                strcat(mensagem_de_retorno, switch_id);
                strncat(mensagem_de_retorno, " already installed in ", 50);
                strcat(mensagem_de_retorno, rack_id);
                strcat(mensagem_de_retorno, "\n");
                // return *mensagem_de_retorno;
                ptr_msg_retorno = mensagem_de_retorno;
                return ptr_msg_retorno;
            }

            racks[rack_da_operacao - 1].switchs[ switches_para_operar[i] ].id_switch = switches_para_operar[i];
            racks[rack_da_operacao - 1].quantidade_switches_alocados += 1;

            switches_alocados += 1;

            sprintf(switch_id, "%d", switches_para_operar[i]); // converte id (int to char)
            if(switches_alocados == 1){
                strcat(mensagem_de_retorno,"switch ");
                strcat(mensagem_de_retorno, switch_id);
            }else if(switches_alocados == contador_switches){ // ultimo switch alocado
                strcat(mensagem_de_retorno, " ");
                strcat(mensagem_de_retorno, switch_id);
            }else{ // ainda nao eh ultimo switch nao
                strcat(mensagem_de_retorno, " ");
                strcat(mensagem_de_retorno, switch_id);
            }
        }
    }

    strcat(mensagem_de_retorno, " installed\n");
    ptr_msg_retorno = mensagem_de_retorno;
    return ptr_msg_retorno;
}

// Lista switch(es) do rack
char* listar_switches(Rack *racks, int rack_da_operacao){
    char mensagem_de_retorno[BUFFER_SIZE] = "", *ptr_msg_retorno;
    char switch_id[2];

    if(racks[rack_da_operacao - 1].quantidade_switches_alocados == 0){
        strcat(mensagem_de_retorno, "empty rack\n");
        ptr_msg_retorno = mensagem_de_retorno;
        return ptr_msg_retorno;
    }

    int switches_impressos = 0;
    for(int i = 0; i < MAX_SWITCH; i++){
        if(racks[rack_da_operacao - 1].switchs[i].id_switch != -1){

            sprintf(switch_id, "%d", racks[rack_da_operacao - 1].switchs[i].id_switch); // converte id (int to char)
            if(switches_impressos == racks[rack_da_operacao - 1].quantidade_switches_alocados - 1){
                strcat(mensagem_de_retorno, switch_id);
                strcat(mensagem_de_retorno, "\n");
                break;
            }else{
                switches_impressos += 1;
                strcat(mensagem_de_retorno, switch_id);
                strcat(mensagem_de_retorno, " ");
            }
        }
    }
    ptr_msg_retorno = mensagem_de_retorno;
    return ptr_msg_retorno;
}

// Lê dados sobre velocidade de tráfego dos switches
char* ler_dados_de_switches(Rack *racks, int rack_da_operacao, int *switches_para_operar, int contador_switches){
    char mensagem_de_retorno[BUFFER_SIZE] = "", *ptr_msg_retorno;
    char velocidade[10];
    if(racks[rack_da_operacao - 1].quantidade_switches_alocados == 0){
        strcat(mensagem_de_retorno, "error switch doesn't exist\n");
        ptr_msg_retorno = mensagem_de_retorno;
        return ptr_msg_retorno;
    }

    int switches_impressos = 0;
    int limite_superior = 5000;
    int limite_inferior = 1;
    bool switch_encontrado = false;

    for(int j = 0; j < contador_switches; j++){

        if(racks[rack_da_operacao - 1].switchs[ switches_para_operar[j] ].id_switch == switches_para_operar[j]){

            int numero_randomico = (rand() % (limite_superior + 1 - limite_inferior));
            sprintf(velocidade, "%d", numero_randomico);    // converte id (int to char*)

            if(switches_impressos == contador_switches - 1){ // último a ser impresso
                if(contador_switches == 1)
                    strcat(mensagem_de_retorno, velocidade);
                else
                    strcat(mensagem_de_retorno, velocidade);
                strcat(mensagem_de_retorno, " Kbs\n");
                switch_encontrado = true;
                break;
            }else{
                strcat(mensagem_de_retorno, velocidade);
                strcat(mensagem_de_retorno, " Kbs ");
                switches_impressos += 1;
                switch_encontrado = true;
            }
        }

    }

    // Caso switch não tenha sido instalado no rack
    if(switch_encontrado == false){
        strcat(mensagem_de_retorno, "error switch doesn't exist\n");
        ptr_msg_retorno = mensagem_de_retorno;
        return ptr_msg_retorno;
    }

    ptr_msg_retorno = mensagem_de_retorno;
    return ptr_msg_retorno;

}

// Remove switch de rack
char* remover_switch(Rack *racks, int rack_da_operacao, int *switches_para_operar){
    char mensagem_de_retorno[BUFFER_SIZE] = "", *ptr_msg_retorno;
    char switch_id[2], rack_id[2];

    // Rack vazio, não há nenhum switch a ser removido
    if(racks[ rack_da_operacao - 1].quantidade_switches_alocados == 0){
        strcat(mensagem_de_retorno, "error switch doesn't exist\n");
        ptr_msg_retorno = mensagem_de_retorno;
        return ptr_msg_retorno;
    }
    else if(racks[ rack_da_operacao - 1 ].switchs[ switches_para_operar[0] ].id_switch == switches_para_operar[0]){
        // Remove switch
        racks[ rack_da_operacao - 1 ].switchs[ switches_para_operar[0] ].id_switch = -1;
        // Diminui por 1 o número de switches alocados
        racks[ rack_da_operacao - 1].quantidade_switches_alocados -= 1;

        strcat(mensagem_de_retorno, "switch ");

        sprintf(switch_id, "%d", switches_para_operar[0]);  // converte id (int to char)
        sprintf(rack_id, "%d", rack_da_operacao);           // converte id (int to char)

        strcat(mensagem_de_retorno, switch_id);
        strcat(mensagem_de_retorno, " removed from ");
        strcat(mensagem_de_retorno, rack_id);
        strcat(mensagem_de_retorno, "\n");
        ptr_msg_retorno = mensagem_de_retorno;
        return ptr_msg_retorno;
    }else{
        strcat(mensagem_de_retorno, "error switch doesn't exist\n");
        ptr_msg_retorno = mensagem_de_retorno;
        return ptr_msg_retorno;
    }
}

// Processa o comando recebido
char* processar_comando(char *mensagem, Rack *racks){
    if(DEBUG == true)
        printf("Processando mensagem: %s\n", mensagem);

    char mensagem_de_retorno[BUFFER_SIZE] = "", *ptr_msg_retorno;;
    char *palavra; palavra = strtok(mensagem, " ");
    int switches_para_operar[3] = {0,0,0};
    int contador_switches = 0;
    int rack_da_operacao = -1;

    if(strcmp(palavra, "add") == 0){
        
        palavra = strtok(NULL, " ");
        if(DEBUG == true)
            printf("palavra atual: %s\n", palavra);
        if(strcmp(palavra, "sw") != 0){
            printf("Mensagem [%s] desconhecida\nA conexao sera encerrada\n", palavra);
            return NULL;
        }

        while(palavra != NULL){
            palavra = strtok(NULL, " ");
            if(DEBUG == true)
                printf("palavra atual: %s\n", palavra);

            if(palavra == NULL)
                break;
            if(strcmp(palavra, "in") == 0){
                palavra = strtok(NULL, " ");
                rack_da_operacao = atoi(palavra);
                if(rack_da_operacao < 1 || rack_da_operacao > MAX_RACK){
                    strcat(mensagem_de_retorno, "error rack doesn't exist\n");
                    ptr_msg_retorno = mensagem_de_retorno;
                    return ptr_msg_retorno;
                }
            }
            else{
                int switch_id = atoi(palavra);
                if(switch_id < 1 || switch_id > 4){ // tipo inválido de switch
                    strcat(mensagem_de_retorno, "error switch type unknown\n");
                    ptr_msg_retorno = mensagem_de_retorno;
                    return ptr_msg_retorno;
                }
                if(contador_switches > 3){  // ultrapassa limite de switches
                    strcat(mensagem_de_retorno, "error rack limit exceeded\n");
                    ptr_msg_retorno = mensagem_de_retorno;
                    return ptr_msg_retorno;
                }
                switches_para_operar[contador_switches] = switch_id;
                contador_switches += 1;
            }

        }

        // Adiciona switch(s) no rack
        ptr_msg_retorno = adicionar_switch(racks, rack_da_operacao, switches_para_operar, contador_switches);
        return ptr_msg_retorno;

    }else if(strcmp(palavra, "rm") == 0){

        palavra = strtok(NULL, " ");
        if(DEBUG == true)
            printf("palavra atual: %s\n", palavra);
        if(strcmp(palavra, "sw") != 0){
            printf("Mensagem [%s] desconhecida\nA conexao sera encerrada\n", palavra); // tratamento EXTRA
            return NULL;
        }

        while(palavra != NULL){
            palavra = strtok(NULL, " ");
            if(DEBUG == true)
                printf("palavra atual: %s\n", palavra);

            if(palavra == NULL)
                break;
            if(strcmp(palavra, "in") == 0){
                palavra = strtok(NULL, " ");
                rack_da_operacao = atoi(palavra);
                if(rack_da_operacao < 1 || rack_da_operacao > MAX_RACK){
                    strcat(mensagem_de_retorno, "error rack doesn't exist\n");
                    ptr_msg_retorno = mensagem_de_retorno;
                    return ptr_msg_retorno;
                }
            }
            else{
                int switch_id = atoi(palavra);
                if(switch_id < 1 || switch_id > 4){ // tipo inválido de switch
                    strcat(mensagem_de_retorno, "error switch type unknown\n");
                    ptr_msg_retorno = mensagem_de_retorno;
                    return ptr_msg_retorno;
                }
                switches_para_operar[contador_switches] = switch_id;
                contador_switches += 1;
            }

        }

        ptr_msg_retorno = remover_switch(racks, rack_da_operacao, switches_para_operar);
        return ptr_msg_retorno;

    }else if(strcmp(palavra, "get") == 0){

        while(palavra != NULL){
            palavra = strtok(NULL, " ");
            if(DEBUG == true)
                printf("palavra atual: %s\n", palavra);

            if(palavra == NULL)
                break;
            if(strcmp(palavra, "in") == 0){
                palavra = strtok(NULL, " ");
                rack_da_operacao = atoi(palavra);
                if(rack_da_operacao < 1 || rack_da_operacao > MAX_RACK){ // tratamento EXTRA
                    strcat(mensagem_de_retorno, "error rack doesn't exist\n");
                    ptr_msg_retorno = mensagem_de_retorno;
                    return ptr_msg_retorno;
                }
            }else{
                int switch_id = atoi(palavra);
                if(switch_id < 1 || switch_id > 4){ // tipo inválido de switch
                    strcat(mensagem_de_retorno, "error switch type unknown\n"); // tratamento EXTRA
                    ptr_msg_retorno = mensagem_de_retorno;
                    return ptr_msg_retorno;
                }
                switches_para_operar[contador_switches] = switch_id;
                contador_switches += 1;
            }

        }

        ptr_msg_retorno = ler_dados_de_switches(racks, rack_da_operacao, switches_para_operar, contador_switches);
        return ptr_msg_retorno;

    }else if(strcmp(palavra, "ls") == 0){

        while(palavra != NULL){
            palavra = strtok(NULL, " ");
            if(DEBUG == true)
                printf("palavra atual: %s\n", palavra);

            if(palavra == NULL)
                break;

            rack_da_operacao = atoi(palavra);
            if(rack_da_operacao < 1 || rack_da_operacao > MAX_RACK){
                strcat(mensagem_de_retorno, "error rack doesn't exist\n");
                ptr_msg_retorno = mensagem_de_retorno;
                return ptr_msg_retorno;
            }
        }

        ptr_msg_retorno = listar_switches(racks, rack_da_operacao);
        return ptr_msg_retorno;

    }else if(strcmp(palavra, "exit") == 0){
        strcat(mensagem_de_retorno, "exit");
        ptr_msg_retorno = mensagem_de_retorno;
        return ptr_msg_retorno;
    }else{
        printf("Mensagem [%s] desconhecida\nA conexao sera encerrada\n", palavra);
        return NULL;
    }

    ptr_msg_retorno = mensagem_de_retorno;
    return ptr_msg_retorno;
}


void tratar_conexao_cliente(int socket_do_servidor, int socket_do_cliente){
    Rack *racks = calloc(MAX_RACK, sizeof(Rack));
    inicializar_racks(racks);

    char buffer[BUFFER_SIZE] = "";
    ssize_t num_bytes_recebidos;
    char resposta_para_cliente[BUFFER_SIZE] = "", mensagem[BUFFER_SIZE] = "";
    char *mensagem_para_retornar = NULL;

    do{ // Desde que tenha alguma solicitação do cliente, faça:
        num_bytes_recebidos = recv(socket_do_cliente, buffer, BUFFER_SIZE, 0);
        if(num_bytes_recebidos < 0)
            informa_erro_e_termina_programa("Falha no recv() ao receber mensagem do cliente.\n");
        else if(num_bytes_recebidos == 0){
            if(DEBUG == true)
                printf("Conexao encerrada pelo cliente.\n");
            close(socket_do_cliente);
            return;
        }

        // imprime a mensagem enviada pelo cliente
        printf("<< %s", buffer);

        mensagem[BUFFER_SIZE] = "";
        // Remove o caractere '\n'
        strncpy(mensagem, buffer, strlen(buffer) - 1);
        mensagem_para_retornar = processar_comando(mensagem, racks);

        if(mensagem_para_retornar == NULL){
            printf("Mensagem desconhecida enviada por cliente.\nA conexao com cliente sera encerrada.\n");
            close(socket_do_cliente);
            return;
        }
        if(strcmp(mensagem_para_retornar, "exit") == 0){
            printf("Comando exit recebido.\nEncerrando cliente e servidor.\n");
            close(socket_do_cliente);
            close(socket_do_servidor);
            free(racks);
            exit(1);
        }

        // Concatena resposta para enviar a cliente
        strcat(resposta_para_cliente, mensagem_para_retornar);
        strcat(resposta_para_cliente, "\n");
        ssize_t num_bytes_enviados = send(socket_do_cliente, resposta_para_cliente, strlen(resposta_para_cliente), 0);

        if (num_bytes_enviados < 0) // no message was sent
            informa_erro_e_termina_programa("Falha no send() ao enviar mensagem.\n");
        // else if(num_bytes_enviados != num_bytes_recebidos)
        //     DieWithUserMessage("sendto()", "sent unexpected number of bytes");

        // reseta buffer, resposta_para_cliente e mensagem
        memset(&buffer, 0, sizeof(buffer));
        memset(&resposta_para_cliente, 0, sizeof(resposta_para_cliente));
        memset(&mensagem, 0, sizeof(mensagem));

    }while(num_bytes_recebidos > 0);

    close(socket_do_cliente);
    free(racks);
}

void comunicar_ipv4(int socket_do_servidor){
    struct sockaddr_in endereco_cliente;
    socklen_t tamanho_endereco_cliente;
    int socket_do_cliente;

    while(true){
        tamanho_endereco_cliente = sizeof(endereco_cliente);

        // Espera conexão de cliente
        socket_do_cliente = accept(socket_do_servidor, (struct sockaddr *) &endereco_cliente, &tamanho_endereco_cliente);
        if(socket_do_cliente < 0)
            informa_erro_e_termina_programa("Falha no accept().");

        if(DEBUG == true)
            printf("Clinte agora esta conectado.");

        char nome_do_cliente[INET_ADDRSTRLEN];
        if(inet_ntop(AF_INET, &endereco_cliente.sin_addr.s_addr, nome_do_cliente,
            sizeof(nome_do_cliente)) != NULL)
            if(DEBUG == true)
                printf("Cliente %s | %d\n", nome_do_cliente, ntohs(endereco_cliente.sin_port));
        else
            if(DEBUG == true)
                printf("Nao eh possivel obter endereco do cliente");

        tratar_conexao_cliente(socket_do_servidor, socket_do_cliente);
    }
}

void comunicar_ipv6(int socket_do_servidor){
    struct sockaddr_in6 endereco_cliente;
    socklen_t tamanho_endereco_cliente;
    int socket_do_cliente;

    while(true){
        tamanho_endereco_cliente = sizeof(endereco_cliente);

        // Espera conexão de cliente
        socket_do_cliente = accept(socket_do_servidor, (struct sockaddr *) &endereco_cliente, &tamanho_endereco_cliente);
        if(socket_do_cliente < 0)
            informa_erro_e_termina_programa("Falha no accept().");

        if(DEBUG == true)
            printf("Clinte agora esta conectado.");

        char nome_do_cliente[INET6_ADDRSTRLEN];
        if(inet_ntop(AF_INET6, &endereco_cliente.sin6_addr.s6_addr, nome_do_cliente,
            sizeof(nome_do_cliente)) != NULL)
            if(DEBUG == true)
                printf("Cliente %s | %d\n", nome_do_cliente, ntohs(endereco_cliente.sin6_port));
        else
            if(DEBUG == true)
                printf("Nao eh possivel obter endereco do cliente");

        tratar_conexao_cliente(socket_do_servidor, socket_do_cliente);
    }
}


int main(int argc, char *argv[]){
    // Args:
    // Tipo do endereço
    // Número de porta
    if(argc != 3){
        fprintf(stderr,
        "O servidor precisa de exatamente de 2 parametros de entrada:\n\
        ./server <tipo de endereco '<v4|v6>'> <numero da porta>\n");
        exit(1);
    }

    char *tipo_de_endereco = argv[1];
    int numero_de_porta = atoi(argv[2]);

    int socket_do_servidor = criar_conexao_tcp(tipo_de_endereco);
    abrir_conexao_tcp(socket_do_servidor, numero_de_porta, tipo_de_endereco);

    if(strcmp(tipo_de_endereco, "v4") == 0)
        comunicar_ipv4(socket_do_servidor);
    else if(strcmp(tipo_de_endereco, "v6") == 0)
        comunicar_ipv6(socket_do_servidor);

    return 0;
}
