#ifndef __STRING_UTILS_H__
#define __STRING_UTILS_H__
using namespace std;

#include <iostream>
#include <vector>
#include <string>

//#include "Command.h"

/*
#include "VarAssignment.h"
#include "StringUtils.h"
#include "IfThenElse.h"
#include "WriteVar.h"
#include "WriteStr.h"
#include "Command.h"
#include "Writeln.h"
#include "While.h"
#include "Read.h"
#include "Proc.h"
#include "For.h"
*/

class StringUtils {
public:
	static void RemoveSpaces(string&);
	static vector<string> TokenizeLine(string, char);
	//static Command* ParseLine(string, ifstream&);
};

#endif
