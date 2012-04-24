#ifndef __WRITELN_H__
#define __WRITELN_H__

#include "Command.h"

class Writeln : public Command {
public:
	void Interpret(Context*, Context*);
};

#endif
