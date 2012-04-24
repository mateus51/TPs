#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


struct HostInfo {
	char *host;
	int port;
	int buffer_size;
};



int make_socket ();

struct sockaddr_in make_sockaddr(char *hostname, uint16_t port);

