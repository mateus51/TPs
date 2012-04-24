#include "Program.h"
using namespace std;

int main(int argc, char **argv) {

	if (argc < 2) {
		cout << "O nome do arquivo de entrada deve ser passado como parâmetro!" << endl;
	}
	else {
		Program* program = new Program(argv[1]);

		program->Run();

		delete program;
	}

	return 0;
}
