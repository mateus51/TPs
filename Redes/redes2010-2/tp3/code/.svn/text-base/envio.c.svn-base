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
  else if (atoi(argv[3]) > 1999 || atoi(argv[3]) < 1001)
  {
		uso();
		erro("Identificador inválido: deve ser entre 1001 e 1999");
	} 

  char* hostname = argv[1];
  int port = atoi(argv[2]);
  short int uid = atoi(argv[3]);
  
  struct sockaddr_in serv_addr;
  struct hostent *server;

  //Cria o socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
      erro("Não foi possível abrir o socket\n");

  //Pega o endereço do servidor
  server = gethostbyname(argv[1]);
  if (server == NULL)
      erro("Host não encontrado\n");

  //Preenche o serv_addr
  //Familia
  serv_addr.sin_family= AF_INET;
  //Porto
  serv_addr.sin_port=htons(port);
  //IP
  bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);

  //Conecta
  if (connect(sockfd,(const struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
  {
    char msg_de_erro[100];
    sprintf(msg_de_erro, "Não foi possivel se conectar ao servidor %s (%d)", server->h_name, port);
		erro(msg_de_erro); 
  }

  //Se identifica ao servidor
  msg_t msg;
  setMsg(&msg,OI,uid,0,0,"");
  if (write(sockfd,&msg,sizeof(msg)) < 0)
    erro("Não foi possível escrever para o socket\n");

  //Resposta do servidor
  int n;
  if ((n=recv(sockfd,&msg,sizeof(msg),0)) < 0)
    erro("Erro no receive");
  else if (getType(&msg) == TCHAU) 
    erro("Conexão recusada pelo servidor\n");

  printf("####################################################################\n");
  printf("#                       ENVIO INICIADO                             #\n");
  printf("####################################################################\n\n");

  while (1) 
  {
    printf("\nOpções:\n\t(1) Fechar conexão\n\t(2) Enviar mensagem\n\n");
    printf("Escolha: ");
   
    char buffer[145];
    fgets(buffer,141,stdin);
    buffer[2] = '\0';
    int tipo_msg = atoi(buffer);

    if (tipo_msg == TCHAU)
    {
      printf("Conexão fechada\n");
      n = write(sockfd,"",0);
      break;
    }
    else if(tipo_msg == MSG) 
    {
      printf("Destino: ");
      fgets(buffer,141,stdin);
      buffer[5]='\0';	

      short int destino_uid=0;
      destino_uid = atoi(buffer);

      if (destino_uid > 999 || destino_uid < 0 )
        printf("Destino inválido: deve ser entre 1 e 999\n");
      else
      {
        printf("Mensagem: ");
        fgets(buffer,141,stdin);

        setMsg(&msg,MSG,uid,destino_uid,strlen(buffer)-1, buffer);
        if (write(sockfd,&msg,sizeof(msg)) < 0 )
          erro("Não foi possível escrever para o socket\n");
      }
    }
    else 
    {
      printf("Tipo de mensagem inválida: deve ser 1 ou 2\n");
      continue;
    }
  }

  shutdown(sockfd,2);
}
