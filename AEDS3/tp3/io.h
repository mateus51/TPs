#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "show.h"

FILE* ParseParams(int argc, char *argv[]);

Show *ReadShowFromFile(FILE *file);

#endif
