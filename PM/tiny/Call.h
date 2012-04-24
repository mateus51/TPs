#ifndef __CALL_H__
#define __CALL_H__

using namespace std;

#include <cstdlib>

#include "Program.h"
#include "Command.h"
#include "Proc.h"

class Proc;

class Call : public Command {
public:
	Call(string);
	~Call();
	void Interpret(Context*, Context*);
	void CopyParamsToLocalContext(Proc*, Context*, Context*);
	void Print(Context*, Context*);

private:
	string proc_name;
	vector<Expression*> params;
};

class ProcNotFound {
public:
	ProcNotFound(string name) { cout << "ERROR: '" << name << "' proc not found!" << endl; };
};

#endif
