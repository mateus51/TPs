#include "IfThenElse.h"

IfThenElse::IfThenElse(string line, ifstream& file) {
	unsigned int i;
	vector<string> commands;
	string str;
	bool reading_then = true;
	//size_t ponto_e_virgula, prev_ponto_e_virgula;

	//Pega a expressão da string
	size_t exp_start = line.find("if") + 3;
	size_t exp_end = line.find("then") - 1;
	exp = new Expression(line.substr(exp_start, exp_end - exp_start));

	//Lê os comandos do arquivo
	getline(file, str);
	while (str.compare("endif") != 0) {
		if (str.compare("else") == 0) {
			reading_then = false;
			getline(file, str);
			continue;
		}

		commands = StringUtils::TokenizeLine(str, ';');
		for (i = 0; i < commands.size(); i++) {
			Command* command = ParseLine(commands[i], file);
			if (command != NULL) {
				if (reading_then) {
					then.push_back(command);
				}
				else {
					elce.push_back(command);
				}
			}
		}
		commands.clear();
/*
		ponto_e_virgula = prev_ponto_e_virgula = str.find(";");
		command_str = str.substr(0, ponto_e_virgula);
		//cout << "command_str = '" << command_str << "'" << endl;
		Command* command = Program::ParseLine(command_str, file);
		if (command != NULL) {
			if (reading_then) {
				//cout << "pushing to then" << endl;
				then.push_back(command);
			}
			else {
				//cout << "pushing to elce" << endl;
				elce.push_back(command);
			}
		}

		while ((ponto_e_virgula = str.find(";", ++ponto_e_virgula)) != string::npos) {
			command_str = str.substr(prev_ponto_e_virgula + 1, ponto_e_virgula - prev_ponto_e_virgula);
			//cout << "command_str = '" << command_str << "'" << endl;
			Command* command = Program::ParseLine(command_str, file);
			if (command != NULL) {
				if (reading_then) {
					//cout << "pushing to then" << endl;
					then.push_back(command);
				}
				else {
					//cout << "pushing to elce" << endl;
					elce.push_back(command);
				}
			}
			prev_ponto_e_virgula = ponto_e_virgula;
		}
*/
		getline(file, str);
		StringUtils::RemoveSpaces(str);
	}
	//cout << "IF END" << endl;
}

IfThenElse::~IfThenElse() {
	unsigned int i;
	for (i = 0; i < then.size(); i++)
		delete then[i];

	for (i = 0; i < elce.size(); i++)
		delete elce[i];

	delete exp;
}

void IfThenElse::Interpret(Context *global_context, Context *local_context) {
	//cout << " - Interpreting if "; exp->PrintExp();

	unsigned int i;
	if (exp->Evaluate(global_context, local_context)) {
		for (i = 0; i < then.size(); i++)
			then[i]->Interpret(global_context, local_context);
	}
	else {
		for (i = 0; i < elce.size(); i++)
			elce[i]->Interpret(global_context, local_context);
	}
}

