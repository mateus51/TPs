#ifndef __VAR_ASSIGNMENT_H__
#define __VAR_ASSIGNMENT_H__
using namespace std;

#include "Expression.h"
#include "Command.h"

class VarAssignment : public Command {
public:

	VarAssignment(string);
	~VarAssignment();
	void Interpret(Context*, Context*);

private:
	char name;
	Expression *exp;
};

#endif
