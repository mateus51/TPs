#include "client.h"

int main(int argc, char *argv[]) {
	struct HostInfo *info = (struct HostInfo*) malloc(sizeof(struct HostInfo));
	char *filename;
	read_client_params(argc, argv, &info->host, &info->port, &filename, &info->buffer_size);
	download_file(info, filename);
	free(info->host);
	free(info);
	free(filename);
	return EXIT_SUCCESS;
}

void download_file(struct HostInfo *info, char *filename) {

    // Creating buffer and socket
    char buffer[info->buffer_size];
    int sock = make_socket();
    struct sockaddr_in serv_addr = make_sockaddr(info->host, info->port);

    // Start to count time
    double start = get_time();

    // Connecting to server
    if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(EXIT_FAILURE);
    }

    // Copying file name to buffer
    bzero(buffer,info->buffer_size);
    strcpy(buffer, filename);

    // Sending file name to server
    if (write(sock, buffer, strlen(buffer)) < 0) {
         perror("ERROR writing to socket");
         exit(EXIT_FAILURE);
    }
    bzero(buffer, info->buffer_size);

    // Opening file to be downloaded
    FILE *file;
    if ((file = fopen(filename, "w+")) == NULL) {
    	fwrite(buffer, 1, strlen(buffer) + 1, file);
    	close(sock);
    	exit(EXIT_FAILURE);
    }

    // Receiving file and counting bytes
    int received_bytes = 0, total_received = 0;
    while((received_bytes = read(sock, buffer, info->buffer_size)) > 0) {
    	fprintf(file, "%s", buffer);
    	total_received += received_bytes;
    	bzero(buffer, info->buffer_size);
    }
    close(sock);
    fclose(file);

    // Calculating info and printing
	double total_time = get_time() - start;
	double kbps = (total_received / total_time) / 1024;
	printf("Buffer = \%5u byte(s), \%10.2f kbps (\%u bytes em %3.6f s)\n", info->buffer_size, kbps, total_received, total_time);
}



void print_info(struct HostInfo *info, char *filename) {
	printf(" %s (%s:%d) - buffer: %d\n", filename, info->host, info->port, info->buffer_size);
}

