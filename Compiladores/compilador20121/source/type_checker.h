#include "sym_table.h"

#define EXIT_ON_ERROR False

enum BuiltInFunction {
	fsin, fcos, flog, ford, fabs, fsqrt, fexp, feofile, feoln
};


void checkAssign(SymbolTable*, int, char*);

void checkIf(char*);

void checkRepeat(char*);

void checkExpType(SymbolTable*, char*, char*);

char* checkFunctionCall(SymbolTable*, int);

void checkMod(char*, char*);

void checkDiv(char*, char*);

void checkAnd(char*, char*);

char* checkNOT(char*);

char* checkRELOP(char*, char*);

char* checkBuiltInFunctionCall(enum BuiltInFunction function, char *arg_type);
