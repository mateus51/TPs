#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "tp_socket.h"
#include "message.h"
#include "client.h"

so_addr serv_addr;
int sock;


void send_message(int uid, int to, char *str) {
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
	int write_resp = write (sock, buffer, str_size + 8);
	if (write_resp < 0) {
		perror("write()");
		exit(EXIT_FAILURE);
	}
	else if (write_resp == 0) {
		// server hung up
		printf("server hung up!\n");
		exit(EXIT_SUCCESS);
	}
}



int main (int argc, char **argv) {
	unsigned short int uid;
	int port;
	char servname[256];
	get_info(argc, argv, &uid, servname, &port);


	if (uid < 1001 || uid > 1999) {
		printf("Erro: identificador de envio deve ser entre 1001 e 1999\n");
		exit(EXIT_FAILURE);
	}



    // Creating buffer and socket
    sock = tp_socket(0);
    tp_build_addr(&serv_addr, servname, port);


    // Estabelecendo conexão TCP com servidor
    if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect()");
        exit(EXIT_FAILURE);
    }


    // Enviando OI. -1 = ID em uso
    if (connect_to_server(uid) == -1)
    	exit(EXIT_FAILURE);

    char msg[142];
    unsigned short int to;
    while (1) {
//    	sleep(20);
    	printf("\n\nNova Mensagem\npara: ");
    	fgets(msg, 141, stdin);
    	msg[strlen(msg) + 1] = '\0';
    	to = (unsigned short int) atoi(msg);
    	bzero(msg, 142);
    	printf("mensagem (max. 140 caracteres): ");
    	fgets(msg, 141, stdin);
    	msg[strlen(msg)] = '\0';
    	send_message(uid, to, msg);
    }

    // sleep for 2 seconds before disconnecting
//    sleep(20);

    // Enviando TCHAU
    disconnect_from_server(uid);

    close(sock);

	return EXIT_SUCCESS;
}
