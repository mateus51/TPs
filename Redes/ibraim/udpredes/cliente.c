#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "tp_socket.h"
#include "io.h"
#define ARQBAIXADO "arquivoBaixado"

main (int argc, char **argv){
	if(argc < 5){
		printf("Uso: %s <ip do servidor> <porta do servidor> <arquivo a ser baixado> <tamanho do buffer>\n", argv[0]);
		exit(1);
	}
	// Variáveis de medida de tempo
	struct timeval tv1, tv2;
	double t1=0, t2=0;
	// Medindo tempo ...
	gettimeofday(&tv1, NULL);
	t1 = (double)(tv1.tv_sec) + (double)(tv1.tv_usec)/ 1000000.00;

	struct sockaddr_in serv_addr;							//endereco do servidor
	int i,j,k,socket, tamBuffer;
	unsigned int bytes=0;
	char c, *buffer, *nomeArq;								//mensagem que sera enviada para o servidor
	char *serv_udp_port, *serv_host_addr;
	FILE *arq;

	//Pega endereço, porta do servidor, nome do arquivo e tamanho do buffer
	serv_host_addr = argv[1];
	serv_udp_port  = argv[2];
	nomeArq=malloc(sizeof(char)*strlen(argv[3]));
	strcpy(nomeArq, argv[3]);
	tamBuffer=atoi(argv[4]);
	buffer=malloc(tamBuffer*sizeof(char));

	//	Cria o socket e configura o destino
	socket=tp_socket(INADDR_ANY);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(serv_host_addr);
	serv_addr.sin_port = htons(atoi(serv_udp_port));

	//Envia o nome do arquivo para o servidor, com cabeçalho, e prepara um arquivo para gravar
	LimpaString(buffer, tamBuffer);
	j=0;
	for(i=0; i<strlen(nomeArq); i++){
		j=j+(int)nomeArq[i];
	}
	c=j%95 + 32;		//Para ser imprimivel, tem de ser entre 32 e no maximo 126('~').
	buffer[0]=c;
	strcat(buffer+1, nomeArq);
	for(i=0; i<strlen(buffer); i++)
		tp_sendto(socket, &buffer[i], 1, (so_addr *) &serv_addr);
	tp_sendto(socket, "0", 1, (so_addr *) &serv_addr);
	arq=fopen(ARQBAIXADO, "wb");

	free(nomeArq);
	nomeArq=malloc(tamBuffer*sizeof(char));
	LimpaString(nomeArq, tamBuffer);
	LimpaString(buffer, tamBuffer);
	//Recebe arquivo do servidor até receber 0 (nulo); [0]=numero do pacote buffer; [1]=verificação
	bytes+=tp_recvfrom(socket, buffer, tamBuffer, (so_addr *) &serv_addr);
	//faz verificação, se ok, manda ack
	j=0; k=0;
	for(k=2; k<tamBuffer; k++){
		j+=(int)(buffer[k]);
	}
	j=(j%95+32);
	printf("Recebi pacote [%d] com verificação=%d.\n", (int)buffer[0], (int)buffer[1]);
	if(j==(int)buffer[1]){
		tp_sendto(socket, &buffer[0], 1, (so_addr *) &serv_addr);			//Responde com um ack, utilizando cabeçalho
		printf("Enviou um [ack %d].\n", (int)buffer[0]);
		//	LimpaString(nomeArq, TAMNOMEARQ) \/ aplicar nomeArq junto com buffer;
		strcpy(nomeArq, buffer+2);
		fwrite(nomeArq,sizeof(char), strlen(nomeArq),arq);
	}														//senão, espera reenvio.
	for(i=1; strcmp(buffer,"");i++){
		LimpaString(buffer, tamBuffer);
		LimpaString(nomeArq, tamBuffer);
		bytes+=tp_recvfrom(socket, buffer, tamBuffer, (so_addr *) &serv_addr);
		//faz verificação, se ok, manda ack
		j=0;
		for(k=2; k<tamBuffer; k++){
			j+=(int)(buffer[k]);
		}
		j=(j%95+32);
		if(j==(int)buffer[1]){
			printf("Recebi pacote [%d] com verificação=%d.\n", (int)buffer[0], (int)buffer[1]);
			tp_sendto(socket, &buffer[0], 1, (so_addr *) &serv_addr);			//Responde com um ack, utilizando cabeçalho
			printf("Enviou um [ack %d].\n", (int)buffer[0]);
			strcpy(nomeArq, buffer+2);								//Tem que passar para outro char*, senão causa erros
			fwrite(nomeArq,sizeof(char),  strlen(nomeArq),arq);
		}														//senão, espera reenvio.
	}

	fclose(arq);
	printf("Arquivo \"%s\" salvo com sucesso. %d mensagens recebidas.\n", ARQBAIXADO, i);
	//Medindo tempo ...
	gettimeofday(&tv2,NULL);
	t2 = (double)(tv2.tv_sec) + (double)(tv2.tv_usec)/ 1000000.00;
	printf("BUFFER = %5u byte(s), %10.2f kbps (%u bytes em %f s)\n", tamBuffer, (8*bytes/1024)/(t2-t1), bytes, t2-t1);
	close(socket);
}
