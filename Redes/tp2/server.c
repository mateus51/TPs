#include "server.h"
#include "window.h"

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define WAIT_TIME 1 // in seconds

boolean keep_listening;

void *ACKListener(void *info) {
	Window *window = (Window*) info;
	byte buffer[2];
	unsigned char seq;
	int resp;

	while(keep_listening){
		resp = tp_recvfrom(window->info->socket, buffer, 2, NULL);
		if (resp < 0) {
			perror("ACKlistener()");
//			exit(EXIT_FAILURE);
		}
		 if (buffer[0] == ACK) {
			 printf("ACKlistener: ACK %d\n", buffer[1]);
			 seq = (unsigned char) buffer[1];
			 window->buffers[seq]->received = True;
		 }
		 else if (buffer[0] == FAIL) {
			 printf("ACKlistener: FAIL\n");
		 }
		 else {
			 printf("ACKlistener: ???\n");
		 }
	}
   pthread_exit(NULL);
   return NULL; // only to remove warning.
}

pthread_t startListener(Window *window) {
	int rc;
	pthread_t thread;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	rc = pthread_create(&thread, &attr, ACKListener, (void*) window);
	if (rc) {
		 printf("ERROR: return code from pthread_create() is %d\n", rc);
		 exit(EXIT_FAILURE);
	}
	pthread_attr_destroy(&attr);
	return thread;
}

void stopListener (pthread_t thread) {
	int rc;
	keep_listening = False;
	rc = pthread_join(thread, NULL);
	if (rc) {
		printf("ERROR; return code from pthread_join() is %d\n", rc);
		exit(EXIT_FAILURE);
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
		bzero(buffer, buffer_size);

		// receiving file name from client
		confirmed_recvfrom(server_sock, buffer, buffer_size, &client_addr);

		// printing host info
		char host[256];
		getnameinfo((struct sockaddr *)&client_addr, sizeof(client_addr), host, 256, 0, 0, 0);
		printf("Message Received: '%s'\n", buffer);
		printf("  From: %s\n", host);

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

		int i, bytes_read, buffers_to_send, current_slot = 0;
		boolean window_full = False, sent = False, received = False, has_more_data = True;
		while(!sent) {

			// filling buffers
			while (!window_full && has_more_data) {
				// 2 bytes header
				window->buffers[current_slot]->buffer[0] = MORE;
				window->buffers[current_slot]->buffer[1] = current_slot;
				bytes_read = fread(window->buffers[current_slot] + 2, 1, buffer_size - 3, file);
				if (bytes_read == 0) {
					has_more_data = False;
					buffers_to_send = current_slot;
				} else if (current_slot == window->window_size - 1) {
					window_full = True;
					buffers_to_send = current_slot + 1;
					current_slot = 0;
				}
				else {
					// put '\0' to use strlen() when sending
					window->buffers[current_slot]->buffer[bytes_read + 2] = '\0';
					current_slot++;
				}
			}
			window_full = False;

			// starting ACK listener
			pthread_t thread = startListener(window);

			// sending data
			for (i = 0; i < buffers_to_send; i++) {
				tp_sendto(server_sock, window->buffers[i]->buffer, strlen(window->buffers[i]->buffer), &client_addr);
			}

			// checking if everything was received
			received = False;
			while (!received) {
				received = True;
				for (i = 0; i < buffers_to_send; i++) {
					if (!window->buffers[i]->received) {
						received = False;
						tp_sendto(server_sock, window->buffers[i]->buffer, strlen(window->buffers[i]->buffer), &client_addr);
					}
				}
				if (!received) sleep(WAIT_TIME);
			}

			// disable listener
			stopListener(thread);

			// all sent!
			if (!has_more_data) {
				send_MSG(window->info->socket, window->info->cli_addr, END, 0);
				sent = True;
			}

		}


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
