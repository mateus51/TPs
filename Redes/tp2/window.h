#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "tp_socket.h"
#include <stdio.h> // for FILE definition

typedef char byte;

typedef char boolean;
#define True 1
#define False 0

#define HEADER_SIZE 2
#define TAIL_SIZE 1

typedef struct {
	so_addr *addr;
	int socket;
} SocketInfo;

typedef struct {
	byte *buffer;
	boolean received;
} Buffer;

typedef struct {
	Buffer **buffers;
	int buffer_size;
	int size;
	boolean full, empty;
	int start, next;
	SocketInfo *info;
} Window;


typedef enum {
	ACK = 1,
	FAIL,
	MORE,
	END
} MSG;

Window* new_window(int window_size, int buffer_size, int socket, so_addr *addr);

void free_window(Window *window);

int receive_and_store(Window *window, FILE *file);

int fill_and_send_next_slot(Window *window, FILE *file);

int confirmed_sendto(int sock, char *buffer, int buff_len, so_addr* to_addr);

int confirmed_recvfrom(int sock, char* buffer, int buff_len, so_addr* from_addr);

int send_MSG(int sock, so_addr *to_addr, MSG msg, byte seq);

boolean mark_received_by_client(Window *window, byte seq);

int resend(Window *window, int seq);

int resend_older(Window *window);

#endif
