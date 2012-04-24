#include "io.h"

// Nome dos arquivos de entrada e saída
char *output_file;
char verbose;

FILE *GetArgs(int argc, char *argv[]) {
	if (argc < 3){
		printf("O programa necessita de 2 argumentos para executar.\nSaindo...\n");
		exit(EXIT_FAILURE);
	}
	else if (argc > 3){
		printf("Somente os 2 primeiros argumentos serão considerados.\n\n");
		if (argc == 4) {
			verbose = !strcmp(argv[3], "v");
		}
	}

	output_file = argv[2];

	FILE *file = fopen(argv[1], "r");

	if (!file) {
		printf("Não foi possível abrir o arquivo %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	return file;
}
