#include "show.h"

Show *NewShow() {
	Show *show = (Show*) malloc(sizeof(Show));
	show->num_musicas = 0;
	show->vol_inicial = 0;
	show->vol_limite = 0;
	show->volumes = NULL;

	return show;
}

void FreeShow(Show *show) {
	free(show->volumes);
	free(show);
}

void PrintShow(Show *show) {
	printf("total_musicas: %d\nvolume inicial: %d\nvolume limite: %d\nvolumes: ", show->num_musicas, show->vol_inicial, show->vol_limite);
	int i;
	for (i = 0; i < show->num_musicas - 1; i++) {
		printf("%3d", show->volumes[i]);
	}
	printf("\n");
	printf("\n");
}




