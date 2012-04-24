#include "expansor.h"
#include "io.h"

int main(int argc, char *argv[]) {

	FILE *file = GetArgs(argc, argv);

	Macro **macros = LeMacros(file);

	extern char verbose;
	if (verbose) {
		int i;
		for (i = 0; macros[i] != NULL; i++) {
			PrintMacro(macros[i]);
		}
	}

	rewind(file);

	WriteFile(file, macros);

	FreeArrayMacros(macros);

	fclose(file);

	return 0;
}
