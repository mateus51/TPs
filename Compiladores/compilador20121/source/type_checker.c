#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void checkAssign(SymbolTable *table, int index, char *type, int fline, int fcolumn, int lline, int lcolumn) {
	if (DBG)
		printf("\n\nchecking type of var %s (%s)\n\n", table->items[index]->name, type);


	if (strcmp(table->items[index]->type, type)) {
		//extern int linha_atual;
		printf("Warning (%d,%d-%d,%d): assignment type mismatch! -  %s <- %s\n", fline, fcolumn, lline, lcolumn, table->items[index]->type, type);
		if (EXIT_ON_ERROR)
			exit(EXIT_FAILURE);
	}
}

void checkIf(char *cond, int fline, int fcolumn, int lline, int lcolumn) {
	if (strcmp(cond, "boolean")) {
		//extern int linha_atual;
		printf("Warning (%d,%d-%d,%d): 'if' statement requires a boolean condition (condition is '%s')\n", fline, fcolumn, lline, lcolumn, cond);
		if (EXIT_ON_ERROR)
			exit(EXIT_FAILURE);
	}
}

void checkRepeat(char *expr, int fline, int fcolumn, int lline, int lcolumn) {
	if (strcmp(expr, "boolean")) {
		//extern int linha_atual;
		printf("Warning (%d,%d-%d,%d): 'repeat' statement requires an expression that evaluates to a boolean (expression is '%s')\n", fline, fcolumn, lline, lcolumn, expr);
		if (EXIT_ON_ERROR)
			exit(EXIT_FAILURE);
	}
}



void checkExpType(SymbolTable *table, char *type1, char *type2, int fline, int fcolumn, int lline, int lcolumn) {
	if (DBG)
		printf("\n\nchecking type of exp (%s x %s)\n", type1, type2);

	if (strcmp(type1, type2)) {
		//extern int linha_atual;
		printf("Warning (%d,%d-%d,%d): expression type mismatch! -  %s and %s are in the same expression.\n", fline, fcolumn, lline, lcolumn, type1, type2);
		//printTable(table);
	}
}

