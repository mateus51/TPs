#ifndef __WHILE_H__
#define __WHILE_H__

#include <fstream>

#include "Expression.h"
#include "Command.h"
#include "Parser.h"

class While : public Command {
public:
	While(string, ifstream&);
	~While();
	void Interpret(Context*, Context*);

private:
	Expression *exp;
	vector<Command*> lista_comandos;
};

#endif
