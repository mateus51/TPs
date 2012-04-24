#include "Context.h"

Context::~Context() {
	unsigned int i;
	for (i = 0; i < vars.size(); i++) {
		delete vars[i];
	}
	vars.clear();
}

double Context::GetVar(char name) {
	unsigned int i;
	for (i = 0; i < vars.size(); i++) {
		if (name == vars[i]->name)
			return vars[i]->value;
	}
	//CreateVariable(name, 0.0);
	throw VariableNotDefined();
}

void Context::SetVar(char name, double value) {
	unsigned int i;
	for (i = 0; i < vars.size(); i++) {
		if (name == vars[i]->name) {
			vars[i]->value = value;
			return;
		}
	}
	//CreateVariable(name, value);
	throw VariableNotDefined();
}

void Context::CreateVars(string line) {
	if (!line.empty()) {
		vector<string> variables = StringUtils::TokenizeLine(line, ',');
		unsigned int i;
		//cout << "    criou ";
		for (i = 0; i < variables.size(); i++) {
			//StringUtils::RemoveSpaces(variables[i]);
			this->CreateVar(variables[i].at(0), 0.0);
			//cout << " " << variables[i].at(0);
		}
		//cout << endl;
	}
}

void Context::CreateVar(char name, double value) {
	vars.push_back(new Variable(name, value));
}

void Context::PrintVars() {
	unsigned int i;
	for (i = 0; i < vars.size(); i++) {
		cout << "  " <<  vars[i]->name << ": " << vars[i]->value << endl;
	}
}

double Context::GetVariable(char name, Context *global_context, Context *local_context) {
	double value;
	try {
		value = local_context->GetVar(name);
	}
	catch(VariableNotDefined) {
		value = global_context->GetVar(name);
	}
	return value;
}

void Context::SetVariable(char name, double value, Context *local_context, Context *global_context) {
	try {
		local_context->SetVar(name, value);
	}
	catch(VariableNotDefined) {
		global_context->SetVar(name, value);
	}
}
