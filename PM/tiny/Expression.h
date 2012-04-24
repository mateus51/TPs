#ifndef __EXPRESSION_H__
#define __EXPRESSION_H__
using namespace std;

#include <iostream>
#include <algorithm>
#include <cstring>
//#include <string>
#include <sstream>
#include <stack>
#include <cmath>

#include "Context.h"

class Expression {
public:
	Expression(string);
	~Expression();
	double Evaluate(Context*, Context*);
	void PrintExp();

private:
	string exp;
};

// Exceção WrongExpression é lançada quando há um erro
// durante a avaliação da expressão.
class WrongExpression {
public:
	WrongExpression(int size) { cout << "ERROR ExpressionError: pilha.size() = " << size << ". Should be 1." << endl; };
};

#endif
