#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX_SIZE 203
#define NAME_MAX_SIZE 50

void read_client_params(int argc, char *argv[], char **host, int *port, char **filename, int *buffer_size);

void read_server_params(int argc, char *argv[], int *port, int *buffer_size);

#endif
