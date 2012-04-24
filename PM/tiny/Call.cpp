#include "Call.h"

Call::Call(string line) {
	//cout << "new CALL -> '" << line << "'" << endl;
	size_t start, end;
	start = line.find("call") + 5;
	end = line.find_first_of("(");
	proc_name = line.substr(start, end - start);
	//StringUtils::RemoveSpaces(line);
	//line[line.size() - 1] = '\0';

	//cout << "  pegou proc_name: " << proc_name << endl;

	start = line.find_first_of("(") + 1;
	end = line.find_last_of(")");
	vector<string> aux = StringUtils::TokenizeLine(line.substr(start, end - start), ',');
	unsigned int i;
	for (i = 0; i < aux.size(); i++) {
		params.push_back(new Expression(aux[i]));
	}
	//this->Print();
}

Call::~Call() {
	params.clear();
}

void Call::Interpret(Context *global_context, Context *local_context) {

	//this->Print(global_context, local_context);

	unsigned int i;
	for (i = 0; i < Program::lista_procs.size(); i++) {
		if (Program::lista_procs[i]->name.compare(proc_name) == 0) {

			// Salva contexto em caso de chamada recursiva
			Context *context_bkp = Program::lista_procs[i]->local_context;
			Program::lista_procs[i]->local_context = new Context();

			// Cria variáveis locais do proc no novo contexto
			//cout << "criando variáveis locais: '" << Program::lista_procs[i]->local_vars << "'" << endl;
			Program::lista_procs[i]->local_context->CreateVars(Program::lista_procs[i]->local_vars);

			// Criando parâmetros no contexto local
			CopyParamsToLocalContext(Program::lista_procs[i], global_context, local_context);

			// Printing...
			//cout << "local context vars: " << endl;
			//Program::lista_procs[i]->local_context->PrintVars();

			// Executing...
			Program::lista_procs[i]->Execute(global_context);

			// Restaura o contexto antigo
			delete Program::lista_procs[i]->local_context;
			Program::lista_procs[i]->local_context = context_bkp;
			return;
		}
	}
	throw ProcNotFound(proc_name);
	//cout << "Proc not found!!!\n Need exeption here!!!" << endl;
}

void Call::CopyParamsToLocalContext(Proc *proc, Context *global_context, Context *local_context) {
	unsigned int i;
	double value;
	char name;

	//cout << "copying " << proc->params.size() << " params to local context" << endl;

	for (i = 0; i < proc->params.size(); i++) {
		name = proc->params[i].at(0);
		value = params[i]->Evaluate(global_context, local_context);
/*
		// Se o token da expressão é um número, empilha
		if (strspn(params[i].c_str(), "0123456789.") == params[i].length())
			value = atof(params[i].c_str());
		else
			value = Context::GetVariable(params[i].at(0), global_context, local_context);
*/
		proc->local_context->CreateVar(name, value);
	}
}

void Call::Print(Context *global_context, Context *local_context) {
	cout << "\n\nCALL '" << proc_name << "'" << endl;
	cout << "  ";
	unsigned int i;
	for (i = 0; i < params.size(); i++) {
		cout << params[i]->Evaluate(global_context, local_context) << " // ";
	}
	cout << endl;
}
