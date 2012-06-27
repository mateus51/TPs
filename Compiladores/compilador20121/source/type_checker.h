#ifndef __TYPE_CHECKER_H__
#define __TYPE_CHECKER_H__

#include "sym_table.h"

#define EXIT_ON_ERROR False

enum BuiltInFunction {
	fsin, fcos, flog, ford, fabs, fsqrt, fexp, feofile, feoln, fchr
};


int getTypeWidth(Type type);

void checkAssign(SymbolTable*, int, Type, int, int, int, int);

void checkIf(Type, int, int, int, int);

void checkRepeat(Type, int, int, int, int);

void checkExpType(SymbolTable*, Type, Type, int, int, int, int);

Type checkFunctionCall(SymbolTable*, int, int, int, int, int);

void checkMod(Type, Type, int, int, int, int);

void checkDiv(Type, Type, int, int, int, int);

void checkAnd(Type, Type, int, int, int, int);

Type checkNOT(Type, int, int, int, int);

Type checkRELOP(Type, Type);

Type checkBuiltInFunctionCall(enum BuiltInFunction, Type, int, int, int, int);

#endif
