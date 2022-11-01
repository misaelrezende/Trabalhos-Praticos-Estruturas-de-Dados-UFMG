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
#define DEBUG true

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

void listar_switches(Rack *racks, int rack_da_operacao){
    if(racks[rack_da_operacao - 1].quantidade_switches_alocados == 0)
        informa_erro_e_termina_programa("empty rack");

    int switches_impressos = 0;
    for(int i = 0; i < MAX_SWITCH; i++){
        if(racks[rack_da_operacao - 1].switchs[i].id_switch != -1){

            if(switches_impressos == racks[rack_da_operacao - 1].quantidade_switches_alocados - 1){
                printf("%d\n", racks[rack_da_operacao - 1].switchs[i].id_switch);
                break;
            }else{
                printf("%d ", racks[rack_da_operacao - 1].switchs[i].id_switch);
                switches_impressos += 1;
            }
        }
    }

}

void ler_dados_de_switches(Rack *racks, int rack_da_operacao, int *switches_para_operar, int contador_switches){
    if(racks[rack_da_operacao - 1].quantidade_switches_alocados == 0)
        informa_erro_e_termina_programa("error switch doesn't exist");

    int switches_impressos = 0;
    int limite_superior = 5000;
    int limite_inferior = 1;
    bool switch_encontrado = false;

    for(int j = 0; j < contador_switches; j++){

        if(racks[rack_da_operacao - 1].switchs[ switches_para_operar[j] ].id_switch == switches_para_operar[j]){

            int numero_randomico = (rand() % (limite_superior + 1 - limite_inferior));

            if(switches_impressos == contador_switches - 1){ // último a ser impresso
                printf("%d Kbs\n", numero_randomico);
                switch_encontrado = true;
                break;
            }else{
                printf("%d Kbs ", numero_randomico);
                switches_impressos += 1;
                switch_encontrado = true;
            }
        }

    }

    // Caso switch não tenha sido instalado no rack
    if(switch_encontrado == false)
        informa_erro_e_termina_programa("error switch doesn't exist");

}

void remover_switch(Rack *racks, int rack_da_operacao, int *switches_para_operar){
    // Rack vazio, não há nenhum switch a ser removido
    if(racks[ rack_da_operacao - 1].quantidade_switches_alocados == 0)
        informa_erro_e_termina_programa("error switch doesn't exist");
    else if(racks[ rack_da_operacao - 1 ].switchs[ switches_para_operar[0] ].id_switch == switches_para_operar[0]){
        // Remove switch
        racks[ rack_da_operacao - 1 ].switchs[ switches_para_operar[0] ].id_switch = -1;
        // Diminui por 1 o número de switches alocados
        racks[ rack_da_operacao - 1].quantidade_switches_alocados -= 1;

        // TODO: Falta enviar o nome do switch e do rack
        informa_erro_e_termina_programa("switch <switch_id> removed from <rack_id>");
    }else{
        informa_erro_e_termina_programa("error switch doesn't exist");
    }
}

