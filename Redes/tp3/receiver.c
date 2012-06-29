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

int main (int argc, char **argv) {
	unsigned short int uid;
	int port;
	char servname[256];
	get_info(argc, argv, &uid, servname, &port);


	if (uid > 999 || uid == 0) {
		printf("Erro: identificador de exibição deve ser entre 1 e 999\n");
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

    char buffer[BUFF_LEN];
    int read_resp;
	printf("\nwaiting for messages...\n");
    while (1) {
    	bzero(buffer, BUFF_LEN);
    	read_resp = read (sock, buffer, BUFF_LEN);
    	if (read_resp < 0) {
    		perror("read()");
    		exit(EXIT_FAILURE);
    	}
    	else if (read_resp == 0) {
    		// server hung up
    		printf("server hung up!\n");
    		exit(EXIT_SUCCESS);
    	}
    	msg_t msg = decode(buffer);
    	char *msg_type = msg.dest_uid == 0 ? "broadcast" : "private";
    	printf("\nMessage Received (%s)\n", msg_type);
    	printf("  from: %u\n", msg.orig_uid);
    	printf("  message: %s\n", msg.text);
    }

    // sleep for 2 seconds before disconnecting
//    sleep(20);

    // Enviando TCHAU
    disconnect_from_server(uid);

    close(sock);

	return EXIT_SUCCESS;
}
