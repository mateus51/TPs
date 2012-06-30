#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>

#include "tp_socket.h"
#include "message.h"


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
 * Tenta se conectar ao servidor. Retorna o socket
 * através do qual as mensagens devem ser enviadas.
 */
int connect_to_server (char *server_name, int port, unsigned short int uid) {
//	printf("connecting to server...\nint id: %d (%u)\n", uid, uid);

    int sock = tp_socket(0);
    so_addr serv_addr;
    tp_build_addr(&serv_addr, server_name, port);

    // Estabelecendo conexão TCP com servidor
    if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect()");
        exit(EXIT_FAILURE);
    }

    // Enviando OI
	msg_t msg;
	msg.type = OI;
	msg.orig_uid = uid;
	msg.dest_uid = 0;
	msg.text_len = 0;
	bzero(msg.text, 141);
	char buffer[BUFF_LEN];
	encode(buffer, msg);

//	printf("connecting to server...\n uid (msg): %d\n uid (buf): %d\n", msg.orig_uid, *(buffer + 2));

	// enviando OI
    if (write(sock, buffer, 8) < 0) {
         perror("write()");
         exit(EXIT_FAILURE);
    }

    // Recebendo resposta do servidor
    bzero(buffer, BUFF_LEN);
    if (read(sock, buffer, BUFF_LEN) < 0) {
    	perror("read()");
    	exit(EXIT_FAILURE);
    }

    // verificando resposta
    msg = decode(buffer);
    switch (msg.type) {
    case OI:
    	printf("Connected to server!\n");
    	break;
    case ERRO:
    	printf("%s\n", msg.text);
    	exit(EXIT_FAILURE);
    default:
    	printf("Server returned unexpected message..\n");
    	exit(EXIT_FAILURE);
    }

    return sock;
}


/*
 * Desconecta do servidor.
 */
void disconnect_from_server(int sock, unsigned short int uid) {
	msg_t msg;
	msg.type = TCHAU;
	msg.orig_uid = uid;
	msg.dest_uid = 0;
	msg.text_len = 0;
	bzero(msg.text, 141);
	char buffer[BUFF_LEN];
	encode(buffer, msg);
    if (write(sock, buffer, 8) < 0) {
         perror("write()");
         exit(EXIT_FAILURE);
    }
    close(sock);
}
