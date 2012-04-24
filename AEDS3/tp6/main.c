#include "io.h"
#include "cache.h"

int main(int argc, char **argv) {

	FILE *log = ParseParams(argc, argv);

	SimulaCache(log);

	fclose(log);

	return EXIT_SUCCESS;
}
