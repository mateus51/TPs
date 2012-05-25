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
	boolean initialized;
} SymbolTable;


void erro(char *message) {
	printf("Erro! - %s\n", message);
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
	table->initialized = True;
}

/* Creates a new symbol */
Symbol *newSymbol(char *name, char *type, int line, int column) {
	printf("\n\nTABLE: %s(%d, %d)\n", name, line, column);
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
	return symbol;
}



void openScope(SymbolTable *table) {
	printf("\n\n\n\nvoid openScope(SymbolTable *table)\n\n");

	table->current_scope++;
	if (table->current_scope >= NUM_SCOPES)
		erro("Não é possível abrir um novo nível.\n");
	else
		table->scopes[table->current_scope] = table->last;
}


void closeScope(SymbolTable *table) {
	table->last = table->scopes[table->current_scope];
	table->current_scope--;
}

int getSymbol(SymbolTable *table, char *name) {
	int i;
	for (i = table->last-1; i >= 0; i--) {
		if (!strcmp(name, table->items[i]->name))
			return i;

	}
	erro("Símbolo não encontrado!");
}

void checkTableCapacity(SymbolTable *table) {
	if (table->last == table->capacity) {
		table->capacity = table->capacity * TABLE_GROWTH_FACTOR;
		table->items = (Symbol**) realloc(table->items, sizeof(Symbol*) * table->capacity);
		if (table->items == NULL)
			erro("Falha ao alocar espaço para a tabela de símbolos!\n");
	}
}

void installId(SymbolTable *table, char *name, int line, int column) {
	int i;
	for (i = table->last-1; i >= 0; i--)
		if (!strcmp(table->items[i]->name, name))
			return;

	checkTableCapacity(table);
	Symbol *symbol = newSymbol(name, NULL, line, column);
	symbol->scope = table->current_scope;
	table->items[table->last] = symbol;
	printf("\n\nINSTALL: %s(%d, %d)\n", table->items[table->last]->name, table->items[table->last]->line, table->items[table->last]->column);
	table->last++;
}

/* Prints the symbol table */
void printTable(SymbolTable *table) {
    printf("%16s %16s %16s %16s %16s\n\n", "NOME", "TYPE", "SCOPE", "LINHA", "COLUNA");
    int i;
    for (i = 0; i < table->last; i++)
    	printf("%16s %16s %16d %16d %16d\n", table->items[i]->name, table->items[i]->type, table->items[i]->scope, table->items[i]->line, table->items[i]->column);

//    struct Cell *aux = table->first->next;
//    while (aux != NULL) {
//        printf("%16s %16s %16d %16d\n", aux->token->token, aux->token->lexema, aux->token->linha, aux->token->coluna);
//    	aux = aux->next;
//    }
    //printf("total_tokens = %d\n", total_tokens);
}

//void main(void) {
//	return;
//}



//
//
//
//
//struct Cell {
//	Symbol *sym;
//	struct Cell *next;
//};
//
//typedef struct SymbolList {
//  struct Cell *first, *last;
//  boolean initialized;
//} SymbolList;
//
//#define MAX_LEVELS 20
//
////typedef struct SymbolTable {
////	SymbolList levels[MAX_LEVELS];
////}SymbolTable;
//
///* Initializes the symbol table */
//void initTable(SymbolTable *table) {
//	int i;
//	for (int i = 0; i < MAX_LEVELS; i++) {
//		table->levels[i] = (SymbolList*) malloc(sizeof(SymbolList));
//		table->levels[i]->first = NULL;
//		table->levels[i]->last = NULL;
//		table->levels[i]->initialized = False;
//	}
//}
//
///* Initializes the symbol list to the default values */
//void initList(SymbolList *list) {
//	list->first = (struct Cell*) malloc(sizeof(struct Cell));
//	list->last = list->first;
//	list->first->sym = NULL;
//	list->first->next = NULL;
//	list->initialized = True;
//}
//
///* Creates a new symbol */
//Symbol *newSymbol(char *name, char *type, int line, int column) {
//	Symbol *symbol = (Symbol*) malloc(sizeof(Symbol));
//	symbol->name = (char*) malloc(sizeof(char) * strlen(name) + 1);
//	strcpy(symbol->name, name);
//	if (symbol->type != NULL) {
//		symbol->type = (char*) malloc(sizeof(char) * strlen(type) + 1);
//		strcpy(symbol->type, type);
//	}
//	else
//		symbol->type = NULL;
//
//	symbol->line = line;
//	symbol->column = column;
//	return symbol;
//}
//
///* Get the corresponding symbol fro the symbol table.
// * Returns NULL if the symbol isn't in the table. */
//Symbol *getSymbol(SymbolTable *table, char *name) {
//	int i;
//	struct Cell *aux;
//	for (int i = MAX_LEVELS-1; i >= 0; i++) {
//		// Só pesquisa no nível se ele possuir algum símbolo
//		if (table->levels[i]->first != NULL && !isListEmpty(table->levels[i])) {
//			aux = table->levels[i]->first->next;
//			while (aux != NULL) {
//				if (!strcmp(aux->sym->name, name))
//					return aux->sym;
//				aux = aux->next;
//			}
//		}
//	}
//	return NULL;
//}
//
///* Adds a token to the symbol table. */
//void addSymbol(SymbolTable *table, Symbol *symbol, int level) {
//	Symbol *found_symbol = getSymbol(table, symbol->name);
//	if (found_symbol == NULL) {
//		table->last->next = (struct Cell*) malloc(sizeof(struct Cell));
//		table->last = table->last->next;
//		table->last->sym = symbol;
//		table->last->next = NULL;
//	}
//	else {
//		printf("Symbol '%s' found in table!\n", found_symbol->name);
//	}
//	return;
//}
//
//
///* Removes a token from the symbol table */
//void Retira(struct Cell *p, SymbolTable *table) {
///*  ---   Obs.: o item a ser retirado e  o seguinte ao apontado por  p --- */
//	struct Cell *q;
//	if (table->first == table->last || p == NULL || p->next == NULL) {
//		if (table->first == table->last)
//			printf("Erro! Lista vazia!\n");
//		else if (p == NULL)
//			printf("Erro! Pointer é NULL!\n");
//		else if (p->next == NULL)
//			printf("Erro! Item a ser removido é NULL!\n");
//		return;
//	}
//	q = p->next;
//	p->next = q->next;
//	if (p->next == NULL) table->last = p;
//	free(q->token->lexema);
//	free(q->token->token);
//	free(q->token);
//	free(q);
//}
//
//boolean isListEmpty(SymbolList *list) {
//	return (boolean) list->first == list->last;
//}
//
///* Prints the symbol table */
//void printTable(SymbolTable *table) {
//    printf("%16s %16s %16s %16s\n\n", "TOKEN", "LEXEMA", "LINHA", "COLUNA");
//    struct Cell *aux = table->first->next;
//    while (aux != NULL) {
//        printf("%16s %16s %16d %16d\n", aux->token->token, aux->token->lexema, aux->token->linha, aux->token->coluna);
//    	aux = aux->next;
//    }
//    //printf("total_tokens = %d\n", total_tokens);
//}




//int main() {
//	SymbolTable *table = newTable();
//	Token *token = newToken("COMMA", ",", 3, 45);
//
//	addToken(table, token);
//
//	struct Cell *aux = table->first->next;
//	while (aux != NULL) {
//		printf("token->token = %s\ntoken->lex = %s\n", token->token, token->lexema);
//		aux = aux->next;
//	}
//	Retira(table->first, table);
//	free(table->first);
//	free(table);
//
//	return 0;
//}
