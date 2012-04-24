#ifndef __PARSER_H__
#define __PARSER_H__

#include "VarAssignment.h"
#include "StringUtils.h"
#include "IfThenElse.h"
#include "WriteVar.h"
#include "WriteStr.h"
#include "Writeln.h"
#include "While.h"
#include "Call.h"
#include "Read.h"
//#include "Proc.h"
#include "For.h"

Command* ParseLine(string, ifstream&);

// Exceção q é lançada qdo um comando não reconhecido é lido
class CommandNotFound {
public:
	CommandNotFound(string command) { cout << "ERROR: Command Not Found: '" << command << "'\n"; }
};

#endif
