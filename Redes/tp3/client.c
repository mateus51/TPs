#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "message.h"

extern int sock;

void get_info(int argc, char **argv, unsigned short int *uid, char *addr, int *port) {
	if(argc != 4){
		printf("Usage:  %s <uid> <server address> <server port>\n", argv[0]);
		exit(EXIT_SUCCESS);
	}
	else {
		int id = atoi(argv[1]);
		*uid = id;
		*port = atoi(argv[3]);
		strcpy(addr, argv[2]);
	}
}

/*
 * Tenta se conectar ao servidor. Se conseguir, retorna 0.
 * Caso contrário, retorna -1.
 */
int connect_to_server (unsigned short int uid) {
//	printf("connecting to server...\nint id: %d (%u)\n", uid, uid);
	msg_t msg;
	bzero(msg.text, BUFF_LEN);
	msg.type = OI;
	msg.orig_uid = uid;
	msg.dest_uid = 0;
	msg.text_len = 0;
	char buffer[BUFF_LEN];
	encode(buffer, msg);

//	printf("connecting to server...\n uid (msg): %d\n uid (buf): %d\n", msg.orig_uid, *(buffer + 2));

	// enviando OI
    if (write(sock, buffer, 8) < 0) {
         perror("write()");
         exit(EXIT_FAILURE);
    }

    bzero(buffer, BUFF_LEN);

    if (read(sock, buffer, BUFF_LEN) < 0) {
    	perror("read()");
    	exit(EXIT_FAILURE);
    }
    msg = decode(buffer);
    switch (msg.type) {
    case OI:
    	printf("Connected to server!\n");
    	return 0;
    case ERRO:
    	printf("Could not connect to server. ID %u is already in use.\n", msg.orig_uid);
    	return -1;
    default:
    	printf("Server returned unknown message..\n");
    	return -1;
    }
}


/*
 * Desconecta do servidor.
 */
void disconnect_from_server(int uid) {
	msg_t msg;
	bzero(msg.text, 141);
	msg.type = TCHAU;
	msg.orig_uid = (unsigned short int) uid;
	msg.dest_uid = 0;
	msg.text_len = 0;
	char buffer[BUFF_LEN];
	encode(buffer, msg);
    if (write(sock, buffer, 8) < 0) {
         perror("write()");
         exit(EXIT_FAILURE);
    }
}
