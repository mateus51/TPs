/* protocolo.h - Interface a ser usada no acesso a funções 
 * básicas deste protocolo.
 */

#ifndef _PROTOCOLO_H_
#define _PROTOCOLO_H_

//define a estrutura pacote deste protocolo
typedef struct{
            unsigned short int type;
            unsigned short int orig_uid;
            unsigned short int dest_uid;
            unsigned short int text_len;;
            unsigned char      text[141];
}Mensagem;

//funcao para retornar o tipo do pacote
short int getType(Mensagem *msg);

//funcao para retornar o conteudo da mensagem
char* getMsg(Mensagem *msg);

//funcao para retornar o tamanho do conteudo
short int getTamanho(Mensagem *msg);

//funcao para retornar a origem da Mesagem
short int getOrigem(Mensagem *msg);

//funcao para retornar o destino da mensagem
short int getDestino(Mensagem *msg);

//funcao para criar um Mensagem
void empacota(Mensagem *msg, short int type, short int origem, short int destino, short int tamanho, char* dados);

#endif /* _protocolo.h*/
