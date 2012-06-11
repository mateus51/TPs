#include "tp_socket.h"

typedef char byte;
typedef char boolean;

#define True 1
#define False 0


typedef struct buffer {
	byte *buffer;
	boolean received;
} Buffer;

enum MSGs {
	ACK = 69,
	FAIL
};

int confirmed_sendto(int sock, char *buffer, int buff_len, so_addr* to_addr);

int confirmed_recvfrom(int sock, char* buffer, int buff_len, so_addr* from_addr);

int send_ack(int sock, so_addr *to_addr, byte seq);
