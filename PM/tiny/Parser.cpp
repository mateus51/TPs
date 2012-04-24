#include "Parser.h"

Command* ParseLine(string line, ifstream& file) {

	Command* command = NULL;
	//cout << "parsing '" << line << "'" << endl;

	// Se o comando for writeStr
	if (line.find("writeStr(\"") != string::npos) {
		command = (Command*) new WriteStr(line);
	}

	// Se o comando for writeln
	else if (line.find("writeln") != string::npos) {
		command = (Command*) new Writeln;
	}

	// Se o comando for WriteVar
	else if (line.find("writeVar(") != string::npos) {
		command = (Command*) new WriteVar(line);
	}

	// Se o comando for 'for' -> PRECISA SER OBRIGATORIAMENTE ANTES DE ATRIBUIÇÃO DE VARIÁVEL
	else if(line.find("for ") != string::npos) {
		command = (Command*) new For(line, file);
	}

	// Se for atribuição de variável
	else if(line.find(":=") != string::npos) {
		command = (Command*) new VarAssignment(line);
	}

	//Se o comando for read()
	else if(line.find("read(") != string::npos) {
		command = (Command*) new Read(line);
	}

	//Se o comando for if
	else if(line.find("if ") != string::npos) {
		command = (Command*) new IfThenElse(line, file);
	}

	//Se o comando for um while
	else if(line.find("while ") != string::npos) {
		command = (Command*) new While(line, file);
	}

	//Se o comando for um call
	else if(line.find("call ") != string::npos) {
		command = (Command*) new Call(line);
	}

	// Se não for nenhum deles
	else {
		throw CommandNotFound(line);
		//cout << "Command not found!" << endl;
	}
	return command;
}
