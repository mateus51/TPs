#include "io.h"

int main (int argc, char *argv[]) {

	FILE *file = ParseParams(argc, argv);

	while (!feof(file)) {
		Show *show = ReadShowFromFile(file);
		int *higher_vol = (int*) malloc(sizeof(int));
		*higher_vol = -1;
		Recursive(show, 0, show->vol_inicial, higher_vol);
		printf("%d\n", *higher_vol);
		free(higher_vol);
		FreeShow(show);
	}

	return 0;
}
