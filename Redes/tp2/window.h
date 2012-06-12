#include "tp_socket.h"

typedef char byte;
typedef char boolean;

#define True 1
#define False 0


typedef struct {
	so_addr *cli_addr;
	int socket;
} SocketInfo;

typedef struct {
	byte *buffer;
	boolean received;
} Buffer;

typedef struct {
	Buffer **buffers;
	int buffer_size;
	int window_size;
	byte start, end;
	SocketInfo *info;
} Window;


typedef enum {
	ACK,
	FAIL,
	MORE,
	END
} MSG;

Window* new_window(int window_size, int buffer_size, int socket, so_addr *cli_addr);

int confirmed_sendto(int sock, char *buffer, int buff_len, so_addr* to_addr);

int confirmed_recvfrom(int sock, char* buffer, int buff_len, so_addr* from_addr);

int send_MSG(int sock, so_addr *to_addr, MSG msg, byte seq);
