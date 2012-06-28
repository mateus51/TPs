#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

#include "tp_socket.h"
#include "message.h"

so_addr serv_addr;
int sock, uid;


void get_info(int argc, char **argv, char *addr, int *port) {
	if(argc != 4){
		printf("Usage:  %s <uid> <server address> <server port>\n", argv[0]);
		exit(EXIT_SUCCESS);
	}
	else {
		uid = atoi(argv[1]);
		*port = atoi(argv[3]);
		strcpy(addr, argv[2]);
	}
}


/*
 * Tenta se conectar ao servidor. Se conseguir, retorna 0.
 * Caso contrário, retorna -1.
 */
int connect_to_server () {
	msg_t msg;
	bzero(msg.text, BUFF_LEN);
	msg.type = OI;
	msg.orig_uid = (unsigned short int) uid;
	msg.dest_uid = 0;
	msg.text_len = 0;
	char buffer[BUFF_LEN];
	encode(buffer, msg);
	// enviando OI
    if (write(sock, buffer, 8) < 0) {
         perror("write()");
         exit(EXIT_FAILURE);
    }

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
    	printf("Could not connect to server. ID already in use.\n");
    	return -1;
    default:
    	printf("Server returned unknown message..\n");
    	return -1;
    }
}


/*
 * Desconecta do servidor.
 */
void disconnect_from_server() {
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



void send_message(unsigned short int to, char *str) {
	// FIXME: Os campos inteiros devem ser enviados na ordem de bytes da rede (network byte order
	msg_t msg;
	bzero(msg.text, 141);
	msg.orig_uid = (unsigned short int) uid;
	msg.dest_uid = (unsigned short int) to;
	msg.type = MSG;
	int str_size = strlen(str) + 1;
	if (str_size > 141) {
		msg.text_len = 141;
		memcpy(msg.text, str, 140);
		msg.text[140] = '\0';
	}
	else {
		msg.text_len = str_size;
		memcpy(msg.text, str, str_size);
	}

	char buffer[BUFF_LEN];
	encode(buffer, msg);
	if (write (sock, buffer, str_size + 8) < 0) {
		perror("write()");
		exit(EXIT_FAILURE);
	}
}



int main (int argc, char **argv) {
	int port;
	char servname[256];
	get_info(argc, argv, servname, &port);


    // Creating buffer and socket
    char buffer[BUFF_LEN];
    sock = tp_socket(port);
    tp_build_addr(&serv_addr, servname, port);


    // Estabelecendo conexão TCP com servidor
    if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect()");
        exit(EXIT_FAILURE);
    }

    // Enviando OI
    connect_to_server();

    while (0) {
    	// ler dest stdin
    	// ler msg stdin
    	// enviar tudo
    }

    sleep(1);

    // Enviando TCHAU
    disconnect_from_server();

    close(sock);

	return EXIT_SUCCESS;
}
