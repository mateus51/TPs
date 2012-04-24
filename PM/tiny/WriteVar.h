#ifndef __WRITE_VAR_H__
#define __WRITE_VAR_H__
using namespace std;

#include "Command.h"

class WriteVar : public Command {
public:

	WriteVar(string);
	void Interpret(Context*, Context*);

private:
	char var_name;
};
#endif
