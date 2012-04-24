#include "For.h"

For::For(string line, ifstream& file) {

	//Pega a variável
	var = line[4];

	//Pega a primeira expressão da string
	size_t exp_start = line.find(":=") + 3;
	size_t exp_end = line.find("to") - 1;
	start_exp = new Expression(line.substr(exp_start, exp_end - exp_start));

	//Pega a segunda expressão da string
	exp_start = line.find("to") + 3;
	exp_end = line.find("do") - 1;
	end_exp = new Expression(line.substr(exp_start, exp_end - exp_start));

	//Lê os comandos do arquivo
	unsigned int i;
	vector<string> commands;
	string str;
	getline(file, str);
	while (str.compare("endfor") != 0) {
		//cout << "  For: '" << str << "'" << endl;
		commands = StringUtils::TokenizeLine(str, ';');
		for (i = 0; i < commands.size(); i++) {
			Command* command = ParseLine(commands[i], file);
			if (command != NULL) {
				lista_comandos.push_back(command);
			}
		}
		commands.clear();
		getline(file, str);
		StringUtils::RemoveSpaces(str);
	}
}

For::~For() {
	delete start_exp;
	delete end_exp;
	lista_comandos.clear();
}

void For::Interpret(Context *global_context, Context *local_context) {
	double start, end, value;
	unsigned int i;

	value = start_exp->Evaluate(global_context, local_context);
	Context::SetVariable(var, value, local_context, global_context);

	start = value;
	end = end_exp->Evaluate(global_context, local_context);

	if (start > end) {
		while (Context::GetVariable(var, global_context, local_context) >= end_exp->Evaluate(global_context, local_context)) {
			for (i = 0; i < lista_comandos.size(); i++)
				lista_comandos[i]->Interpret(global_context, local_context);
			value = Context::GetVariable(var, global_context, local_context) - 1;
			Context::SetVariable(var, value, global_context, local_context);
		}
	}
	else {
		while (Context::GetVariable(var, global_context, local_context) <= end_exp->Evaluate(global_context, local_context)) {
			for (i = 0; i < lista_comandos.size(); i++)
				lista_comandos[i]->Interpret(global_context, local_context);
			value = Context::GetVariable(var, global_context, local_context) + 1;
			Context::SetVariable(var, value, global_context, local_context);
		}
	}
}
