#include "While.h"

While::While(string line, ifstream& file) {
	//Pega a expressão da string
	size_t exp_start = line.find("while") + 6;
	size_t exp_end = line.find("do") - 1;
	exp = new Expression(line.substr(exp_start, exp_end - exp_start));

	//Lê os comandos do arquivo
	unsigned int i;
	vector<string> commands;
	string str;
	getline(file, str);
	StringUtils::RemoveSpaces(str);
	while (str.compare("endw") != 0) {
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

While::~While() {
	delete exp;
	lista_comandos.clear();
}

void While::Interpret(Context *global_context, Context *local_context) {
	unsigned int i;
	while (exp->Evaluate(global_context, local_context)) {
		for (i = 0; i < lista_comandos.size(); i++)
			lista_comandos[i]->Interpret(global_context, local_context);
	}
}
