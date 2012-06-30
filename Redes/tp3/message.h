
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


// Exibição: 1-999
// Envio: 1001 - 1999






msg_t decode(const char *buffer);

void encode(char *buffer, msg_t msg);

