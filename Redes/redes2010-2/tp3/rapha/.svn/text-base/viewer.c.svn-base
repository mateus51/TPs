// programa client cujo objetivo e solicitar um arquivo ao servidor e gavar-lo em disco local
//@param host_do_servidor porto_servidor nome_arquivo tam_buffer
//@host_do_servidor = nome do servidor ex(localhost,127.0.0.1)
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
	printf("Usage: \n ./viewer host_server port uid\n"); 
	printf("\t host_server: \t  Nome do servidor\n"); 
	printf("\t port: \t\t  Porto do servidor\n"); 
	printf("\t uid: \t\t  identificador único do cliente (1-999)\n"); 
} 

int main(int argc, char *argv[])
{
	//verifica numero de argumentos
	if (argc != 4) {
		usage();	
		error("Numero de argumentos invalido");	 
	}else if( atoi(argv[3]) > 999 || atoi(argv[3]) < 1 ){
		usage();
		error("Identificador inválido");
	} 
   
	//declaracoes iniciais 
	int sockfd, port=atoi(argv[2]), n, totalBytes=0, totalMsg=0;
	short int uid = atoi(argv[3]);
	Mensagem msg;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[157];
	FILE *file;
    	

	//cria o novo socket TCP
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){ 
        	error("ERROR abrindo o socket");
	}

	//Pega o endereço do server
	server = gethostbyname(argv[1]);
	
	//verifica se foi possivel encontrar o endereco do host
	if (server == NULL) {
		error("Host nao encontrado");
	}

	//define o address family do sockaddr_in 
	serv_addr.sin_family= AF_INET;

	//define o porto a ser utilizado, lembrando de converter antes para network byte order
	serv_addr.sin_port=htons(port);

	//copia o endereco ip do servidor pego pelo gethostbyname, para o serv_addr 
	bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
		
	//faz a abertura ativa
	if( connect(sockfd,(const struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
		//imprime as informacoes da conexao
		printf("Server end: \t %s\n", server->h_name);
		printf("Server port:\t %d\n", port);
		error("Erro na conexao com o servidor"); 
	}



	empacota(&msg,0,uid,0,2,"OI");

	//envia mensagem de "OI" para o servidor 
	n = write(sockfd,&msg,sizeof(msg));
	if ( n < 0 ){
		error("Falha na escrita para o socket\n");
	}

	//Loop principal da aplicação
	while(1) {

		n=recv(sockfd, &msg, sizeof(msg),0);

		if ( n > 0 ){
			printf("Mensagem de %d: ", getOrigem(&msg));
			printf("%s\n", getMsg(&msg));
			if (getType(&msg) == 1) break;
		}else{
			printf("Conexão fechada pelo Servidor %s.\n ", argv[1]);
			break;
		} 
	}

	//fecha a conexao, para de receber e transmitir
	shutdown(sockfd,2);
	
}
