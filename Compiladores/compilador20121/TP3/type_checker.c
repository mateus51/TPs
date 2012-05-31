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


/* Numerical Operators */
void checkMod(char *op1, char *op2) {
	if (strcmp("integer", op1) || strcmp("integer", op2)) {
		printf("Warning: 'mod' operator requires integer operands.\n");

		if (EXIT_ON_ERROR)
			exit(EXIT_FAILURE);
	}
}

void checkDiv(char *op1, char *op2) {
	if (strcmp("integer", op1) || strcmp("integer", op2)) {
		printf("Warning: 'div' operator requires integer operands.\n");

		if (EXIT_ON_ERROR)
			exit(EXIT_FAILURE);
	}
}

void checkAnd(char *op1, char *op2) {
	if (strcmp("boolean", op1) || strcmp("boolean", op2)) {
		printf("Warning: 'and' operator requires boolean operands.\n");

		if (EXIT_ON_ERROR)
			exit(EXIT_FAILURE);
	}
}




/* Built-in functions */
char* checkBuiltInFunctionCall(enum BuiltInFunction function, char *arg_type) {
	switch (function) {

	case fsin:
		if (!checkNumericalArg(arg_type)) {
			printf("Warning: 'sin' function requires an integer or real argument.\n");
			if (EXIT_ON_ERROR)
				exit(EXIT_FAILURE);
		}
		return "real";

	case fcos:
		if (!checkNumericalArg(arg_type)) {
			printf("Warning: 'cos' function requires an integer or real argument.\n");
			if (EXIT_ON_ERROR)
				exit(EXIT_FAILURE);
		}
		return "real";

	case flog:
		if (!checkNumericalArg(arg_type)) {
			printf("Warning: 'log' function requires an integer or real argument.\n");
			if (EXIT_ON_ERROR)
				exit(EXIT_FAILURE);
		}
		return "real";

	case ford:
		if (strcmp("char", arg_type)) {
			printf("Warning: 'ord' function requires a char argument.\n");
			if (EXIT_ON_ERROR)
				exit(EXIT_FAILURE);
		}
		return "integer";

	case fabs:
		if (!checkNumericalArg(arg_type)) {
			printf("Warning: 'abs' function requires an integer or real argument.\n");
			if (EXIT_ON_ERROR)
				exit(EXIT_FAILURE);
		}
		return arg_type;

	case fsqrt:
		if (!checkNumericalArg(arg_type)) {
			printf("Warning: 'sqrt' function requires an integer or real argument.\n");
			if (EXIT_ON_ERROR)
				exit(EXIT_FAILURE);
		}
		return "real";

	case fexp:
		if (!checkNumericalArg(arg_type)) {
			printf("Warning: 'exp' function requires an integer or real argument.\n");
			if (EXIT_ON_ERROR)
				exit(EXIT_FAILURE);
		}
		return "real";

	case feofile:
		if (strcmp(arg_type, "integer")) {
			printf("Warning: 'eofile' function requires an integer argument.\n");
			if (EXIT_ON_ERROR)
				exit(EXIT_FAILURE);
		}
		return "boolean";

	case feoln:
		if (strcmp(arg_type, "integer")) {
			printf("Warning: 'eoln' function requires an integer argument.\n");
			if (EXIT_ON_ERROR)
				exit(EXIT_FAILURE);
		}
		return "boolean";

	default:
		printf("Default case!\n");
		return NULL;
	}
}

boolean checkNumericalArg(char *arg) {
	if (strcmp("integer", arg) && strcmp("real", arg))
		return False;

	return True;
}

/*

char* checkSIN(char *arg) {

}

char* checkCOS(char *arg) {

}

char* checkLOG(char *arg) {

}

char* checkORD(char *arg) {

}

char* checkABS(char *arg) {

}

char* checkSQRT(char *arg) {

}

char* checkEXP(char *arg) {

}

char* checkEOFILE(char *arg) {

}

char* checkEOLN(char *arg) {

}

 */
