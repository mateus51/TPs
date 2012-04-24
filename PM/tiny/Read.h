#ifndef __READ_H__
#define __READ_H__
using namespace std;

#include "Command.h"

class Read : public Command {
public:
	Read(string);
	void Interpret(Context*, Context*);

private:
	char var_name;
};

#endif
