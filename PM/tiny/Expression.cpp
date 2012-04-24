#include "Expression.h"

Expression::Expression(string str) {
	//cout << "-- New Exp: '" << str << "'" << endl;
	size_t pos = str.find_first_not_of(" ");
	if (pos != string::npos)
		str = str.substr(pos);
	exp = str;
}

Expression::~Expression() {
	//while (!pilha.empty())
	//	pilha.pop();
}

double Expression::Evaluate(Context *global_context, Context *local_context) {
	stack<double> pilha;
	double n1, n2;

	//cout << "Expression: '" << exp << "'" << endl;

	stringstream os(exp);
	string temp;

	while (os >> temp) {

		//cout << "-- '" << temp << "' --" << endl;

		// Se o token da expressão é um número, empilha
		if (strspn(temp.c_str(), "0123456789.") == temp.length()) {
			pilha.push(atof(temp.c_str()));
			//cout << "pushed " << pilha.top() << endl;
		}

		// Se é variável, empilha o valor da variável
		else if (strspn(temp.c_str(), "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") == 1) {
			pilha.push(Context::GetVariable(temp.at(0), global_context, local_context));
			//cout << "pushed " << pilha.top() << endl;
		}

		// Se não é número nem variável, é operador
		else {
			n2 = pilha.top();
			pilha.pop();
			if (!pilha.empty()) {
				n1 = pilha.top();
				pilha.pop();
			}

			if (temp.compare("+") == 0) {
				pilha.push(n1 + n2);
			}
			else if (temp.compare("-") == 0) {
				//cout << "subtraindo: " << n1 << " - " << n2;
				pilha.push(n1 - n2);
				//cout << " -> " << (n1 - n2) << endl;
			}
			else if (temp.compare("/") == 0) {
				pilha.push(n1 / n2);
			}
			else if (temp.compare("*") == 0) {
				pilha.push(n1 * n2);
			}
			else if (temp.compare("sqrt") == 0) {
				pilha.push(n1);
				pilha.push(sqrt(n2));
			}
			else if (temp.compare(">") == 0) {
				//cout << "comparing >: " << n1 << " > " << n2;
				pilha.push(n1 > n2);
				//cout << " -> " << (n1 > n2) << endl;
			}
			else if (temp.compare("<") == 0) {
				pilha.push(n1 < n2);
			}
			else if (temp.compare(">=") == 0) {
				pilha.push(n1 >= n2);
			}
			else if (temp.compare("<=") == 0) {
				pilha.push(n1 <= n2);
			}
			else if (temp.compare("<>") == 0) {
				pilha.push(n1 != n2);
			}
			else if (temp.compare("=") == 0) {
				pilha.push(n1 == n2);
			}
			else if (temp.compare("and") == 0) {
				pilha.push(n1 && n2);
			}
			else if (temp.compare("or") == 0) {
				pilha.push(n1 || n2);
			}
			else if (temp.compare("not") == 0) {
				pilha.push(n1);
				pilha.push(!n2);
			}
		}
	}

	if (pilha.size() == 1) {
		return pilha.top();
	}
	else {
		throw WrongExpression(pilha.size());
	}

}

void Expression::PrintExp() {
	cout << exp << endl;
}
