#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mv.h"

typedef struct {
	int PC, SP;
	char *filename;
} Args;

Args *GetArgs(int argc, char *argv[]);

#endif
