#ifndef __SIMBOLOS_H__
#define __SIMBOLOS_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
	char **simbolos;
	int *ILC;
	int total_simbolos;
	int total_linhas;
} TabelaDeSimbolos;

TabelaDeSimbolos *NewTabelaDeSimbolos();

void AdicionaSimbolo(TabelaDeSimbolos *tabela, char *simbolo, int ILC);

void ImprimeTabela(TabelaDeSimbolos *tabela);

void FreeTabela(TabelaDeSimbolos *tabela);

#endif
