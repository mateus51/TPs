#ifndef __SYM_TABLE_H__
#define __SYM_TABLE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char boolean;
#define True  1
#define False 0

#define TABLE_INITIAL_CAPACITY 32
#define TABLE_GROWTH_FACTOR 2
#define NUM_SCOPES 50

#define DBG False//True

typedef struct Symbol {
    char *name;
    char *type;
    int num_params;
    int scope;
    int line;
    int column;
} Symbol;

typedef struct {
	Symbol** items;
	int capacity;
	int last;
	int scopes[NUM_SCOPES];
	int current_scope;
} SymbolTable;


void erro(SymbolTable *table, char *message);

void initTable(SymbolTable *table);

Symbol *newSymbol(char *name, char *type, int scope, int line, int column);

void openScope(SymbolTable *table);

void closeScope(SymbolTable *table);

int getSymbol(SymbolTable *table, char *name);

void checkTableCapacity(SymbolTable *table);

int installId(SymbolTable *table, char *name, int line, int column);

void updateType(SymbolTable *table, int var_index, char *type);

void printTable(SymbolTable*);

#endif