char* checkFunctionCall(SymbolTable *table, int index, int fline, int fcolumn, int lline, int lcolumn) {
	if (DBG)
		printf("\n\nchecking function call: %s(%d params)\n", table->items[index]->name, table->items[index]->num_params);

	extern int function_call_params;
	if (table->items[index]->num_params != function_call_params) {
		//extern int linha_atual;
		printf("Warning (%d,%d-%d,%d): wrong number of parameters on function call: %s (have %d, supplied %d)\n", fline, fcolumn, lline, lcolumn, table->items[index]->name, table->items[index]->num_params, function_call_params);
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
void checkMod(char *op1, char *op2, int fline, int fcolumn, int lline, int lcolumn) {
	if (strcmp("integer", op1) || strcmp("integer", op2)) {
		//extern int linha_atual;
		printf("Warning (%d,%d-%d,%d): 'mod' operator requires integer operands.\n", fline, fcolumn, lline, lcolumn);

		if (EXIT_ON_ERROR)
			exit(EXIT_FAILURE);
	}
}

void checkDiv(char *op1, char *op2, int fline, int fcolumn, int lline, int lcolumn) {
	if (strcmp("integer", op1) || strcmp("integer", op2)) {
		//extern int linha_atual;
		printf("Warning (%d,%d-%d,%d): 'div' operator requires integer operands.\n", fline, fcolumn, lline, lcolumn);

		if (EXIT_ON_ERROR)
			exit(EXIT_FAILURE);
	}
}

void checkAnd(char *op1, char *op2, int fline, int fcolumn, int lline, int lcolumn) {
	if (strcmp("boolean", op1) || strcmp("boolean", op2)) {
		//extern int linha_atual;
		printf("Warning (%d,%d-%d,%d): 'and' operator requires boolean operands.\n", fline, fcolumn, lline, lcolumn);

		if (EXIT_ON_ERROR)
			exit(EXIT_FAILURE);
	}
}


/*
 * Boolean operators
 */
char* checkNOT(char *op, int fline, int fcolumn, int lline, int lcolumn) {
	if (strcmp("boolean", op)) {
		//extern int linha_atual;
		printf("Warning (%d,%d-%d,%d): 'NOT' operator requires a boolean operand.\n", fline, fcolumn, lline, lcolumn);

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
char* checkBuiltInFunctionCall(enum BuiltInFunction function, char *arg_type, int fline, int fcolumn, int lline, int lcolumn) {
	switch (function) {

	case fsin:
		if (!checkNumericalArg(arg_type)) {
			//extern int linha_atual;
			printf("Warning (%d,%d-%d,%d): 'sin' function requires an integer or real argument.\n", fline, fcolumn, lline, lcolumn);
			if (EXIT_ON_ERROR)
				exit(EXIT_FAILURE);
		}
		return "real";

	case fcos:
		if (!checkNumericalArg(arg_type)) {
			//extern int linha_atual;
			printf("Warning (%d,%d-%d,%d): 'cos' function requires an integer or real argument.\n", fline, fcolumn, lline, lcolumn);
			if (EXIT_ON_ERROR)
				exit(EXIT_FAILURE);
		}
		return "real";

	case flog:
		if (!checkNumericalArg(arg_type)) {
			//extern int linha_atual;
			printf("Warning (%d,%d-%d,%d): 'log' function requires an integer or real argument.\n", fline, fcolumn, lline, lcolumn);
			if (EXIT_ON_ERROR)
				exit(EXIT_FAILURE);
		}
		return "real";

	case ford:
		if (strcmp("char", arg_type)) {
			//extern int linha_atual;
			printf("Warning (%d,%d-%d,%d): 'ord' function requires a char argument.\n", fline, fcolumn, lline, lcolumn);
			if (EXIT_ON_ERROR)
				exit(EXIT_FAILURE);
		}
		return "integer";

	case fabs:
		if (!checkNumericalArg(arg_type)) {
			//extern int linha_atual;
			printf("Warning (%d,%d-%d,%d): 'abs' function requires an integer or real argument.\n", fline, fcolumn, lline, lcolumn);
			if (EXIT_ON_ERROR)
				exit(EXIT_FAILURE);
		}
		return arg_type;

	case fsqrt:
		if (!checkNumericalArg(arg_type)) {
			//extern int linha_atual;
			printf("Warning (%d,%d-%d,%d): 'sqrt' function requires an integer or real argument.\n", fline, fcolumn, lline, lcolumn);
			if (EXIT_ON_ERROR)
				exit(EXIT_FAILURE);
		}
		return "real";

	case fexp:
		if (!checkNumericalArg(arg_type)) {
			//extern int linha_atual;
			printf("Warning (%d,%d-%d,%d): 'exp' function requires an integer or real argument.\n", fline, fcolumn, lline, lcolumn);
			if (EXIT_ON_ERROR)
				exit(EXIT_FAILURE);
		}
		return "real";

	case feofile:
		if (strcmp(arg_type, "integer")) {
			//extern int linha_atual;
			printf("Warning (%d,%d-%d,%d): 'eofile' function requires an integer argument.\n", fline, fcolumn, lline, lcolumn);
			if (EXIT_ON_ERROR)
				exit(EXIT_FAILURE);
		}
		return "boolean";

	case feoln:
		if (strcmp(arg_type, "integer")) {
			//extern int linha_atual;
			printf("Warning (%d,%d-%d,%d): 'eoln' function requires an integer argument.\n", fline, fcolumn, lline, lcolumn);
			if (EXIT_ON_ERROR)
				exit(EXIT_FAILURE);
		}
		return "boolean";

	case fchr:
		if (strcmp("integer", arg_type)) {
			//extern int linha_atual;
			printf("Warning (%d,%d-%d,%d): 'chr' function requires an integer argument.\n", fline, fcolumn, lline, lcolumn);
			if (EXIT_ON_ERROR)
				exit(EXIT_FAILURE);
		}
		return "char";
		break;

	default:
		printf("Default case!\n");
		return NULL;
	}
}




