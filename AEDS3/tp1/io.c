#include "io.h"

/*
 * Retorna o primeiro parâmetro passado pela linha de comando
 * na hora da execução do programa. Aborta a execução do
 * programa caso nenhum parâmetro seja passado.
 */
char* ParseParams(int argc, char *argv[]){
	if(argc < 2){
		printf("Deve ser passado um argumento na inicialização do programa.\n");
		exit(EXIT_FAILURE);
	}
	else if(argc > 2){
		printf("Somente o primeiro argumento passado para o programa será usado.\n");
		printf("Todos os outros serão ignorados.\n\n");
	}
	return argv[1];
}
