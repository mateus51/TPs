#include "window.h"
#include "listener.h"

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
//#include <pthread.h>
#include <unistd.h>
//#include <signal.h>

#define WAIT_TIME 1 // in seconds

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

		// socket info
		int server_sock = tp_socket(port);
		so_addr client_addr;

		// creating buffer
		char buffer[buffer_size];


		while (1) {
			bzero(buffer, buffer_size);

			// receiving file name from client
			confirmed_recvfrom(server_sock, buffer, buffer_size, &client_addr);

			// printing host info
			char host[256];
			getnameinfo((struct sockaddr *)&client_addr, sizeof(client_addr), host, 256, 0, 0, 0);
			printf("Message Received: '%s'\n", buffer);
			printf("  From: %s\n", host);

			if (!strcmp(buffer, "exit"))
				break;

			// preparing file to be sent
			char filename[strlen(buffer) + 1];
			strcpy(filename, buffer);
			FILE *file = fopen(filename, "r");
			if (file == NULL) {
				printf("ERROR opening file...\n");
				exit(EXIT_FAILURE);
			}

			// preparing window
			Window *window = new_window(window_size, buffer_size, server_sock, &client_addr);

			int bytes_read, total_sent = 0;
			boolean sent = False;

			// start signal listener
			pthread_t sig_listener = start_signal_listener(window);
			set_alarm(1);

			// start ACK listener
			pthread_t ack_listener = start_ack_listener(window);

			while(!sent) {

				// fill next slot and send it to client. Listener will verify if arrived,
				// and resend if necessary.
				bytes_read = fill_and_send_next_slot(window, file);

				// EOF reached. All sent.
				if (bytes_read == 0) {
					sent = True;
				}

				// Window is full. Wait for an empty slot.
				else if (bytes_read == -1) {
					//sleep(1); // OK to call since it's in the main function
	//				struct timespec time;
	//				time.tv_sec = 0;
	//				time.tv_nsec = 500000000; // 0.5 sec.
	//				nanosleep(time, NULL);
				}

				else {
					total_sent += bytes_read;
				}
			}

			// wait listener to finish handling ACKs.
			printf("waiting for ACK listener to finish...\n");
			stop_listener(ack_listener);
			printf("ACK listener stoped!\n");

			// tell listener to stop
			extern int keep_listening_for_signals;
			keep_listening_for_signals = False;
			printf("stoping SIG listener...\n");
			stop_listener(sig_listener); // wait for it to stop

			fclose(file);
			free_window(window);
		}

	}

	destroy_server_window_mutex();

	return EXIT_SUCCESS;
}
