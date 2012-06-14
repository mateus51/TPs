#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <netdb.h>
//#include <sys/socket.h>
//#include <sys/types.h>

#include "window.h"
#include "time.h"

void read_client_params(int argc, char *argv[], char **host, int *port, char **filename, int *buffer_size, int *window_size) {
	if(argc != 6){
		printf("Usage:  %s host port filename buffer_size window_size\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	else {
		*host = (char*) malloc(sizeof(char) * (strlen(argv[1])+1));
		strcpy(*host, argv[1]);

		*port = atoi(argv[2]);

		*filename = (char*) malloc(sizeof(char) * (strlen(argv[3])+1));
		strcpy(*filename, argv[3]);

		*buffer_size = atoi(argv[4]);

		*window_size = atoi(argv[5]);
	}
}



int main(int argc, char *argv[]) {
	int resp = tp_init();
	if (resp != 0) {
		fprintf(stderr, "tp_init() failed (%d)\n", resp);
		exit(EXIT_FAILURE);
	}
	else {

		// infos da linha de comando
		char *host, *filename;
		int port, buffer_size, window_size;
		read_client_params(argc, argv, &host, &port, &filename, &buffer_size, &window_size);

		int client_sock = tp_socket(0);
		so_addr server_addr;
		tp_build_addr(&server_addr, host, port);

		char buffer[buffer_size];

		// start to count time
		//double start = get_time();

		// sending file name
		bzero(buffer, buffer_size);
		strcpy(buffer, filename);
		resp = confirmed_sendto(client_sock, buffer, strlen(buffer) + 1, &server_addr);

		FILE *file = fopen(filename, "w+");
		if (file == NULL) {
			printf("Error creating file.\n");
			exit(EXIT_FAILURE);
		}

		Window *window = new_window(window_size, buffer_size, client_sock, &server_addr);
		boolean received = False;
		int bytes;

		while (!received) {

			bytes = receive_and_store(window, file);

			if (bytes == 0)
				received = True;

		}

		fclose(file);
		free(host);
		free(filename);
		free_window(window);
	}

	return EXIT_SUCCESS;
}
