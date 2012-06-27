#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "type_checker.h"

int getTypeWidth(Type type) {
	switch (type) {
	case real:
		return 8;
	case integer:
		return 4;
	case character:
		return 1;
	case boolean:
		return 1;
	default:
		return 0;
	}
}

// private functions
char checkNumericalArg(Type arg_type) {
	switch (arg_type) {
	case integer:
		return True;
	case real:
		return True;
	default:
		return False;
	}
}


/*
 * Statements
 */
void checkAssign(SymbolTable *table, int index, Type type, int fline, int fcolumn, int lline, int lcolumn) {
	if (DBG)
		printf("\n\nchecking type of var %s (%s)\n\n", table->items[index]->name, typeStr(type));


	if (table->items[index]->type != type) {
		//extern int linha_atual;
		printf("Warning (%d,%d-%d,%d): assignment type mismatch! -  %s <- %s\n", fline, fcolumn, lline, lcolumn, typeStr(table->items[index]->type), typeStr(type));
		if (EXIT_ON_ERROR)
			exit(EXIT_FAILURE);
	}
}

void checkIf(Type cond_type, int fline, int fcolumn, int lline, int lcolumn) {
	if (cond_type != boolean) {
		//extern int linha_atual;
		printf("Warning (%d,%d-%d,%d): 'if' statement requires a boolean condition (condition is '%s')\n", fline, fcolumn, lline, lcolumn, typeStr(cond_type));
		if (EXIT_ON_ERROR)
			exit(EXIT_FAILURE);
	}
}

void checkRepeat(Type expr_type, int fline, int fcolumn, int lline, int lcolumn) {
	if (expr_type != boolean) {
		//extern int linha_atual;
		printf("Warning (%d,%d-%d,%d): 'repeat' statement requires an expression that evaluates to a boolean (expression is '%s')\n", fline, fcolumn, lline, lcolumn, typeStr(expr_type));
		if (EXIT_ON_ERROR)
			exit(EXIT_FAILURE);
	}
}



void checkExpType(SymbolTable *table, Type type1, Type type2, int fline, int fcolumn, int lline, int lcolumn) {
	if (DBG)
		printf("\n\nchecking type of exp (%s x %s)\n", typeStr(type1), typeStr(type2));

	if (type1 != type2) {
		//extern int linha_atual;
		printf("Warning (%d,%d-%d,%d): expression type mismatch! -  %s and %s are in the same expression.\n", fline, fcolumn, lline, lcolumn, typeStr(type1), typeStr(type2));
		//printTable(table);
	}
}

Type checkFunctionCall(SymbolTable *table, int index, int fline, int fcolumn, int lline, int lcolumn) {
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
void checkMod(Type op1, Type op2, int fline, int fcolumn, int lline, int lcolumn) {
	if (op1 != integer || op2 != integer) {
		//extern int linha_atual;
		printf("Warning (%d,%d-%d,%d): 'mod' operator requires integer operands.\n", fline, fcolumn, lline, lcolumn);

		if (EXIT_ON_ERROR)
			exit(EXIT_FAILURE);
	}
}

void checkDiv(Type op1, Type op2, int fline, int fcolumn, int lline, int lcolumn) {
	if (op1 != integer || op2 != integer) {
		//extern int linha_atual;
		printf("Warning (%d,%d-%d,%d): 'div' operator requires integer operands.\n", fline, fcolumn, lline, lcolumn);

		if (EXIT_ON_ERROR)
			exit(EXIT_FAILURE);
	}
}

void checkAnd(Type op1, Type op2, int fline, int fcolumn, int lline, int lcolumn) {
	if (op1 != boolean || op2 != boolean) {
		//extern int linha_atual;
		printf("Warning (%d,%d-%d,%d): 'and' operator requires boolean operands.\n", fline, fcolumn, lline, lcolumn);

		if (EXIT_ON_ERROR)
			exit(EXIT_FAILURE);
	}
}


/*
 * Boolean operators
 */
Type checkNOT(Type op, int fline, int fcolumn, int lline, int lcolumn) {
	if (op != boolean) {
		//extern int linha_atual;
		printf("Warning (%d,%d-%d,%d): 'NOT' operator requires a boolean operand.\n", fline, fcolumn, lline, lcolumn);

		if (EXIT_ON_ERROR)
			exit(EXIT_FAILURE);
	}
	return op;
}

// FIXME: RELOPs não necessariamente são boolean! 1 > 2 é válido! Ver documentaçao pascal.
Type checkRELOP(Type op1, Type op2) {
	// RELOPs aceitam qualquer tipo de operandos.

	return boolean;
}




/* Built-in functions */
Type checkBuiltInFunctionCall(enum BuiltInFunction function, Type arg_type, int fline, int fcolumn, int lline, int lcolumn) {
	switch (function) {

	case fsin:
		if (!checkNumericalArg(arg_type)) {
			//extern int linha_atual;
			printf("Warning (%d,%d-%d,%d): 'sin' function requires an integer or real argument.\n", fline, fcolumn, lline, lcolumn);
			if (EXIT_ON_ERROR)
				exit(EXIT_FAILURE);
		}
		return real;

	case fcos:
		if (!checkNumericalArg(arg_type)) {
			//extern int linha_atual;
			printf("Warning (%d,%d-%d,%d): 'cos' function requires an integer or real argument.\n", fline, fcolumn, lline, lcolumn);
			if (EXIT_ON_ERROR)
				exit(EXIT_FAILURE);
		}
		return real;

	case flog:
		if (!checkNumericalArg(arg_type)) {
			//extern int linha_atual;
			printf("Warning (%d,%d-%d,%d): 'log' function requires an integer or real argument.\n", fline, fcolumn, lline, lcolumn);
			if (EXIT_ON_ERROR)
				exit(EXIT_FAILURE);
		}
		return real;

	case ford:
		if (arg_type != character) {
			//extern int linha_atual;
			printf("Warning (%d,%d-%d,%d): 'ord' function requires a char argument.\n", fline, fcolumn, lline, lcolumn);
			if (EXIT_ON_ERROR)
				exit(EXIT_FAILURE);
		}
		return integer;

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
		return real;

	case fexp:
		if (!checkNumericalArg(arg_type)) {
			//extern int linha_atual;
			printf("Warning (%d,%d-%d,%d): 'exp' function requires an integer or real argument.\n", fline, fcolumn, lline, lcolumn);
			if (EXIT_ON_ERROR)
				exit(EXIT_FAILURE);
		}
		return real;

	case feofile:
		if (arg_type != integer) {
			//extern int linha_atual;
			printf("Warning (%d,%d-%d,%d): 'eofile' function requires an integer argument.\n", fline, fcolumn, lline, lcolumn);
			if (EXIT_ON_ERROR)
				exit(EXIT_FAILURE);
		}
		return boolean;

	case feoln:
		if (arg_type != integer) {
			//extern int linha_atual;
			printf("Warning (%d,%d-%d,%d): 'eoln' function requires an integer argument.\n", fline, fcolumn, lline, lcolumn);
			if (EXIT_ON_ERROR)
				exit(EXIT_FAILURE);
		}
		return boolean;

	case fchr:
		if (arg_type != integer) {
			//extern int linha_atual;
			printf("Warning (%d,%d-%d,%d): 'chr' function requires an integer argument.\n", fline, fcolumn, lline, lcolumn);
			if (EXIT_ON_ERROR)
				exit(EXIT_FAILURE);
		}
		return character;
		break;

	default:
		printf("Default case!\n");
		return nulltype;
	}
}




