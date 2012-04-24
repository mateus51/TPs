#include "io.h"

// Variável global "boolean" que indica o modo verbose.
char verbose = TRUE;

// Posição de memória a partir da qual o programa será carregado.
int load_exe_from;

Args *GetArgs(int argc, char *argv[]){
	if (argc < 6){
		printf("O programa necessita de 5 argumentos para executar.\nSaindo...\n");
		exit(EXIT_FAILURE);
	}
	else if (argc > 6){
		printf("O programa necessita de 5 argumentos para executar.\nSomente os 5 primeiros serão considerados.\n\n");
	}

	Args *args = (Args*) malloc(sizeof(Args));

	args->PC = atoi(argv[1]);

	args->SP = atoi(argv[2]);

	load_exe_from = atoi(argv[3]);

	if (strcmp(argv[4], "v")) verbose = FALSE;

	args->filename = argv[5];

	return args;
}
