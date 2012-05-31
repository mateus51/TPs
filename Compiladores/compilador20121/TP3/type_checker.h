#include "sym_table.h"

#define EXIT_ON_ERROR False

enum BuiltInFunction {
	fsin, fcos, flog, ford, fabs, fsqrt, fexp, feofile, feoln
};


void checkAtribType(SymbolTable*, int, char*);

void checkExpType(SymbolTable*, char*, char*);

void checkFunctionCall(SymbolTable*, int);

void checkMod(char*, char*);

void checkDiv(char*, char*);

void checkAnd(char*, char*);

char* checkBuiltInFunctionCall(enum BuiltInFunction, char*);

boolean checkNumericalArg(char*);
