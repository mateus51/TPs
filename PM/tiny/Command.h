#ifndef __COMMAND_H__
#define __COMMAND_H__

using namespace std;

#include <iostream>
#include <string>

#include "Context.h"

class Command {
public:

	virtual void Interpret(Context *global_context, Context *local_context) = 0;

};

#endif
