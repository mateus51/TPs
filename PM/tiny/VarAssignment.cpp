#include "VarAssignment.h"

VarAssignment::VarAssignment(string line) {
	size_t pos = line.find(":=");
	name = line[0];
	exp = new Expression(line.substr(pos + 2));
}

VarAssignment::~VarAssignment() {
	delete exp;
}

void VarAssignment::Interpret(Context *global_context, Context *local_context) {
	double value = exp->Evaluate(global_context, local_context);
	Context::SetVariable(name, value, global_context, local_context);
}
