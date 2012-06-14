#include "tp_socket.h"
#include "window.h"
#include "listener.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/errno.h>
//#include <sys/time.h>
#include <signal.h>
#include <string.h>

int g_sock;
char *g_buffer;
so_addr* g_to_addr;


// #### COMMON FUNCTIONS ####

Window* new_window(int window_size, int buffer_size, int socket, so_addr *cli_addr) {
	Window *window = (Window*) malloc(sizeof(Window));
	int mtu = tp_mtu();
	window->size = window_size;
	window->buffer_size = mtu > buffer_size ? buffer_size : mtu;
	window->start = window->next = 0;
	window->full = False;
	window->empty = True;
	window->info = (SocketInfo*) malloc(sizeof(SocketInfo));
	window->info->socket = socket;
	window->info->addr = cli_addr;
	window->buffers = (Buffer**) malloc(sizeof(Buffer*) * window->size);
	int i;
	for (i = 0; i < window_size; i++) {
		window->buffers[i] = (Buffer*) malloc(sizeof(Buffer));
		window->buffers[i]->buffer = (byte*) malloc(window->buffer_size);
		bzero(window->buffers[i]->buffer, window->buffer_size);
		window->buffers[i]->received = False;
	}
	return window;
}

void free_window(Window *window) {
	int i;
	for (i = 0; i < window->size; i++) {
		free(window->buffers[i]->buffer);
		free(window->buffers[i]);
	}
	free(window->buffers);
	free(window->info);
	free(window);
}


int send_MSG(int sock, so_addr *to_addr, MSG msg, byte seq) {
	byte buffer[HEADER_SIZE];
	bzero(buffer, HEADER_SIZE);
	buffer[0] = msg;
	buffer[1] = seq;
	return tp_sendto(sock, buffer, HEADER_SIZE, to_addr);
}

byte get_parity_byte(char *str, int size) {
	int i, result, sum = 0;//, j, mask = 1;
//	byte chr;
	for (i = 0; i < size; i++) {
//		chr = str[i];
//		for (j = 0; j < 8; j++) {
//			if (chr & mask)
//				sum++;
//			chr >>= 1;
//		}
		sum += str[i];
	}
	result = sum % 256;
	return result;
//	return 1;
}

// returns the positions of this seq number in the window.
// requires that the first position be occupied. If it's not,
// it will assume that the first packet hasn't arrived.
int get_pos(Window *window, int seq) {
	int first_seq;
	if (window->buffers[window->start]->received == False)
		first_seq = 0;
	else
		first_seq = window->buffers[window->start]->buffer[1];
	int pos = seq - first_seq + window->start;
	if (pos >= window->size) {
		pos -= window->size;
		// window not big enough
		if (pos >= window->start)
			return -1;
	}
	return pos;
}

// resends a packet.
int resend(Window *window, int seq) {
	int pos = get_pos(window, seq);
	return tp_sendto(window->info->socket, window->buffers[pos]->buffer, strlen(window->buffers[pos]->buffer + HEADER_SIZE) + HEADER_SIZE + TAIL_SIZE + 1, window->info->addr);
}

// resends the older packet in window
int resend_older(Window *window) {
	int pos;
	if (window->buffers[window->start]->received) {
		pos = window->start + 1;
		if (pos == window->size) pos = 0;
	}
	else
		pos = window->start;

	printf("  resending %d\n", window->buffers[pos]->buffer[1]);
	return tp_sendto(window->info->socket, window->buffers[pos]->buffer, strlen(window->buffers[pos]->buffer + HEADER_SIZE) + HEADER_SIZE + TAIL_SIZE + 1, window->info->addr);
}


boolean check_parity_byte(char *buffer, int size) {
	byte par = get_parity_byte(buffer, size - 1);
	return par == buffer[size - 1];
}

boolean window_full(Window *window) {
	return (window->next == window->start) && (!window->empty);
}

void slide_window_start(Window *window) {
	window->buffers[window->start]->received = False;
	window->start++;
	if (window->start == window->size) window->start = 0;
	if (window->full) window->full = False;
	if (window->start == window->next) window->empty = True;
}









// #### CLIENT FUNCTIONS ####

