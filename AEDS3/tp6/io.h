#ifndef __IO_H__
#define __IO_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boolean.h"

#define LINE_MAX_SIZE 20

FILE* ParseParams(int argc, char *argv[]);

void RemoveNewlineChar(char *string);

#endif
