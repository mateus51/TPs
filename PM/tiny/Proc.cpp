#include "Proc.h"

Proc::Proc(string line, ifstream& file) {
	//cout << "\nnew Proc: '" << line << "'" << endl;
	size_t start, end;
	end = line.find_first_of('(') - 1;
	start = line.find("proc") + 5;
	string nam = line.substr(start, end - start + 1);
	StringUtils::RemoveSpaces(nam);
	name = nam;
	//cout << " name: " << name << endl;

	local_context = new Context;

	unsigned int i;
	string aux_str;
	start = line.find_first_of('(') + 1;
	end = line.find_first_of(')');
	aux_str = line.substr(start, end - start);
	if (!aux_str.empty()) {
		vector<string> aux = StringUtils::TokenizeLine(aux_str, ',');
		for (i = 0; i < aux.size(); i++) {
			params.push_back(aux[i].substr(0, 1));
		}
	}

	//cout << endl;


	vector<string> commands;
	string str;
//	while (str.compare("endproc") != 0) {
	while (true) {
		getline(file, str);
		//cout << " -proc ";
		StringUtils::RemoveSpaces(str);

		if (str.size() > 0) {

			// Declaração de variáveis locais
			start = str.find("local");
			if (start != string::npos) {
				//cout << " -variaveis locais!" << endl;
				local_vars = str.substr(start + 6);
				local_context->CreateVars(local_vars);
				continue;
			}

			// Fim do proc
			if (str.find("endproc") == 0) {
				return;
			}

			commands = StringUtils::TokenizeLine(str, ';');
			for (i = 0; i < commands.size(); i++) {
				Command* command = ParseLine(commands[i], file);
				if (command != NULL) {
					lista_comandos.push_back(command);
				}
			}
			commands.clear();
			//getline(file, str);
		}

	}
}

Proc::~Proc() {
	delete local_context;
	lista_comandos.clear();
	params.clear();
}

void Proc::Execute(Context *global_context) {
	//cout << "executing " << name << endl;
	unsigned int i;
/*
	for (i = 0; i < params.size(); i++) {
		local_context->CreateVariable(params[i].at(0), global_context->GetVariable(params[i].at(0)));
	}
	for (i = 0; i < global_context->vars.size(); i++) {
		local_context->CreateVariable(global_context->vars[i]->name, global_context->vars[i]->value);
	}
*/

	//cout << "will execute proc " << name << endl;
	//local_context->PrintVariables();

	for (i = 0; i < lista_comandos.size(); i++) {
		lista_comandos[i]->Interpret(global_context, local_context);
	}
/*
	for (i = 0; i < global_context->vars.size(); i++) {
		for (j = (int)params.size() - 1; j >= 0; j--) {
			if (global_context->vars[i]->name == local_context->vars[j]->name) {
				cout << "copying " << local_context->vars[j]->name << "to global context" << endl;
				global_context->SetVariable(local_context->vars[j]->name, local_context->vars[j]->value);
			}
		}
	}
*/
}

void Proc::Print() {
	cout << "'" << name << "' (" << params.size() << " params) ";
	unsigned int i;
	for (i = 0; i < params.size(); i++) {
		cout << "[" << params[i] << "] ";
	}
	cout << "\n" << endl;;
}
