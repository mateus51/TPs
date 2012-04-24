#include "benchmark.h"
#include "io.h"


void fb(Show *show) {
	int vol_atual = show->vol_inicial;

	if (vol_atual < 0 || vol_atual > show->vol_limite) {
		printf("-1\n");
		return;
	}

	long long unsigned int i, control = 0, mask = 1;
	int counter;
	int higher_vol = -1;

	int j;
	for (i = 0; i < pow((double) 2, (double) show->num_musicas) - 1; i++) {
		control = i;
		counter = 0;
		vol_atual = show->vol_inicial;
		for (j = 0; j < show->num_musicas - 1; j++) {

			// Se o bit menos significativo do control for 1, soma o volume.
			// Caso contrário subtrai o volume.
			if (control & mask)
				vol_atual += show->volumes[counter];
			else
				vol_atual -= show->volumes[counter];


			// Se saiu dos limites, marca o erro e continua.
			if (vol_atual < 0 || vol_atual > show->vol_limite) {
				vol_atual = -1;
				break;
			}

			// Soma o contador e faz o shift para testar o próximo bit.
			counter += 1;
			control >>= 1;
		}

		if (vol_atual > higher_vol) higher_vol = vol_atual;
	}
	printf("%d", higher_vol);
}

int main (int argc, char *argv[]) {

	FILE *file = ParseParams(argc, argv);

	extern char benchmark;
	struct timeval start_time, end_time;

	while (!feof(file)) {
		Show *show = ReadShowFromFile(file);
		if (benchmark) gettimeofday(&start_time, NULL);
		fb(show);
		if (benchmark) {
			gettimeofday(&end_time, NULL);
			printTime(&start_time, &end_time);
		}
		printf("\n");
		FreeShow(show);
	}

	return 0;
}