void write_to_file(Window *window, FILE *file) {

	int next = window->start + 1;
	if (next == window->size)
		next = 0;

	while (window->buffers[next]->received) {
		printf("  writing buffer %d\n", window->buffers[window->start]->buffer[1]);
		char received = window->buffers[next]->received ? 'T' : 'F';
		switch (window->buffers[next]->buffer[0]) {
		case MORE:
			printf("  next [MORE %d] (%c)\n", window->buffers[next]->buffer[1], received);
			break;
		case END:
			printf("  next [END %d] (%c)\n", window->buffers[next]->buffer[1], received);
			break;
		}

		// writing buffer
		fwrite(window->buffers[window->start]->buffer + HEADER_SIZE, 1, strlen(window->buffers[window->start]->buffer + HEADER_SIZE), file);
		window->buffers[window->start]->received = False;

//		printf("wrote:\n%s\n", window->buffers[window->start]->buffer + HEADER_SIZE);

		// moving pointers
//		window->start++;
//		if (window->start == window->size)
//			window->start = 0;
		slide_window_start(window);

		next = window->start + 1;
		if (next == window->size)
			next = 0;
	}

	char received = window->buffers[next]->received ? 'T' : 'F';
	switch (window->buffers[next]->buffer[0]) {
	case MORE:
		printf("  next [MORE %d] (%c)\n", window->buffers[next]->buffer[1], received);
		break;
	case END:
		printf("  next [END %d] (%c)\n", window->buffers[next]->buffer[1], received);
		break;
	}
}

// on success returns 0;
int store_buffer(Window *window, char *buffer, FILE *file) {

	boolean ok = check_parity_byte(buffer, window->buffer_size);
	if (!ok)
		return -1;

	byte seq = buffer[1];
	int pos = get_pos(window, seq);

	switch (buffer[0]) {
	case MORE:
		printf("storing [MORE %d]\n", buffer[1]);
		break;
	case END:
		printf("storing [END %d]\n", buffer[1]);
		break;
	}

	if (pos == window->start)
		set_alarm(1);

	bzero(window->buffers[pos]->buffer, window->buffer_size);
	memcpy(window->buffers[pos]->buffer, buffer, strlen(buffer + HEADER_SIZE) + HEADER_SIZE + TAIL_SIZE + 1);
	window->buffers[pos]->received = True;
	if (window->empty) window->empty = False;

	switch (window->buffers[pos]->buffer[0]) {
	case MORE:
		printf("stored [MORE %d]\n", window->buffers[pos]->buffer[1]);
		break;
	case END:
		printf("stored [END %d]\n", window->buffers[pos]->buffer[1]);
		break;
	}

	// se recebeu o próximo a ser escrito
	if (window->buffers[window->start]->received) {
		write_to_file(window, file);
	}

	return 0;
}

int receive_and_store(Window *window, FILE *file) {
	int bytes_recv, resp;
	char buffer[window->buffer_size];

	resp = tp_recvfrom(window->info->socket, buffer, window->buffer_size, window->info->addr);
	if (resp < 0) {
		perror("receive_and_store() > tp_recvfrom()");
		exit(EXIT_FAILURE);
	}

	byte ack = buffer[0], seq = buffer[1];
	if (store_buffer(window, buffer, file) == 0)
		send_MSG(window->info->socket, window->info->addr, ACK, seq);
	else
		send_MSG(window->info->socket, window->info->addr, FAIL, seq);

	switch (ack) {
	case MORE:
		bytes_recv = strlen(buffer + HEADER_SIZE);
		break;
	case END:
		// end of file
		bytes_recv = 0;
		break;
	default:
		printf("default case!\n");
		bytes_recv = -1;
		break;
	}

	return bytes_recv;
}


// #### SERVER FUNCTIONS ####

