#include "mv.h"

extern char verbose;

int main(int argc, char *argv[]){

	Args *args = GetArgs(argc, argv);

	MaquinaVirtual *mv = NewMV(args);

	LoadProgram(mv, args->filename);

	RunMV(mv);

	free(mv);
	free(args);

	return 0;
}