// Processa o comando recebido
void processar_comando(char *mensagem, Rack *racks){
    char *palavra; palavra = strtok(mensagem, " ");
    int switches_para_operar[3] = {0,0,0};
    int contador_switches = 0;
    int rack_da_operacao = -1;

    if(strcmp(palavra, "add") == 0){
        printf("comando digitado: %s\n", palavra);
        
        palavra = strtok(NULL, " ");
        printf("palavra atual: %s\n", palavra);
        if(strcmp(palavra, "sw") != 0){
            // TODO: Mensagem desconhecida, ENCERRAR CONEXÃO
            printf(">> mensagem [%s] desconhecida\nENCERRAR CONEXÃO\n", palavra);
        }

        while(palavra != NULL){
            palavra = strtok(NULL, " ");
            printf("palavra atual: %s\n", palavra);

            if(palavra == NULL)
                break;
            if(strcmp(palavra, "in") == 0){
                palavra = strtok(NULL, " ");
                rack_da_operacao = atoi(palavra);
                if(rack_da_operacao < 1 || rack_da_operacao > MAX_RACK){
                    informa_erro_e_termina_programa("error rack doesn't exist\n");
                    break; // pode ser desnecessário
                }
            }
            else if(strcmp(palavra, "sw") == 0){ // NOTE: Não vai entrar aqui mais não - pode apagar esse 'else if'
                printf("\n\n>>>UAI, NAO EH PRA ENTRAR AQUI NAO SOO!\n\n");
                continue;
            }
            else{
                int switch_id = atoi(palavra);
                if(switch_id < 1 || switch_id > 4){ // tipo inválido de switch
                    informa_erro_e_termina_programa("error switch type unknown");
                    break; // pode ser desnecessário
                }
                if(contador_switches > 3){  // ultrapassa limite de switches TODO: DAR BREAK E RETORNAR MSG
                    informa_erro_e_termina_programa("error rack limit exceeded");
                    break; // pode ser desnecessário
                }
                switches_para_operar[contador_switches] = switch_id;
                contador_switches += 1;
            }

        }
        // NOTE: PRINTS EXTRAS
        printf("contado_switches: %d | ", contador_switches);
        for(int i = 0; i < 3; i++)
            printf("%d ", switches_para_operar[i]);
        printf(" | rack_da_operacao: %d\n", rack_da_operacao);

        // Adiciona switch(s) no rack
        adicionar_switch(racks, rack_da_operacao, switches_para_operar, contador_switches);

    }else if(strcmp(palavra, "rm") == 0){
        printf("comando digitado: %s\n", palavra);

        palavra = strtok(NULL, " ");
        printf("palavra atual: %s\n", palavra);
        if(strcmp(palavra, "sw") != 0){
            // TODO: Mensagem desconhecida, ENCERRAR CONEXÃO
            printf(">> mensagem [%s] desconhecida\nENCERRAR CONEXÃO\n", palavra); // tratamento EXTRA
        }

        while(palavra != NULL){
            palavra = strtok(NULL, " ");
            printf("palavra atual: %s\n", palavra);

            if(palavra == NULL)
                break;
            if(strcmp(palavra, "in") == 0){
                palavra = strtok(NULL, " ");
                rack_da_operacao = atoi(palavra);
                if(rack_da_operacao < 1 || rack_da_operacao > MAX_RACK){
                    informa_erro_e_termina_programa("error rack doesn't exist\n"); // tratamento EXTRA
                    break; // pode ser desnecessário
                }
            }
            else{
                int switch_id = atoi(palavra);
                if(switch_id < 1 || switch_id > 4){ // tipo inválido de switch
                    informa_erro_e_termina_programa("error switch type unknown");
                    break; // pode ser desnecessário
                }
                switches_para_operar[contador_switches] = switch_id;
                contador_switches += 1;
            }

        }
        // NOTE: PRINTS EXTRAS
        printf("contado_switches: %d | ", contador_switches);
        for(int i = 0; i < 3; i++)
            printf("%d ", switches_para_operar[i]);
        printf(" | rack_da_operacao: %d\n", rack_da_operacao);

        remover_switch(racks, rack_da_operacao, switches_para_operar);

    }else if(strcmp(palavra, "get") == 0){
        printf("comando digitado: %s\n", palavra);

        while(palavra != NULL){
            palavra = strtok(NULL, " ");
            printf("palavra atual: %s\n", palavra);

            if(palavra == NULL)
                break;
            if(strcmp(palavra, "in") == 0){
                palavra = strtok(NULL, " ");
                rack_da_operacao = atoi(palavra);
                if(rack_da_operacao < 1 || rack_da_operacao > MAX_RACK){
                    informa_erro_e_termina_programa("error rack doesn't exist\n");
                    break; // pode ser desnecessário
                }
            }else{
                int switch_id = atoi(palavra);
                if(switch_id < 1 || switch_id > 4){ // tipo inválido de switch
                    informa_erro_e_termina_programa("error switch type unknown");
                    break; // pode ser desnecessário
                }
                switches_para_operar[contador_switches] = switch_id;
                contador_switches += 1;
            }

        }
        // NOTE: PRINTS EXTRAS
        printf("contado_switches: %d | ", contador_switches);
        for(int i = 0; i < 3; i++)
            printf("%d ", switches_para_operar[i]);
        printf(" | rack_da_operacao: %d\n", rack_da_operacao);

        ler_dados_de_switches(racks, rack_da_operacao, switches_para_operar, contador_switches);

    }else if(strcmp(palavra, "ls") == 0){
        printf("comando digitado: %s\n", palavra);

        while(palavra != NULL){
            palavra = strtok(NULL, " ");
            printf("palavra atual: %s\n", palavra);

            if(palavra == NULL)
                break;

            rack_da_operacao = atoi(palavra);
            if(rack_da_operacao < 1 || rack_da_operacao > MAX_RACK){
                informa_erro_e_termina_programa("error rack doesn't exist\n");
                break; // pode ser desnecessário
            }
        }

        listar_switches(racks, rack_da_operacao);

    }else{
        // TODO: Se receber mensagem desconhecida, ENCERRAR CONEXÃO
        printf(">> mensagem [%s] desconhecida\nENCERRAR CONEXÃO\n", palavra);
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
