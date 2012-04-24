#include "simbolos.h"


TabelaDeSimbolos *NewTabelaDeSimbolos() {
	TabelaDeSimbolos *tabela = (TabelaDeSimbolos*) malloc(sizeof(TabelaDeSimbolos));
	tabela->ILC = NULL;
	tabela->simbolos = NULL;
	tabela->total_simbolos = 0;
	tabela->total_linhas = 0;
	return tabela;
}

void AdicionaSimbolo(TabelaDeSimbolos *tabela, char *simbolo, int ILC) {

	//printf("Inserindo %s -> %d\n", simbolo, ILC);

	tabela->total_simbolos++;

	tabela->ILC = (int*) realloc(tabela->ILC, sizeof(int) * tabela->total_simbolos);

	tabela->simbolos = (char**) realloc(tabela->simbolos, sizeof(char*) * tabela->total_simbolos);
	tabela->simbolos[tabela->total_simbolos - 1] = (char*) calloc(strlen(simbolo) + 1, sizeof(char));

	tabela->ILC[tabela->total_simbolos - 1] = ILC;
	strcpy(tabela->simbolos[tabela->total_simbolos - 1], simbolo);
}

void ImprimeTabela(TabelaDeSimbolos *tabela) {
	//printf("imprimindo...\n");
	int i;
	for (i = 0; i < tabela->total_simbolos; i++) {
		printf(" %s %5d\n", tabela->simbolos[i], tabela->ILC[i]);
	}
}

void FreeTabela(TabelaDeSimbolos *tabela) {
	int i;
	for (i = 0; i < tabela->total_simbolos; i++)
		free(tabela->simbolos[i]);

	free(tabela->simbolos);
	free(tabela->ILC);
	free(tabela);
}
