#include "io.h"
#include "fractal.h"
#include "benchmark.h"

int main(int argc, char *argv[]) {

	FILE *file = ParseParams(argc, argv);

	extern boolean benchmark;
	struct timeval start_time, end_time;

	while (!feof(file)) {
		Grafo *grafo = ReadGraphFromFile(file);
		if (benchmark) gettimeofday(&start_time, NULL);
		CheckIfIsFractal(grafo);
		if (benchmark) {
			gettimeofday(&end_time, NULL);
			printTime(&start_time, &end_time);
		}
		FreeGraph(grafo);
	}

/*
	Grafo *grafo = ReadGraphFromFile(file);
	PrintGraph(grafo);
	CheckIfIsFractal(grafo);
	printf("\n\n\n\n\n\n\n");
	FreeGraph(grafo);
*/


	fclose(file);

	return 0;
}
