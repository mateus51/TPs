// programa writer cujo objetivo é ser a interface de escrita do chat
//@param host_do_servidor porto_servidor uid
//@host_do_servidor = nome do servidor ex(localhost,127.0.0.1)
//@porto_servidor = porto em que o servidor esta "bind"
//@uid = identificador unico do writer

//bibliotecas utilizadas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include "protocolo.h" 

//funcao de auxilio para informar erros e abortar
void error(char *msg)
{
    printf("\n%s\n", msg);
    exit(0);
}
//funcao de auxilio para informar como usar o programa
void usage()
{
    printf("Usage: \n ./writer host_server port uid\n"); 
    printf("\t host_server: \t  Nome do servidor\n"); 
    printf("\t port: \t\t  Porto do servidor\n"); 
    printf("\t uid: \t\t  identificador único do cliente (1001-1999)\n"); 
} 

int main(int argc, char *argv[])
{
    //verifica numero de argumentos
    if (argc != 4) {
        usage();	
        error("Numero de argumentos invalido");	 
    }else if( atoi(argv[3]) > 1999 || atoi(argv[3]) < 1001 ){
        usage();
        error("Identificador inválido");
    } 

    //declaracoes iniciais 
    int sockfd, port=atoi(argv[2]), n, totalBytes=0, totalMsg=0;
    short int uid = atoi(argv[3]);
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[145];
    short int destino_uid = 0, tipo_msg;
    Mensagem msg;

    //cria o novo socket TCP
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){ 
        error("ERROR abrindo o socket\n");
    }

    //Pega o endereço do server
    server = gethostbyname(argv[1]);

    //verifica se foi possivel encontrar o endereco do host
    if (server == NULL) {
        error("Host nao encontrado\n");
    }

    //define o address family do sockaddr_in 
    serv_addr.sin_family= AF_INET;

    //define o porto a ser utilizado, lembrando de converter antes para network byte order
    serv_addr.sin_port=htons(port);

    //copia o endereco ip do servidor pego pelo gethostbyname, para o serv_addr 
    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);

    //faz a abertura ativa
    if( connect(sockfd,(const struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
        printf("Server end: \t %s\n", server->h_name);
        printf("Server port:\t %d\n", port);
        error("Erro na conexao com o servidor\n"); 
    }


    empacota(&msg,0,uid,0,2,"OI");
	n = write(sockfd,&msg,sizeof(msg));
    if ( n < 0 ){
        error("Falha na escrita para o socket\n");
    }

    if((n=recv(sockfd,&msg,sizeof(msg),0)) < 0){
        error("recv");
    }else{
        if(getType(&msg) == 1) 
            error("Conexão recusada pelo servidor\n");
    }


    //Loop principal da aplicação
    while(1) {

        printf("[1] Fechar conexão\n[2] Envio de texto\n");
        printf("Tipo desejado: ");
        fgets(buffer,141,stdin);
        buffer[2] = '\0';
        tipo_msg = atoi(buffer);
        if ( tipo_msg == 1 ){
            printf("Encerrando conexao...\n");
            n = write(sockfd,"",0);
            break;
        }else if ( tipo_msg == 2) {

            printf("[%d] Destino: ",uid);
            fgets(buffer,141,stdin);
            buffer[5]='\0';	
            destino_uid = atoi(buffer);

            if ( destino_uid > 999 || destino_uid < 0 ){
                printf("O destino náo é um uid viewer válido (1 - 999)\n");
                continue;
            }


            printf("Mensagem para %d: ", (int) destino_uid);
            fgets(buffer,141,stdin);

            tipo_msg=2;

            empacota(&msg,tipo_msg,uid,destino_uid,strlen(buffer) -1, buffer);
            n = write(sockfd,&msg,sizeof(msg));
            if ( n < 0 ){
                error("Falha na escrita para o socket\n");
            }
        }else{
            printf("O tipo escolhido náo é válido (1 -2)\n");
            continue;
        }
    }

    shutdown(sockfd,2);
}
