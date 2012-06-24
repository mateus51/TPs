#include "sym_table.h"

#define EXIT_ON_ERROR False

enum BuiltInFunction {
	fsin, fcos, flog, ford, fabs, fsqrt, fexp, feofile, feoln, fchr
};


void checkAssign(SymbolTable*, int, char*, int, int, int, int);

void checkIf(char*, int, int, int, int);

void checkRepeat(char*, int, int, int, int);

void checkExpType(SymbolTable*, char*, char*, int, int, int, int);

char* checkFunctionCall(SymbolTable*, int, int, int, int, int);

void checkMod(char*, char*, int, int, int, int);

void checkDiv(char*, char*, int, int, int, int);

void checkAnd(char*, char*, int, int, int, int);

char* checkNOT(char*, int, int, int, int);

char* checkRELOP(char*, char*);

char* checkBuiltInFunctionCall(enum BuiltInFunction, char*, int, int, int, int);
