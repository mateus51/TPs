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


void init_buffer(Buffer *buffer, int buffer_size) {
	buffer->buffer = (byte*) malloc(buffer_size);
	buffer->received = False;
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
	int sent, recv;
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
            received = True;
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
	send_ack(sock, from_addr, buffer[2]);
	return resp;
}

int send_ack(int sock, so_addr *to_addr, byte seq) {
	printf("will sleep for 3\n");
	sleep(3);
	printf("woke up!\n");
	byte ack[2] = {ACK, seq};
	return tp_sendto(sock, ack, 2, to_addr);
}
