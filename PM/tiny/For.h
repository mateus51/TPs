#ifndef __FOR_H__
#define __FOR_H__

#include <fstream>

#include "Parser.h"
#include "Command.h"
#include "Expression.h"
#include "StringUtils.h"

class For : public Command {
public:
	For(string, ifstream&);
	~For();
	void Interpret(Context*, Context*);

private:
	char var;
	vector<Command*> lista_comandos;
	Expression *start_exp, *end_exp;
};

#endif
