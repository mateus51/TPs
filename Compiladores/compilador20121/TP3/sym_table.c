#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char boolean;
#define True  1
#define False 0

#define TABLE_INITIAL_CAPACITY 32
#define TABLE_GROWTH_FACTOR 2
#define NUM_SCOPES 50

typedef struct Symbol {
    char *name;
    char *type;
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

void printTable(SymbolTable*);

void erro(SymbolTable *table, char *message) {
	printf("Erro! - %s\n\n", message);
	printTable(table);
	exit(EXIT_FAILURE);
}

/* Initializes the symbol table */
void initTable(SymbolTable *table) {
	table->capacity = TABLE_INITIAL_CAPACITY;
	table->items = (Symbol**) malloc(sizeof(Symbol*) * table->capacity);
	table->last = 0;
	table->current_scope = 0;
	int i;
	for (i = 0; i < table->capacity; i++)
		table->items[i] = NULL;
	for (i = 0; i < NUM_SCOPES; i++)
		table->scopes[i] = 0;
}

/* Creates a new symbol */
Symbol *newSymbol(char *name, char *type, int scope, int line, int column) {
//	printf("TABLE: %s(%d, %d)\n", name, line, column);
	Symbol *symbol = (Symbol*) malloc(sizeof(Symbol));
	symbol->name = (char*) malloc(sizeof(char) * strlen(name) + 1);
	strcpy(symbol->name, name);
	if (symbol->type != NULL) {
		symbol->type = (char*) malloc(sizeof(char) * strlen(type) + 1);
		strcpy(symbol->type, type);
	}
	else
		symbol->type = NULL;

	symbol->line = line;
	symbol->column = column;
	symbol->scope = scope;
	return symbol;
}



void openScope(SymbolTable *table) {
	printf("\n\nOpening scope...\n  previous: %d\n", table->current_scope);

	table->current_scope++;
	if (table->current_scope >= NUM_SCOPES)
		erro(table, "Não é possível abrir um novo nível.\n");
	else
		table->scopes[table->current_scope] = table->last;

	printf("  current: %d\n\n", table->current_scope);
}


void closeScope(SymbolTable *table) {
	table->last = table->scopes[table->current_scope];
	table->current_scope--;
}

/* Returns the symbol index in the table. Symbol must be in the table. */
int getSymbol(SymbolTable *table, char *name) {
	printf("\n\n looking for '%s'...", name);
	int i;
	for (i = table->last-1; i >= 0; i--) {
		if (!strcmp(name, table->items[i]->name))
			return i;

	}
	erro(table, "Símbolo não encontrado!");
}

void checkTableCapacity(SymbolTable *table) {
	if (table->last == table->capacity) {
		table->capacity = table->capacity * TABLE_GROWTH_FACTOR;
		table->items = (Symbol**) realloc(table->items, sizeof(Symbol*) * table->capacity);
		if (table->items == NULL)
			erro(table, "Falha ao alocar espaço para a tabela de símbolos!\n");
	}
}

void installId(SymbolTable *table, char *name, int line, int column) {
	int i;
	for (i = table->last-1; i >= table->scopes[table->current_scope]; i--)
		if (!strcmp(table->items[i]->name, name))
			return;

	checkTableCapacity(table);
	Symbol *symbol = newSymbol(name, NULL, table->current_scope, line, column);
	symbol->scope = table->current_scope;
	table->items[table->last] = symbol;
	table->last++;

	printf("\n\n");
	printf("TABLE: symbol %s (%d, %d) installed.\n", table->items[table->last-1]->name, table->items[table->last-1]->line, table->items[table->last-1]->column);
	printf("  current scope: %d\n", table->current_scope);
	printf("  symbol scope: %d\n", table->current_scope);
	printf("\n");
	printTable(table);
}

/* Updates the symbol type in the table */
void updateType(SymbolTable *table, int var_index, char *type) {
	printf("\n\n");
	printf("TABLE: Updating type of %s (scope %d)...\n", table->items[var_index]->name, table->items[var_index]->scope);
	if (table->items[var_index]->type != NULL)
		erro(table, "Tipo de variável já foi especificado!");
	else {
		table->items[var_index]->type = (char*) malloc(sizeof(char) * strlen(type) + 1);
		strcpy(table->items[var_index]->type, type);
	}

	printf("  type updated to '%s'.\n\n", table->items[var_index]->type);
}

/* Prints the symbol table */
void printTable(SymbolTable *table) {
    printf("%16s %16s %16s %16s %16s\n\n", "NOME", "TYPE", "SCOPE", "LINHA", "COLUNA");
    int i;
    for (i = 0; i < table->last; i++) {
//    	printf("%16s %16s %16d %16d %16d\n", table->items[i]->name, table->items[i]->type, table->items[i]->scope, table->items[i]->line, table->items[i]->column);
    	printf("%16s ", table->items[i]->name);
    	printf("%16s ", table->items[i]->type);
    	printf("%16d ", table->items[i]->scope);
    	printf("%16d ", table->items[i]->line);
    	printf("%16d\n", table->items[i]->column);
    }
}

//char *concat(char *str1, char *str2) {
//	str1 = (char*) realloc(str1, sizeof(char) * strlen(str2));
//	return strcat(str1, str2);
//}

//void main(void) {
//	return;
//}
