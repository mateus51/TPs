#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <signal.h>
#include <string.h>
#include "tp_socket.h"
#include "window.h"

int g_sock;
char *g_buffer;
so_addr* g_to_addr;


Window* new_window(int window_size, int buffer_size, int socket, so_addr *cli_addr) {
	Window *window = (Window*) malloc(sizeof(Window));
	int mtu = tp_mtu();
	window->buffer_size = mtu > buffer_size ? buffer_size : mtu;
	window->start = window->end = 0;
	window->info = (SocketInfo*) malloc(sizeof(SocketInfo));
	window->info->socket = socket;
	window->info->cli_addr = cli_addr;
	window->buffers = (Buffer**) malloc(sizeof(Buffer*) * window_size);
	int i;
	for (i = 0; i < window_size; i++) {
		window->buffers[i] = (Buffer*) malloc(sizeof(Buffer));
		window->buffers[i]->buffer = (byte*) malloc(buffer_size);
		window->buffers[i]->received = False;
	}
	return window;
}


void timeout_handler(int signum) {
	psignal(signum, "ALARM");
	tp_sendto(g_sock, g_buffer, strlen(g_buffer) + 1, g_to_addr);
//    fprintf(stderr,"%s\n", strsignal(signum));

    /* Uma outra opção seria setar uma variável global
     * e testá-la no loop principal do programa, mas isso
     * só funcionaria nos casos onde a chamada bloqueada
     * fosse interrompida pelo sinal
     * (o que não acontece no caso do teclado, pelo menos).
     */
//    mysettimer(espera);  /* Melhor lugar para reiniciar o timer */
	alarm(1);
}


/*
 * usada para o cliente enviar o nome do arquivo para o servidor
 */
int confirmed_sendto(int sock, char *buffer, int buff_len, so_addr* to_addr) {
	// Variável globais para que a rotina de temporização consiga
	// reenviar o pacote caso ocorra timeout.
	g_sock = sock;
	g_buffer = buffer;
	g_to_addr = to_addr;
	signal(SIGALRM, timeout_handler);
	int sent;
	boolean received = False;
	char buff[2];
	alarm(1);
	while (!received) {
		sent = tp_sendto(sock, buffer, strlen(buffer) + 1, to_addr);
//		recv = tp_recvfrom(sock, buff, 2, to_addr);
        if (tp_recvfrom(sock, buff, 2, to_addr) < 0) {
            /* chamadas de socket só retornam < 0 se deu erro */

        	printf("dentro do if\n");

            if (errno == EINTR) {
                /* uma chamada interrompida seria tratada aqui */
            	printf("errno == EINTR\n");
            	sent = tp_sendto(sock, buffer, strlen(buffer) + 1, to_addr);
                errno = 0;
            }
            else if (errno) {
                perror("tp_recvfrom()");
                exit(EXIT_FAILURE);
            }
        }
        else {
        	printf("buffer: [%d %d]\n", buff[0], buff[1]);
        	if (buff[0] == ACK) {
        		received = True;
				alarm(0); // disable timer
        	}
        	else if (buff[0] == FAIL) {
        		printf("request FAILED!\n");
        	}
        	else {
        		printf("header wasnt ACK nor FAIL");
        	}
        }

	}
	return sent;
}


/*
 * usada pelo servidor para receber o nome do arquivo.
 */
int confirmed_recvfrom(int sock, char* buffer, int buff_len, so_addr* from_addr) {
	boolean received = False;
	int resp;
	while (!received) {
		resp = tp_recvfrom(sock, buffer, buff_len, from_addr);
		if (resp < 0) {
			perror("tp_recvfrom()");
		}
		else {
			received = True;
		}

	}
	send_MSG(sock, from_addr, ACK, buffer[2]);
	return resp;
}

int send_MSG(int sock, so_addr *to_addr, MSG msg, byte seq) {
//	printf("will sleep for 3\n");
//	sleep(3);
//	printf("woke up!\n");
	byte buffer[2] = {msg, seq};
	return tp_sendto(sock, buffer, 2, to_addr);
}
