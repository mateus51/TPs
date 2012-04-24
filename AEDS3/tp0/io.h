#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "TADeleicao.h"

#define LINE_MAX_SIZE 203
#define NAME_MAX_SIZE 50

FILE* ParseParams(int argc, char *argv[]);

Eleicao LeEleicao(FILE *file);

void ChangeNewLineToNull(char *string);

#endif
