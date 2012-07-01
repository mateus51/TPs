#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "message.h"
#include "client.h"


int main (int argc, char **argv) {
	unsigned short int uid;
	int port;
	char servname[256];
	get_info(argc, argv, &uid, servname, &port);

	// checando se uid informado está range especificado.
	if (uid > 999 || uid == 0) {
		fprintf(stderr, "Erro: identificador de exibição deve ser entre 1 e 999\n");
		exit(EXIT_FAILURE);
	}

	int sock = connect_to_server(servname, port, uid);

    char buffer[BUFF_LEN];
    int read_resp;
    while (1) {
    	bzero(buffer, BUFF_LEN);
    	read_resp = read (sock, buffer, BUFF_LEN);
    	if (read_resp < 0) {
    		perror("read()");
    		exit(EXIT_FAILURE);
    	}
    	else if (read_resp == 0) {
    		// cliente de exibição desconectou ou servidor caiu
    		printf("\ndisconnected!\n");
    		exit(EXIT_SUCCESS);
    	}
    	msg_t msg = decode(buffer);
    	printf("\n%u", msg.orig_uid);
    	if (msg.dest_uid != 0) printf(" (private)");
    	printf(": %s\n", msg.text);

    }

	return EXIT_SUCCESS;
}
