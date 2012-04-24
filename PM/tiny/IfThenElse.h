#ifndef __IFTHENELSE_H__
#define __IFTHENELSE_H__

#include <fstream>

#include "Parser.h"
#include "Expression.h"
#include "Command.h"

class IfThenElse : public Command {
public:
	IfThenElse(string, ifstream&);
	~IfThenElse();
	void Interpret(Context*, Context*);

private:
	Expression *exp;
	vector<Command*> then, elce;
};

#endif
