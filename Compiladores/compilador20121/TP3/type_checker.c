#include "type_checker.h"

void checkAtribType(SymbolTable *table, int index, char *type) {
	if (DBG)
		printf("\n\nchecking type of var %s (%s)\n", table->items[index]->name, type);

	if (strcmp(table->items[index]->type, type)) {
		printf("Warning: assignment type mismatch! -  %s := %s\n\n", table->items[index]->type, type);
		//printTable(table);
	}
}

void checkExpType(SymbolTable *table, char *type1, char *type2) {
	if (DBG)
		printf("\n\nchecking type of exp (%s x %s)\n", type1, type2);

	if (strcmp(type1, type2)) {
		printf("Warning: expression type mismatch! -  %s and %s are in the same expression.\n\n", type1, type2);
		//printTable(table);
	}
}

void checkFunctionCall(SymbolTable *table, int index) {
	if (DBG)
		printf("\n\nchecking function call: %s(%d params)\n", table->items[index]->name, table->items[index]->num_params);

	extern int function_call_params;
	if (table->items[index]->num_params != function_call_params) {
		printf("Function call error! Wrong number of parameters: %s (%d for %d)\n", table->items[index]->name, table->items[index]->num_params, function_call_params);
		printTable(table);
//		exit(EXIT_FAILURE);
	}
	function_call_params = 0;
}

