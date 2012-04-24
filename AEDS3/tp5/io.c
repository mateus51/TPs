#include "io.h"

FILE* ParseParams(int argc, char *argv[]) {
	if(argc < 2){
		printf("O nome do arquivo de entrada deve ser passado na inicialização do programa.\n");
		exit(EXIT_FAILURE);
	}
	else if(argc > 2){
		printf("Somente o primeiro argumento passado para o programa será usado.\n\n");
	}

	FILE *file = fopen(argv[1], "r");
	if(!file){
		printf("Não foi possível abrir o arquivo '%s'. Saindo do programa...\n\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	return file;
}
