#include "server.h"

int main(int argc, char *argv[]) {
	struct HostInfo *info = (struct HostInfo*) malloc(sizeof(struct HostInfo));
	read_server_params(argc, argv, &info->port, &info->buffer_size);
	info->host = NULL;
	send_file(info);
	free(info);
	return EXIT_SUCCESS;
}

void send_file(struct HostInfo *info) {

    // Creating sockets anf buffer
    int client_sock;
    socklen_t clilen;
    char buffer[info->buffer_size];
    struct sockaddr_in serv_addr, cli_addr;
    int sock = make_socket();
    int n;

    // Configuring and binding the server to an address
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(info->port);
    if (bind(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    	perror("ERROR on binding");
    	exit(EXIT_FAILURE);
    }

    // Start to listen for new connections
    listen(sock, 1);
    clilen = sizeof(cli_addr);

    // Accepting a new connection from the client. If the server
    // were supposed to run in an endless loop, this would be the
    // start of it
    if ((client_sock = accept(sock, (struct sockaddr *) &cli_addr, &clilen)) < 0) {
    	perror("ERROR on accept");
    	exit(EXIT_FAILURE);
    }

    // Receiving file name
    bzero(buffer, info->buffer_size);
    n = read(client_sock, buffer, info->buffer_size);
    if (n < 0) {
    	perror("ERROR reading from socket");
    	exit(EXIT_FAILURE);
    }

	// Opening file to be sent
	FILE *file;
	if ((file = fopen(buffer, "r")) == NULL) {
		fprintf(stderr, "File '%s' could not be read.\n", buffer);
		close(sock); // Closing connection
		free(info);
		exit(EXIT_FAILURE);
	}

	// Reading file and sending to client
	int sent_bytes = 0, total_sent = 0;
	bzero(buffer, info->buffer_size);
	while(fread(buffer, 1, info->buffer_size, file) != 0) {
		sent_bytes = write(client_sock, buffer, strlen(buffer));
		if (sent_bytes < 0) {
			perror("send()");
			exit(EXIT_FAILURE);
		}
		total_sent += sent_bytes;
		sent_bytes = 0;
		bzero(buffer, info->buffer_size);
	}
	printf("%d bytes sent!\n", total_sent);
	fclose(file);
    close(client_sock);
    // Here would be the end of the server loop

    close(sock);
}

