#include "io.h"

int estrategia, cache_size;

FILE* ParseParams(int argc, char *argv[]) {
	if(argc < 4){
		printf("O programa deve receber 3 argumentos como parâmetro:\n");
		printf("  ./tp6 <arquivoLog> <0 ou 1 ou 2> <tamanho da cache em Kbytes>\n\n");
		exit(EXIT_FAILURE);
	}
	else if(argc > 4){
		printf("Somente 4 primeiros argumentos serão usados.\n\n");
	}

	estrategia = atoi(argv[2]);

	if (estrategia > 2 || estrategia < 0) {
		printf("A estratégia deve ser 0 ou 1 ou 2\n");
		exit(EXIT_FAILURE);
	}

	cache_size = atoi(argv[3]);

	if (cache_size < 0) {
		printf("Deve ser passado um valor positivo para o tamanho da cache.\n");
		exit(EXIT_FAILURE);
	}

	FILE *file = fopen(argv[1], "r");
	if(!file){
		printf("Não foi possível abrir o arquivo '%s'. Saindo do programa...\n\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	return file;
}

void RemoveNewlineChar(char *string) {
	int size = strlen(string);
	if (string[size-1] == '\n') string[size-1] = '\0';
}
