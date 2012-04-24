#include "WriteVar.h"

WriteVar::WriteVar(string line) {
	size_t pos = line.find_first_of("(") + 1;
	var_name = line.at(pos);
}

void WriteVar::Interpret(Context *global_context, Context *local_context) {
	cout << Context::GetVariable(var_name, global_context, local_context);
}
