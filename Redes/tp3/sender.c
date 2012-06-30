#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "message.h"
#include "client.h"



int main (int argc, char **argv) {
	unsigned short int uid;
	int port;
	char servname[256];
	get_info(argc, argv, &uid, servname, &port);


	if (uid < 1001 || uid > 1999) {
		printf("Erro: identificador de envio deve ser entre 1001 e 1999\n");
		exit(EXIT_FAILURE);
	}

	// Conectando ao servidor
	int server = connect_to_server(servname, port, uid);

    char *msg = NULL;
    int total_read = 0;
    size_t msg_size = 0;
    int to;
    while (1) {
    	printf("\n\nNova Mensagem\npara (-1 para desconectar): ");
    	total_read = getline(&msg, &msg_size, stdin);
    	to = atoi(msg);
    	if (to < 0) {
    		// Desconectando do servidor
    		printf("\ndesconectando...\n");
			disconnect_from_server(server, uid);
			break;
    	}
    	printf("mensagem (max. 140 caracteres): ");
    	total_read = getline(&msg, &msg_size, stdin);
    	if (total_read > 140)
    		msg[140] = '\0';
    	else
    		msg[total_read - 1] = '\0';
    	send_message(server, uid, to, msg);
    }

	return EXIT_SUCCESS;
}
