#ifndef __MESSAGE_H__
#define __MESSAGE_H__


#define BUFF_LEN 149

typedef enum {
	OI, TCHAU, MSG, ERRO
} msgtype_t;

typedef struct {
	unsigned short int type;
	unsigned short int orig_uid;
	unsigned short int dest_uid;
	unsigned short int text_len;
	char text[141];
} msg_t;


/*
 * retorna o buffer passado com parâmetro decodificado
 * em uma msg_t
 */
msg_t decode(const char *buffer);

/*
 * Codifica a mensagem msg no buffer
 */
void encode(char *buffer, msg_t msg);

/*
 * Envia a seguinte mensagem:
 *   de: from
 *   para: to
 *   texto: str
 */
void send_message(int sock, unsigned short int from, unsigned short int to, const char *str);

#endif
