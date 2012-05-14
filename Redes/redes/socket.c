#include "socket.h"

int make_socket () {
	int sock;
	/* Create the socket. */
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket()");
        exit(EXIT_FAILURE);
    }
	return sock;
}

struct sockaddr_in make_sockaddr(char *hostname, uint16_t port) {
    struct sockaddr_in serv_addr;
    struct hostent *server;
    if ((server = gethostbyname(hostname)) == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(EXIT_FAILURE);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(port);

    return serv_addr;
}

