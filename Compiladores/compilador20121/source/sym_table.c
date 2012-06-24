#include "sym_table.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void checkTableCapacity(SymbolTable *table) {
	if (table->last == table->capacity) {
		table->capacity = table->capacity * TABLE_GROWTH_FACTOR;
		table->items = (Symbol**) realloc(table->items, sizeof(Symbol*) * table->capacity);
		if (table->items == NULL) {
			fprintf(stderr, "Falha ao alocar espaço para a tabela de símbolos!\n");
			exit(EXIT_FAILURE);
		}
	}
}

void erro(char *message) {
//	extern int linha_atual;
	fprintf(stderr, "Error: %s\n", message);
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
	int name_size = strlen(name);
	Symbol *symbol = (Symbol*) malloc(sizeof(Symbol));
	symbol->name = (char*) malloc(sizeof(char) * name_size + 1);
	strcpy(symbol->name, name);
	if (symbol->type != NULL) {
		symbol->type = (char*) malloc(sizeof(char) * strlen(type) + 1);
		strcpy(symbol->type, type);
	}
	else
		symbol->type = NULL;

	symbol->line = line;
	symbol->first_column = column;
	symbol->last_column = symbol->first_column + strlen(name) - 1;
	symbol->scope = scope;
	symbol->num_params = 0;
	return symbol;
}



void openScope(SymbolTable *table) {
	if (DBG)
		printf("\n\nOpening scope...\n  previous: %d\n", table->current_scope);

	table->current_scope++;
	if (table->current_scope >= NUM_SCOPES)
		erro("Não é possível abrir um novo nível.\n");
	else
		table->scopes[table->current_scope] = table->last;

	if (DBG)
		printf("  current: %d\n\n", table->current_scope);
}


void closeScope(SymbolTable *table) {
	table->last = table->scopes[table->current_scope];
	table->current_scope--;
}

/* Returns the symbol index in the table. Symbol must be in the table. */
int getSymbol(SymbolTable *table, char *name) {
	if (DBG)
		printf("\n\n looking for '%s'...", name);

	int i;
	for (i = table->last-1; i >= 0; i--) {
		if (!strcmp(name, table->items[i]->name))
			return i;

	}
	erro("Símbolo não encontrado!");
	return 0;
}

char *lookupType(SymbolTable *table, int index) {
	return table->items[index]->type;
}

int installId(SymbolTable *table, char *name, int linha_atual, int coluna_atual) {
	int i;
	for (i = table->last-1; i >= table->scopes[table->current_scope]; i--)
		if (!strcmp(table->items[i]->name, name))
			return i;

	checkTableCapacity(table);
//	extern int linha_atual, coluna_atual;
	Symbol *symbol = newSymbol(name, NULL, table->current_scope, linha_atual, coluna_atual);
	symbol->scope = table->current_scope;
	table->items[table->last] = symbol;
	table->last++;

	if (DBG) {
		int last = table->last - 1;
		printf("\n\n");
		printf("TABLE: symbol %s (%d, %d-%d) installed.[%d]\n", table->items[last]->name, table->items[last]->line, table->items[last]->first_column, table->items[last]->last_column, last);
		printf("  current scope: %d\n", table->current_scope);
		printf("  symbol scope: %d\n", table->current_scope);
		printf("\n");
		printTable(table);
	}
	return table->last - 1;
}

/* Updates the symbol type in the table */
void updateType(SymbolTable *table, int var_index, char *type) {
	if (DBG)
		printf("\n\nTABLE: Updating type of %s (scope %d)...\n", table->items[var_index]->name, table->items[var_index]->scope);

	if (table->items[var_index]->type != NULL)
		erro("Tipo de variável já foi especificado!");
	else {
		table->items[var_index]->type = (char*) malloc(sizeof(char) * strlen(type) + 1);
		strcpy(table->items[var_index]->type, type);
	}

	if (DBG)
		printf("  type updated to '%s'.\n\n", table->items[var_index]->type);
}

/* Prints the symbol table */
void printTable(SymbolTable *table) {
    printf("%16s %16s %16s %16s %16s %16s %16s %16s\n\n", "NOME", "INDEX", "TYPE", "NUM_PARAMS", "SCOPE", "LINHA", "COLUNA I", "COLUNA F");
    int i;
    for (i = 0; i < table->last; i++) {
    	printf("%16s ", table->items[i]->name);
    	printf("%16d ", i);
    	printf("%16s ", table->items[i]->type);
    	printf("%16d ", table->items[i]->num_params);
    	printf("%16d ", table->items[i]->scope);
    	printf("%16d ", table->items[i]->line);
    	printf("%16d ", table->items[i]->first_column);
    	printf("%16d\n", table->items[i]->last_column);
    }
}

