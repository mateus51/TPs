#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>
//#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "tp_socket.h"
#include "io.h"
#include "tp2.h"
#define TAMNOMEARQ 15
#define TAMJANELA 4			//Não pode ser maior que 128 pois char assume -128 a 127.

//Verificação de erro: x=soma%95 + 32. //caracteres imprimiveis: 32 a 126 -> 0 a 94.
//Tá implementado: quando dá o timeout, reenvia o pacote mais antigo. (selective repeat)

typedef struct{
	int socket;
	int janela[TAMJANELA];				//vetor booleano; 1->janela ocupada; 0->janela livre.
	struct sockaddr_in cli_addr;
} strRede;

void escutaAck(void *apontador){
	strRede *tdata;
	tdata=(struct strRede *)apontador;
	char *buffer=malloc(sizeof(char));
	int cabecalho;

	while(1){
		tp_recvfrom(tdata->socket, buffer, 1, (so_addr*)&(tdata->cli_addr) );			//recebe só o cabeçalho
		cabecalho=(int)buffer[0];
		printf("Pacote %d -> [ Ack %d ]\n", cabecalho, (cabecalho-1)%TAMJANELA);
		//desocupa a janela correspondente -> o main muda de 0 pra 1 e o thread muda de 1 pra 0.
		tdata->janela[(cabecalho-1)%TAMJANELA]=0;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////

int alarm;		//alarm poderia indicar o pacote que deu timeout, mas como faz?

void main (int argc, char **argv){
	if (argc < 3){printf("Uso: %s <porta do servidor> <tamanho do buffer>\n", argv[0]); exit(1); }
	tp_init();
	int i, j, k, tamBuffer, socket, timeout=1000, cabecalho;
	unsigned int bytes=0;
	char byte, null = 0;
	char *buffer, *portaServ, *nomeArq;
	char *janela[TAMJANELA];							//armazena o buffer+cabeçalho em cada
	FILE *arq;
	pthread_t thread;
	strRede dados;
	mysethandler(); 										//Habilita o uso temporizador

	//Aplica a porta do servidor e o tamanho do buffer
	portaServ = argv[1];
	tamBuffer=atoi(argv[2]);
	buffer=malloc(tamBuffer*sizeof(char));
	nomeArq=malloc(TAMNOMEARQ*sizeof(char));
	for(i=0; i<TAMJANELA; i++) janela[i]=malloc(tamBuffer*sizeof(char));

	//Cria o socket
	socket=tp_socket(atoi(portaServ));
	dados.socket=socket;
	printf("Servidor inicializado.\n");
 
	/*
	 * Entre em um loop infinito respondendo aos clientes 
	 * que enviam uma mensagem para o servidor.
	*/
	for(;;) {
		do{		
			alarm=0;
			LimpaString(buffer, tamBuffer);
			LimpaString(nomeArq, TAMNOMEARQ);
			for(i=0; i<TAMJANELA; i++){ dados.janela[i]=0; LimpaString(janela[i], TAMJANELA); }
			cabecalho=0;
			i=0;
			printf("\nPronto para receber mensagens de novos clientes...\n");

			//Recebe o nome do arquivo que um cliente requisitou
			//Como cada pacote só tem 1 caractere, a verificação de erros foi feita baseando no nome todo.
			//Senão ela seria feita baseando em cada pacote.
			tp_recvfrom(socket, buffer, 1, (so_addr*)&(dados.cli_addr));
			cabecalho=(int)(buffer[0]);
			while(strcmp(buffer, "0")){
				strcat(nomeArq, buffer);
				tp_recvfrom(socket, buffer, 1, (so_addr*)&(dados.cli_addr));//Tem de receber 1 a 1, para saber quando acaba.
				i+=(int)(buffer[0]);
			}
			i-=48;		//Subtrai o 0 que foi somado.
			i=i%95 + 32;
			if (i!=cabecalho){
				printf("ERRO: Falha no recebimento do nome do arquivo a enviar.");
				tp_sendto(socket, &null, 1, (so_addr*)&(dados.cli_addr));
			}
		}while(i!=cabecalho);
		printf("Arquivo a ser aberto: '%s'.\n", nomeArq+1);

		//Abre o arquivo para ser enviado
		arq=fopen(nomeArq+1, "rb");
		if(!arq){ printf("\nERRO: Falha ao tentar abrir arquivo requisitado!\n"); exit(1); }

		//Cria a thread que ficará por conta de escutar acks.
		i=pthread_create(&thread, NULL, escutaAck, (void *)&dados);
		if(i){ printf("ERRO: codigo retornado por pthread_create() foi: %d\n", i); exit(-1); }

		// Envia o arquivo para o cliente
		LimpaString(buffer, tamBuffer);
		printf("Servidor: Enviando arquivo...\n");
		mysettimer(timeout);									//Ativa o temporizador	
		for(i=0; fread(buffer, 1, tamBuffer-2, arq); i++){
//printf("buffer = '%s'.\n", buffer);
			while((dados.janela[i%TAMJANELA])==1){	//i=numero pacote; i%TAMJANELA=janela que deve ser enviado
				if(alarm){
					printf("TIMEOUT: Reenviando pacote não confirmado!\n");
//					for(i=0; i<TAMJANELA; i++){				//Dá apenas uma "volta" da estrutura da janela
//						if(dados.janela[i]){
//							printf("Reenviando janela %d.\n", i);
							tp_sendto(socket, janela[i%TAMJANELA], tamBuffer, (so_addr*)&(dados.cli_addr)); //janela[i] já tem cabeçalho e verificação de erro
//						}
//					}
					alarm=0;
					mysettimer(timeout);									//Ativa o temporizador
				}
			}
			/*	marcando a janela como ocupada antes de realmente ser enviada,
				evita de um ack super-rapido escrever 0 na janela antes dela ser marcada como 1*/
			dados.janela[i%TAMJANELA]=1;
			LimpaString(janela[i%TAMJANELA], tamBuffer);
			byte=(char)(i%127)+1;										//byte=0 dá problemas
			strcpy(janela[i%TAMJANELA], &byte);						//Coloca o cabeçalho
//printf("janelacab = %s (%d).\n", janela[i%TAMJANELA], strlen(janela[i%TAMJANELA]));
			k=0;
			for(j=0; j<strlen(buffer); j++){
				k+=(int)buffer[j];
			}
			janela[i%TAMJANELA][1]=(char)(k%95 + 32);			//Colcou a verificação de erro após o cabeçalho
//printf("janelacabver = %s (%d).\n", janela[i%TAMJANELA], strlen(janela[i%TAMJANELA]));
			strcat(janela[i%TAMJANELA]+2, buffer);
			printf("Enviando cabeçalho [%d] e verificação=%d.\n", (int)janela[i%TAMJANELA][0], (int)janela[i%TAMJANELA][1]);
//printf("janelafull = '%s' (%d).\n", janela[i%TAMJANELA], strlen(janela[i%TAMJANELA]));
			tp_sendto(socket, janela[i%TAMJANELA], tamBuffer, (so_addr*)&(dados.cli_addr));	//envia cabeçalho+buffer (tamBuffer)
			LimpaString(buffer, tamBuffer);
		}

		//Termina enviando o 0 (null).
		tp_sendto(socket, &null, 1, (so_addr*)&(dados.cli_addr));
		pthread_cancel(thread);
		fclose(arq);
	}	
}
