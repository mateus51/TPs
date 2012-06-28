/* protocolo.c - funções auxiliares para uso do protocolo baseado em sockets tcp 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "protocolo.h"


//funcao para retornar o tipo da mensagem 
short int getType(Mensagem *msg){
	return msg->type;
}

//funcao para retornar o tamanho do conteudo 
short int getTamanho(Mensagem *msg){
	return msg->text_len;
}

//funcao apra retornar o conteudo do pacote 
char* getMsg(Mensagem *msg){
	return msg->text;
}

//funçao para criar uma Mensagem 
void empacota(Mensagem *msg, short int type, short int origem, short int destino, short int tamanho, char* dados){
	msg->type = type;
	msg->orig_uid = origem;
	msg->dest_uid = destino;
	msg->text_len = tamanho;
	strcpy(msg->text,dados);
	
}

//retorna o conteudo da mensagem
short int getOrigem(Mensagem *msg){
	return msg->orig_uid;
}

short int getDestino(Mensagem *msg){
	return msg->dest_uid;
}
