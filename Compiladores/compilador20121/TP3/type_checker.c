#include "type_checker.h"

// private functions
boolean checkNumericalArg(char *arg) {
	if (strcmp("integer", arg) && strcmp("real", arg))
		return False;

	return True;
}


/*
 * Statements
 */
void checkAssign(SymbolTable *table, int index, char *type) {
	if (DBG)
		printf("\n\nchecking type of var %s (%s)\n\n", table->items[index]->name, type);


	if (strcmp(table->items[index]->type, type)) {
		extern int linha_atual;
		printf("Warning (line %d): assignment type mismatch! -  %s <- %s\n", linha_atual, table->items[index]->type, type);
		if (EXIT_ON_ERROR)
			exit(EXIT_FAILURE);
	}
}

void checkIf(char *cond) {
	if (strcmp(cond, "boolean")) {
		extern int linha_atual;
		printf("Warning (line %d): 'if' statement requires a boolean condition (condition is '%s')\n", linha_atual, cond);
		if (EXIT_ON_ERROR)
			exit(EXIT_FAILURE);
	}
}

void checkRepeat(char *expr) {
	if (strcmp(expr, "boolean")) {
		extern int linha_atual;
		printf("Warning (line %d): 'repeat' statement requires an expression that evaluates to a boolean (expression is '%s')\n", linha_atual, expr);
		if (EXIT_ON_ERROR)
			exit(EXIT_FAILURE);
	}
}



void checkExpType(SymbolTable *table, char *type1, char *type2) {
	if (DBG)
		printf("\n\nchecking type of exp (%s x %s)\n", type1, type2);

	if (strcmp(type1, type2)) {
		extern int linha_atual;
		printf("Warning (line %d): expression type mismatch! -  %s and %s are in the same expression.\n", linha_atual, type1, type2);
		//printTable(table);
	}
}

char* checkFunctionCall(SymbolTable *table, int index) {
	if (DBG)
		printf("\n\nchecking function call: %s(%d params)\n", table->items[index]->name, table->items[index]->num_params);

	extern int function_call_params;
	if (table->items[index]->num_params != function_call_params) {
		extern int linha_atual;
		printf("Warning (line %d): wrong number of parameters on function call: %s (%d for %d)\n", linha_atual, table->items[index]->name, table->items[index]->num_params, function_call_params);
//		printTable(table);
		if (EXIT_ON_ERROR)
			exit(EXIT_FAILURE);
	}
	function_call_params = 0;
	return lookupType(table, index);
}


/*
 * Numerical Operators
 */
void checkMod(char *op1, char *op2) {
	if (strcmp("integer", op1) || strcmp("integer", op2)) {
		extern int linha_atual;
		printf("Warning (line %d): 'mod' operator requires integer operands.\n", linha_atual);

		if (EXIT_ON_ERROR)
			exit(EXIT_FAILURE);
	}
}

void checkDiv(char *op1, char *op2) {
	if (strcmp("integer", op1) || strcmp("integer", op2)) {
		extern int linha_atual;
		printf("Warning (line %d): 'div' operator requires integer operands.\n", linha_atual);

		if (EXIT_ON_ERROR)
			exit(EXIT_FAILURE);
	}
}

void checkAnd(char *op1, char *op2) {
	if (strcmp("boolean", op1) || strcmp("boolean", op2)) {
		extern int linha_atual;
		printf("Warning (line %d): 'and' operator requires boolean operands.\n", linha_atual);

		if (EXIT_ON_ERROR)
			exit(EXIT_FAILURE);
	}
}


/*
 * Boolean operators
 */
char* checkNOT(char *op) {
	if (strcmp("boolean", op)) {
		extern int linha_atual;
		printf("Warning (line %d): 'NOT' operator requires a boolean operand.\n", linha_atual);

		if (EXIT_ON_ERROR)
			exit(EXIT_FAILURE);
	}
	return op;
}

// FIXME: RELOPs não necessariamente são boolean! 1 > 2 é válido! Ver documentaçao pascal.
char* checkRELOP(char *op1, char *op2) {
	// RELOPs aceitam qualquer tipo de operandos.

	return "boolean";
}




/* Built-in functions */
char* checkBuiltInFunctionCall(enum BuiltInFunction function, char *arg_type) {
	switch (function) {

	case fsin:
		if (!checkNumericalArg(arg_type)) {
			extern int linha_atual;
			printf("Warning (line %d): 'sin' function requires an integer or real argument.\n", linha_atual);
			if (EXIT_ON_ERROR)
				exit(EXIT_FAILURE);
		}
		return "real";

	case fcos:
		if (!checkNumericalArg(arg_type)) {
			extern int linha_atual;
			printf("Warning (line %d): 'cos' function requires an integer or real argument.\n", linha_atual);
			if (EXIT_ON_ERROR)
				exit(EXIT_FAILURE);
		}
		return "real";

	case flog:
		if (!checkNumericalArg(arg_type)) {
			extern int linha_atual;
			printf("Warning (line %d): 'log' function requires an integer or real argument.\n", linha_atual);
			if (EXIT_ON_ERROR)
				exit(EXIT_FAILURE);
		}
		return "real";

	case ford:
		if (strcmp("char", arg_type)) {
			extern int linha_atual;
			printf("Warning (line %d): 'ord' function requires a char argument.\n", linha_atual);
			if (EXIT_ON_ERROR)
				exit(EXIT_FAILURE);
		}
		return "integer";

	case fabs:
		if (!checkNumericalArg(arg_type)) {
			extern int linha_atual;
			printf("Warning (line %d): 'abs' function requires an integer or real argument.\n", linha_atual);
			if (EXIT_ON_ERROR)
				exit(EXIT_FAILURE);
		}
		return arg_type;

	case fsqrt:
		if (!checkNumericalArg(arg_type)) {
			extern int linha_atual;
			printf("Warning (line %d): 'sqrt' function requires an integer or real argument.\n", linha_atual);
			if (EXIT_ON_ERROR)
				exit(EXIT_FAILURE);
		}
		return "real";

	case fexp:
		if (!checkNumericalArg(arg_type)) {
			extern int linha_atual;
			printf("Warning (line %d): 'exp' function requires an integer or real argument.\n", linha_atual);
			if (EXIT_ON_ERROR)
				exit(EXIT_FAILURE);
		}
		return "real";

	case feofile:
		if (strcmp(arg_type, "integer")) {
			extern int linha_atual;
			printf("Warning (line %d): 'eofile' function requires an integer argument.\n", linha_atual);
			if (EXIT_ON_ERROR)
				exit(EXIT_FAILURE);
		}
		return "boolean";

	case feoln:
		if (strcmp(arg_type, "integer")) {
			extern int linha_atual;
			printf("Warning (line %d): 'eoln' function requires an integer argument.\n", linha_atual);
			if (EXIT_ON_ERROR)
				exit(EXIT_FAILURE);
		}
		return "boolean";

	default:
		printf("Default case!\n");
		return NULL;
	}
}




