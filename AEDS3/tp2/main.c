#include "kemeny_young.h"
#include "benchmark.h"

int main(int argc, char *argv[]){

	int i, total_instancias;

	FILE *file = ParseParams(argc, argv);

	fscanf(file, "%d\n", &total_instancias);

	extern char benchmark;
	struct timeval start_time, end_time;

	for(i = 0; i < total_instancias; i++){
		if (benchmark) gettimeofday(&start_time, NULL);
		Eleicao *eleicao = LeEleicao(file);
		CalculaResultado(eleicao);
		ImprimeResultado(eleicao);
		FreeEleicao(eleicao);
		if (benchmark) {
			gettimeofday(&end_time, NULL);
			printTime(&start_time, &end_time);
		}
	}

	fclose(file);

	return 0;
}
