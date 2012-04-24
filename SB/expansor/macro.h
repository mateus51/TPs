#ifndef MACRO_H
#define MACRO_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "boolean.h"

#define LINE_MAX_SIZE 500

typedef struct {
	char *name;
	char *arg;
	char **instructions;
	int total_instructions;
} Macro;


Macro *NewMacro(char *name, char *arg);

void ExpandMacro(Macro **macros, int index, FILE *file, char *arg);

int IsMacro(Macro **macros, char *token);

void FreeMacro(Macro *macro);

void FreeArrayMacros(Macro **macros);

void PrintMacro(Macro *macro);

void AddInstruction(Macro *macro, char *command);

#endif
