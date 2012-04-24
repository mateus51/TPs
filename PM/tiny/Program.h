#ifndef __PROGRAM_H__
#define __PROGRAM_H__

using namespace std;

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "StringUtils.h"
#include "Context.h"
#include "Proc.h"

class Context;
class Proc;

class Program {
public:
	Program(const char*);
	~Program();
	void Run();

	static vector<Proc*> lista_procs;

private:
	void Parse();

	string filename;
	Context* global_context;
};

class MainProcNotFound {
public:
	MainProcNotFound() { cout << "ERROR: 'main' proc not found!" << endl; }
};

#endif
