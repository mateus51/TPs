#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h> 
#include "mensagem.h" 

void erro(char *msg)
{
  printf("\nERRO: %s\n", msg);
  exit(0);
}

void uso()
{
	printf("Uso: \n ./exibicao <host_server> <port> <uid>\n\n"); 
	printf("\t host_server: \t  Nome do servidor\n"); 
	printf("\t port: \t\t  Porto do servidor\n"); 
	printf("\t uid: \t\t  Identificador do cliente\n"); 
} 

int main(int argc, char *argv[])
{
  //Valida parametros
	if (argc != 4) 
  {
		uso();	
		erro("Erro nos parâmetros");	 
	}
  else if (atoi(argv[3]) > 999 || atoi(argv[3]) < 1)
  {
		uso();
		erro("Identificador inválido: deve ser entre 1 e 999");
	} 
   
  char* hostname = argv[1];
	int port = atoi(argv[2]); 
	short int uid = atoi(argv[3]);

	struct sockaddr_in serv_addr;
	struct hostent *server;

  //Cria o socket
  int sockfd;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
    erro("Nao foi possivel abrir o socket");

	//Pega o endereço do servidor
	server = gethostbyname(hostname);
	if (server == NULL) 
		erro("Host nao encontrado");

  //Preenche o serv_addr
  //Familia
	serv_addr.sin_family = AF_INET;
  //Porto
	serv_addr.sin_port = htons(port);
  //IP
	bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
		
  //Conecta
	if(connect(sockfd,(const struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
  {
    char msg_de_erro[100];
    sprintf(msg_de_erro, "Nao foi possivel se conectar ao servidor %s (%d)", server->h_name, port);
		erro(msg_de_erro); 
	}

  //Se identifica ao servidor
	msg_t msg;
	setMsg(&msg,OI,uid,0,0,"");
	if(write(sockfd,&msg,sizeof(msg)) < 0)
		erro("Não foi possível escrever para o socket\n");

  printf("####################################################################\n");
  printf("#                     EXIBICAO INICIADO                            #\n");
  printf("####################################################################\n\n");

	while(1) 
  {
		int n=recv(sockfd, &msg, sizeof(msg),0);

		if (n > 0)
    {
			printf("%d diz: %s\n", getOrig(&msg), getText(&msg));
			if (getType(&msg) == TCHAU) break;
		}
    else
    {
			printf("Conexão fechada pelo servidor\n");
			break;
		} 
	}

	shutdown(sockfd,2);
}