int fill_and_send_next_slot(Window *window, FILE *file) {
	// mutex to access the window
//	extern pthread_mutex_t server_window;
//	pthread_mutex_t *server_window = get_server_window_mutex();

	// lock to check window state
//	pthread_mutex_lock(server_window);
	lock_server_window_mutex();

	if (!window->full) {
		int bytes_read, resp;

		// posição do próximo slot na janela
		int pos = window->next;

		// próximo número de sequência
		unsigned char seq;
		if (window->empty) {
			seq = 0;
		}
		else {
			int last = window->next - 1;
			if (last < 0) last = window->size - 1;
			seq = ((unsigned char) window->buffers[last]->buffer[1]) + 1;
		}

		// unlock to read from disk
//		pthread_mutex_unlock(server_window);


		printf("fill_and_send_next_slot()\n");

		// guarda as duas primeiras posições para cabeçalho e a última para o '/0' da string.
		bzero(window->buffers[pos]->buffer, window->buffer_size);
		bytes_read = fread(window->buffers[pos]->buffer + HEADER_SIZE, 1, window->buffer_size - HEADER_SIZE - TAIL_SIZE - 1, file);
		if (bytes_read == 0) {
			// acabou o arquivo
			window->buffers[pos]->buffer[0] = END;
			window->buffers[pos]->buffer[1] = seq;
			window->buffers[pos]->buffer[2] = '\0';
		} else {
			window->buffers[pos]->buffer[0] = MORE;
			window->buffers[pos]->buffer[1] = seq;
			window->buffers[pos]->buffer[bytes_read + 2] = '\0';
			printf("  window->buffers[pos]->buffer[%d] = '\\0'", bytes_read + 2);
		}
		byte parity = get_parity_byte(window->buffers[pos]->buffer, window->buffer_size - 1);
		window->buffers[pos]->buffer[window->buffer_size - 1] = parity;

		printf("  read %d bytes\n", bytes_read);
		printf("  sending...\n");
		switch (window->buffers[pos]->buffer[0]) {
		case ACK:
			printf("    msg: ACK\n");
			break;
		case MORE:
			printf("    msg: MORE\n");
			break;
		case FAIL:
			printf("    msg: FAIL\n");
			break;
		case END:
			printf("    msg: END\n");
			break;
		}
		printf("    seq: %d\n", window->buffers[pos]->buffer[1]);
		printf("    crc: %d\n", window->buffers[pos]->buffer[window->buffer_size - 1]);

//		resp = tp_sendto(window->info->socket, window->buffers[pos]->buffer, strlen(window->buffers[pos]->buffer + HEADER_SIZE) + HEADER_SIZE + TAIL_SIZE + 1, window->info->addr);
		resp = tp_sendto(window->info->socket, window->buffers[pos]->buffer, window->buffer_size, window->info->addr);
		if (resp < 0) {
			perror("fill_and_send_next_slot() >  tp_sendto()");
			exit(EXIT_FAILURE);
		}

		// maybe these 2 commands require a mutex
		window->next++;
		if (window->next == window->size) window->next = 0;
		if (window_full(window)) window->full = True;
		window->empty = False;

		unlock_server_window_mutex();
		return bytes_read;
	}

	// window is full. nothing to do.
	else {
		unlock_server_window_mutex();
		return -1;
	}
}

// slide the window while it's possible.
// returns a boolean that indicates if the client received all parts
boolean slide_window(Window *window) {
	boolean slided_end = False;
	if (window->buffers[window->start]->received) {
//		printf("start received!\n");
		int next = window->start + 1;
		if (next == window->size) next = 0;

		printf("sliding window...\n");
		while (window->buffers[next]->received) {
			printf("  window->start (old): %d\n", window->start);
			slide_window_start(window);
			printf("  window->start (new): %d\n", window->start);
			printf("  window->next: %d\n", window->next);
			next = window->start + 1;
			if (next == window->size) next = 0;
		}

		// If last packet is END, slide it and return true;
		if (window->buffers[window->start]->received && window->buffers[window->start]->buffer[0] == END) {
			printf("  sliding END...\n");
			slide_window_start(window);
			slided_end = True;
		}
	}

	return slided_end;
}

// returns a boolean that indicates if the client received all parts
boolean mark_received_by_client(Window *window, byte seq) {
	// getting position on window & marking as received
	int pos = get_pos(window, seq);
	window->buffers[pos]->received = True;

	// sliding window if possible
	boolean slided_end = False;
	if (window->buffers[window->start]->received && !window->empty)
		slided_end = slide_window(window);

	return slided_end;
}




void timeout_handler(int signum) {
	tp_sendto(g_sock, g_buffer, strlen(g_buffer) + 1, g_to_addr);
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


