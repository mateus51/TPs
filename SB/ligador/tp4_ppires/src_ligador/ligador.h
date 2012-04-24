#ifndef __LIGADOR_H__
#define __LIGADOR_H__

#define LINE_MAX_SIZE 500
#define SYMBOL_MAX_SIZE 100

#include "simbolos.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void BuildMasterSymbolTable(TabelaDeSimbolos *tabela);

void LinkObjects(TabelaDeSimbolos *tabela);

int GetOperandFromSymbol(TabelaDeSimbolos *tabela, char *token, int ILC);

void RemoveNewlineChar(char *string);

#endif
