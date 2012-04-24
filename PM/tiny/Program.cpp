#include "Program.h"

vector<Proc*> Program::lista_procs;

Program::Program(const char* string) {
	filename = string;
	global_context = new Context;
	Parse();
}

Program::~Program() {
/*
	unsigned int i;
	for (i = 0; i < lista_comandos.size(); i++) {
		//cout << "Deleting lista_comandos[" << i << "]" << endl;
		delete lista_comandos[i];
	}
*/
	//lista_comandos.erase(lista_comandos.begin(), lista_comandos.end());

	lista_procs.clear();

	delete global_context;
}

void Program::Run() {

	unsigned int i;
/*
	cout << "printing lista_procs:" << endl;
	for (i = 0; i < Program::lista_procs.size(); i++) {
		Program::lista_procs[i]->Print();
		cout << endl;
	}
	cout << "executing..." << endl;
*/

	for (i = 0; i < lista_procs.size(); i++) {
		if (lista_procs[i]->name.compare("main") == 0) {
			lista_procs[i]->Execute(global_context);
			return;
		}
	}
	throw MainProcNotFound();
}

void Program::Parse() {

	//cout << "Parsing progam" << endl;

	ifstream file(filename.c_str());

	vector<string> commands;
	string line;
	size_t pos;

	if (file.is_open()) {
		while (file.good()) {

			getline(file, line);
			StringUtils::RemoveSpaces(line);

			// Só processa a linha se ela não estiver em branco
			if (line.length() > 0) {

				// Declaração de variáveis globais
				pos = line.find("global");
				if (pos != string::npos) {
					//cout << "  -variaveis globais: '" << line << "'" << endl;
					global_context->CreateVars(line.substr(pos + 7));
					continue;
				}

				// Fim do programa
				if (line.find("endp") != string::npos) {
					file.close();
					return;
				}

				Proc *proc = new Proc(line, file);
				Program::lista_procs.push_back(proc);

			}
		}
		file.close();
	}
	else {
		cout << "Could not open file '" << filename << "'" << endl;
	}
}
