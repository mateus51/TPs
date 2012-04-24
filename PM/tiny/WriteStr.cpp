#include "WriteStr.h"

WriteStr::WriteStr(string cmd) {
	str = WriteStr::GetStringToPrint(cmd);
	//cout << "String to print: " << str << endl;
}

WriteStr::~WriteStr() {
	cout << "Deleting WriteStr(\"" << str << "\")" << endl;
}

void WriteStr::Interpret(Context *global_context, Context *local_context) {
	cout << str;
}


string WriteStr::GetStringToPrint(string cmd) {
	size_t str_start_pos, str_length;
	str_start_pos = cmd.find("\"") + 1;
	str_length = cmd.rfind("\"") - str_start_pos;
	//cout << "start pos: " << str_start_pos << endl;
	//cout << "length: " << str_length << endl;
	string str_to_print = cmd.substr(str_start_pos, str_length);
	cmd.clear();
	return str_to_print;
}
