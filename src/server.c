#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // _Bool
#include <time.h> // rand()
// #include <netinet/in.h>
// #include <sys/socket.h>

#define MAX_RACK   4 // número máximo de racks
#define MAX_SWITCH 3 // número máximo de switchs

typedef struct{
    int id_switch; // switch id
} Switch;

typedef struct{
    int id_rack; // rack number
    int quantidade_switches_alocados;
    Switch switchs[MAX_SWITCH];
} Rack;

void informa_erro_e_termina_programa(char *mensagem){
    printf("%s", mensagem);
    exit(1);
}

// Inicializa racks
void inicializar_racks(Rack *racks){
    for(int i = 0; i < MAX_RACK; i++){
        racks[i].id_rack = i + 1;
        racks[i].quantidade_switches_alocados = 0;
        for(int j = 0; j < MAX_SWITCH; j++)
            racks[i].switchs[j].id_switch = -1;
    }
}

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

void adicionar_switch(Rack *racks, int rack_da_operacao, int *switches_para_operar, int contador_switches){
    if(racks[rack_da_operacao - 1].quantidade_switches_alocados + contador_switches > MAX_SWITCH)
        informa_erro_e_termina_programa("error rack limit exceeded");

    // Cria espaço para adicionar switch(es)
    printf(">> Chegou ate aqui\n");
    for(int i = 0; i < contador_switches; i++){
        if(switches_para_operar[i] != 0){

            // Checa se switch já está instalado neste rack
            if(racks[rack_da_operacao - 1].switchs[ switches_para_operar[i] ].id_switch == switches_para_operar[i])
                // TODO: Falta enviar o nome do switch e do rack
                informa_erro_e_termina_programa("error switch <switch_id> already installed in <rack_id>");

            racks[rack_da_operacao - 1].switchs[ switches_para_operar[i] ].id_switch = switches_para_operar[i];
            racks[rack_da_operacao - 1].quantidade_switches_alocados += 1;
            printf(">> Passou aqui tambem!\n");
        }
    }

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
    // if(argc != 3){
    //     fprintf(stderr,
    //     "O servidor precisa de exatamente de 2 parametros de entrada:\n\
    //     ./server <tipo de endereço '<v4|v6>'> <número da porta>\n");
    //     exit(1);
    // }

    // char *tipo_de_endereco = argv[1];
    // int numero_de_porta = atoi(argv[2]);
    char tipo_de_endereco[3], mensagem[30];
    // int numero_de_porta;
    // scanf("%s %d", tipo_de_endereco, &numero_de_porta);

    // int socket_do_servidor = criar_conexao_tcp(tipo_de_endereco);

    Rack *racks = calloc(MAX_RACK, sizeof(Rack));
    inicializar_racks(racks);

    while(true){
        printf("## Digite uma mensagem: ");
        fflush(stdin);
        fgets(mensagem, 30, stdin);
        processar_comando(mensagem, racks);
        // break;
    }

    return 0;
}
