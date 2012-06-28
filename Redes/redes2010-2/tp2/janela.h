
#include "tp_socket.h"
#include <sys/time.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_NOME 20
#define CABECALHO 6
#define DADOS 0
#define FINAL 1
#define ACK 2
#define NCK 3
#define TIMEOUT 1000

struct sockaddr_in endereco_;
int idsocket_;
int numero_;
int ultimoack_;

char **buffer_;
int offset_;
int tamatual_;
int tamjanela_;

int reenvios_;
int pacotesenviados_;
int pacotesrecebidos_;
int pacotesdescartados_;
int acksrecebidos_;
int acksenviados_;

// Formato do pacote:
// 
// | NUMERO  | TIPO   | CHECKSUM |  DADOS  | 
// | 4 Bytes | 1 Byte | 1 Byte   |  buffer |
//


// Faz a abertura ativa da conexao
// @host - nome do host
// @porto - numero do porto 
// retorna: o id do socket criado 
int windowInitAtivo(char *host,int porto);

// Faz a abertura passiva da conexao
// @porto - numero do porto 
// retorna: o id do socket criado
int windowInitPassivo(int porto,int tambuffer, int tamjanela);

// Envia uma mensagem
// @buffer - mensagem a ser enviada
// @tambuffer - tamanho da mensagem
// retorna o numero de bytes enviados
int windowSend(char *buffer, int tambuffer);

// Recebe uma mensagem
// @buffer - mensagem a ser enviada
// @tambuffer - tamanho da mensagem
// retorna o numero de bytes recebidos
// -1 se o pacote já foi recebido
// -2 em caso de erro
int windowReceive(char *buffer, int tambuffer);

// Faz o checksum da mensagem
// @buf - mensagem
// @count - tamannho da mensagem em bytes/2
// retorna o checksum da mensagem
int checksum(char *buffer, int tambuffer);

int windowSendName(char *buffer, int tambuffer);

int windowReceiveName(char *buffer, int tambuffer);

int windowSendFinal(int tambuffer);

void windowClose();

void makePkg(char *pacote,int numero,int tipo, char *buffer,int tambuffer);

void setTimer(int segundos);
