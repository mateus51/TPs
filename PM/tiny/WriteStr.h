#ifndef __WRITESTR_H__
#define __WRITESTR_H__

using namespace std;

#include "Command.h"

class WriteStr : public Command {
public:
	WriteStr(string);
	~WriteStr();
	void Interpret(Context*, Context*);
	static string GetStringToPrint(string);

private:

	string str;
};

#endif
