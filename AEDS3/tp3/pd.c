#include "benchmark.h"
#include "io.h"

void pd(Show *show) {
	int **table = NewPdTable(show);
	int var, vol, vol_atual, vol_acima, vol_abaixo;

	for (var = show->num_musicas - 2; var >= 0; var--) {
		for (vol = 0; vol <= show->vol_limite; vol++) {

			//printf("%d %d\n", var, vol);

			// Se for a última linha
			if (var == show->num_musicas - 2) {
				vol_atual = vol + show->volumes[var];

				if (vol_atual > show->vol_limite)
					vol_atual = vol - show->volumes[var];

				if (vol_atual < 0)
					table[var][vol] = -1;
				else
					table[var][vol] = vol_atual;
			}

			else {

				vol_acima = vol + show->volumes[var];
				vol_abaixo = vol - show->volumes[var];

				if (vol_acima <= show->vol_limite && vol_abaixo >= 0) {
					table[var][vol] = table[var+1][vol_acima] > table[var+1][vol_abaixo] ? table[var+1][vol_acima] : table[var+1][vol_abaixo];
				}
				else if (vol_acima <= show->vol_limite) {
					table[var][vol] = table[var+1][vol_acima];
				}
				else if (vol_abaixo >= 0) {
					table[var][vol] = table[var+1][vol_abaixo];
				}
				else {
					table[var][vol] = -1;
				}

			}

		}
	}

	printf("%d", table[0][show->vol_inicial]);

	FreePdTable(table, show->num_musicas - 1);
}

int **NewPdTable(Show *show) {
	int i;
	int **table = (int**) calloc(show->num_musicas - 1, sizeof(int*));
	for (i = 0; i < show->num_musicas - 1; i++) {
		table[i] = (int*) calloc(show->vol_limite + 1, sizeof(int));
	}
	return table;
}

void FreePdTable(int **table, int n) {
	int i;
	for (i = 0; i < n; i++) {
		free(table[i]);
	}
	free(table);
}

void PrintPdTable(Show *show, int **table) {
	int i, j;
	for (i = 0; i < show->num_musicas - 1; i++) {
		for (j = 0; j <= show->vol_limite; j++)
			printf("%4d", table[i][j]);
		printf("\n");
	}

}

int main (int argc, char *argv[]) {

	FILE *file = ParseParams(argc, argv);

	extern char benchmark;
	struct timeval start_time, end_time;

	while (!feof(file)) {
		Show *show = ReadShowFromFile(file);
		if (benchmark) gettimeofday(&start_time, NULL);
		pd(show);
		if (benchmark) {
			gettimeofday(&end_time, NULL);
			printTime(&start_time, &end_time);
		}
		printf("\n");
		FreeShow(show);
	}

	return 0;
}
