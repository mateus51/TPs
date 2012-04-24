#include "io.h"

void read_client_params(int argc, char *argv[], char **host, int *port, char **filename, int *buffer_size) {
	if(argc != 5){
		printf("Usage:  %s host port filename buffer_size\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	else {
		*host = (char*) malloc(sizeof(char) * (strlen(argv[1])+1));
		strcpy(*host, argv[1]);

		*port = atoi(argv[2]);

		*filename = (char*) malloc(sizeof(char) * (strlen(argv[3])+1));
		strcpy(*filename, argv[3]);

		*buffer_size = atoi(argv[4]);
	}
}

void read_server_params(int argc, char *argv[], int *port, int *buffer_size) {
	if(argc != 3){
		printf("Usage:  %s port buffer_size\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	else {
		*port = atoi(argv[1]);
		*buffer_size = atoi(argv[2]);
	}
}


