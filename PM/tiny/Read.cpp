#include "Read.h"

Read::Read(string line) {
	size_t pos = line.find_first_of("(") + 1;
	var_name = line.at(pos);
}

void Read::Interpret(Context *global_context, Context *local_context) {
	double value;
	cin >> value;

	Context::SetVariable(var_name, value, global_context, local_context);
}
