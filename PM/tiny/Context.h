#ifndef __CONTEXT_H__
#define __CONTEXT_H__
using namespace std;

#include <iostream>
#include <vector>

#include "Variable.h"
#include "StringUtils.h"

class Context {
public:
	~Context();
	void CreateVar(char, double);
	void CreateVars(string);
	void PrintVars();

	static double GetVariable(char, Context*, Context*);
	static void SetVariable(char, double, Context*, Context*);

	vector<Variable*> vars;
private:
	double GetVar(char);
	void SetVar(char, double);


};

//Exception class
class VariableNotDefined {};

#endif
