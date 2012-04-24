#ifndef MONTADOR_H
#define MONTADOR_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define LINE_MAX_SIZE 500


#define LOAD  1
#define STORE 2
#define JMP   3
#define JPG   4
#define JPE   5
#define JPL   6
#define JPNE  7
#define PUSH  8
#define POP   9
#define READ  10
#define WRITE 11
#define CALL  12
#define RET   13
#define ADD   14
#define SUB   15
#define XOR   16
#define AND   17
#define OR    18
#define HALT  19


typedef struct {
	char **simbolos;
	int *ILC;
	int total_simbolos;
	int total_linhas;
} TabelaDeSimbolos;

TabelaDeSimbolos *ConstroiTabelaDeSimbolos(FILE *file);

void AdicionaSimbolo(TabelaDeSimbolos *tabela, char *simbolo, int ILC);

void TraduzPrograma(FILE *file, TabelaDeSimbolos *tabela);

FILE *OutputFileWithSymbolTable(TabelaDeSimbolos *tabela);

int GetOpcodeFromToken(char *token);

int GetOperandFromSymbol(TabelaDeSimbolos *tabela, char *token, int ILC);

void ImprimeTabela(TabelaDeSimbolos *tabela);

void FreeTabela(TabelaDeSimbolos *tabela);

void RemoveNewlineChar(char *string);

void RemoveCommentFromLine(char *string);

#endif
