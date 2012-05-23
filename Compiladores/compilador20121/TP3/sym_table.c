#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char boolean;
#define True  1
#define False 0

typedef struct Token {
    char *token;
    char *lexema;
    int linha;
    int coluna;
} Token;

struct Cell {
  Token *token;
  struct Cell *next;
};

typedef struct SymbolTable {
  struct Cell *first, *last;
  boolean initialized;
} SymbolTable;

#define DEFAULT_TABLE {NULL, NULL, False};


/* Creates a new empty table */
//SymbolTable *newTable() {
//	SymbolTable *table = (SymbolTable*) malloc(sizeof(SymbolTable));
//	table->first = (struct Cell*) malloc(sizeof(struct Cell));
//	table->last = table->first;
//	table->first->token = NULL;
//	table->first->next = NULL;
//	return table;
//}

/* Initializes a symbol table */
void initTable(SymbolTable *table) {
	table->first = (struct Cell*) malloc(sizeof(struct Cell));
	table->last = table->first;
	table->first->token = NULL;
	table->first->next = NULL;
	table->initialized = True;
}

/* Creates a new token */
Token *newToken(char *tok, char *lexema, int linha, int coluna) {
	Token *token = (Token*) malloc(sizeof(Token));
	token->token = (char*) malloc(sizeof(char) * strlen(tok) + 1);
	strcpy(token->token, tok);
	token->lexema = (char*) malloc(sizeof(char) * strlen(lexema) + 1);
	strcpy(token->lexema, lexema);
	token->linha = linha;
	token->coluna = coluna;
	return token;
}

/* Adds a token to the symbol table */
void addToken(SymbolTable *table, Token *token) {
	table->last->next = (struct Cell*) malloc(sizeof(struct Cell));
	table->last = table->last->next;
	table->last->token = token;
	table->last->next = NULL;
	if (table->first == table->last)
		printf("Acabou de inserir e lista está vazia!\n");
	return;
}

/* Removes a token from the symbol table */
void Retira(struct Cell *p, SymbolTable *table) {
/*  ---   Obs.: o item a ser retirado e  o seguinte ao apontado por  p --- */
	struct Cell *q;
	if (table->first == table->last || p == NULL || p->next == NULL) {
		if (table->first == table->last)
			printf("Erro! Lista vazia!\n");
		else if (p == NULL)
			printf("Erro! Pointer é NULL!\n");
		else if (p->next == NULL)
			printf("Erro! Item a ser removido é NULL!\n");
		return;
	}
	q = p->next;
	p->next = q->next;
	if (p->next == NULL) table->last = p;
	free(q->token->lexema);
	free(q->token->token);
	free(q->token);
	free(q);
}

void printTable(SymbolTable *table) {
    printf("%16s %16s %16s %16s\n\n", "TOKEN", "LEXEMA", "LINHA", "COLUNA");
    struct Cell *aux = table->first->next;
    while (aux != NULL) {
        printf("%16s %16s %16d %16d\n", aux->token->token, aux->token->lexema, aux->token->linha, aux->token->coluna);
    	aux = aux->next;
    }
    //printf("total_tokens = %d\n", total_tokens);
}




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
