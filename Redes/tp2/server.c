#include "server.h"
#include "window.h"

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>



int main(int argc, char *argv[]) {

	int resp = tp_init();
	if (resp != 0) {
		fprintf(stderr, "tp_init() failed (%d)\n", resp);
		exit(EXIT_FAILURE);
	}
	else {

		// infos da linha de comando
		int port, buffer_size, window_size;
		read_server_params(argc, argv, &port, &buffer_size, &window_size);

		int server_sock = tp_socket(port);
		so_addr client_addr;

		char buffer[buffer_size];
		bzero(buffer, buffer_size);

		confirmed_recvfrom(server_sock, buffer, buffer_size, &client_addr);

		char host[256];
		getnameinfo((struct sockaddr *)&client_addr, sizeof(client_addr), host, 256, 0, 0, 0);

		printf("Message Received: '%s'\n", buffer);
		printf("  From: %s\n", host);
	}

	return EXIT_SUCCESS;
}

void read_server_params(int argc, char *argv[], int *port, int *buffer_size, int *window_size) {
	if(argc != 4){
		printf("Usage:  %s port buffer_size window_size\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	else {
		*port = atoi(argv[1]);
		*buffer_size = atoi(argv[2]);
		*window_size = atoi(argv[3]);
	}
}
