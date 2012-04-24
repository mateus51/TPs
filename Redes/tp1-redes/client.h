#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "socket.h"
#include "time.h"
#include "io.h"



void download_file(struct HostInfo *info, char *filename);

void print_info(struct HostInfo *info, char *filename);
