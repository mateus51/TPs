#ifndef __PROC_H__
#define __PROC_H__

using namespace std;

#include <vector>
#include <fstream>

#include "Command.h"
#include "Context.h"
#include "Parser.h"

class Proc {
public:
	string name;

	Proc(string, ifstream&);
	~Proc();
	void Execute(Context*);
	void Print();

	vector<string> params;
	string local_vars;
	Context *local_context;
private:
	vector<Command*> lista_comandos;
};

#endif
