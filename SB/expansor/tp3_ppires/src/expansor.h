#ifndef EXPANSOR_H
#define EXPANSOR_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "macro.h"

Macro **LeMacros(FILE *file);

void WriteFile(FILE *file, Macro **macros);

Macro **AppendNullPointer(Macro **macros, int counter);

void RemoveNewlineChar(char *string);

void RemoveCommentFromLine(char *string);

#endif
