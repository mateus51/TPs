#include "io.h"

char benchmark = 0;

FILE* ParseParams(int argc, char *argv[]) {
	if(argc < 2){
		printf("Somente o nome do arquivo de entrada deve ser passado na inicialização do programa:\n");
		exit(EXIT_FAILURE);
	}
	else if(argc > 2){
		if (!strcmp(argv[2], "benchmark")) {
			benchmark = 1;
		}
		else {
			printf("Somente o primeiro argumento passado para o programa será usado.\n");
			printf("Todos os outros serão ignorados.\n\n");
		}
	}

	FILE *file = NULL;
	if((file = fopen(argv[1], "r")) == NULL){
		printf("Não foi possível abrir o arquivo '%s'. Saindo do programa...\n\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	return file;
}

Show *ReadShowFromFile(FILE *file) {
	Show *show = NewShow();
	fscanf(file, "%d %d %d\n", &show->num_musicas, &show->vol_inicial, &show->vol_limite);
	show->volumes = (int*) calloc(show->num_musicas - 1, sizeof(int));
	int i;
	for (i = 0; i < show->num_musicas - 2; i++) {
		fscanf(file, "%d ", &show->volumes[i]);
	}
	fscanf(file, "%d\n", &show->volumes[i]);

	return show;
}

