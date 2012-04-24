#include "io.h"

// Variável global "boolean" que indica o modo verbose.
char verbose;

// Nome dos arquivos de entrada e saída
char *exec_name;

FILE *GetArgs(int argc, char *argv[]) {
	if (argc < 4){
		printf("O programa necessita de 3 argumentos para executar.\nSaindo...\n");
		exit(EXIT_FAILURE);
	}
	else if (argc > 4){
		printf("Somente os 3 primeiros argumentos serão considerados.\n\n");
	}

	verbose = strcmp(argv[1], "s");

	exec_name = argv[3];

	FILE *file = fopen(argv[2], "r");

	if (!file) {
		printf("Não foi possível abrir o arquivo %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}

	return file;
}
