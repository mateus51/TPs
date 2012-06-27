#ifndef __SYM_TABLE_H__
#define __SYM_TABLE_H__

//typedef char boolean;
#define True  1
#define False 0

#define TABLE_INITIAL_CAPACITY 32
#define TABLE_GROWTH_FACTOR 2
#define NUM_SCOPES 50

#define DBG False//True

typedef enum {
	nulltype, integer, real, character, boolean, program
} Type;

typedef struct Symbol {
    char *name;
    Type type;
    int num_params;
    int scope;
    int line;
    int first_column;
    int last_column;
    int width;
} Symbol;

typedef struct {
	Symbol** items;
	int capacity;
	int last;
	int scopes[NUM_SCOPES];
	int current_scope;
} SymbolTable;


char *typeStr(Type type);

void erro(char *message);

void initTable(SymbolTable *table);

Symbol *newSymbol(char *name, Type type, int scope, int line, int column);

void openScope(SymbolTable *table);

void closeScope(SymbolTable *table);

int getSymbol(SymbolTable *table, char *name);

Type lookupType(SymbolTable *table, int index);

int installId(SymbolTable *table, char *name, int linha_atual, int coluna_atual);

void updateType(SymbolTable *table, int var_index, Type type);

void printTable(SymbolTable*);

#endif
