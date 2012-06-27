#ifndef __SEMANTIC_ANALYZER_H__
#define __SEMANTIC_ANALYZER_H__

#include "type_checker.h"
#include "sym_table.h"

typedef struct {
	Type type; // symbol type
	int width;

	int addr;   // symbol table addr;

	enum BuiltInFunction function;

	int intval;
	double realval;
	char charval;
} Attributes;

#endif
