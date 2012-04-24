#include "io.h"

FILE* ParseParams(int argc, char *argv[]){
	if(argc < 2){
		printf("O nome do arquivo de entrada deve ser passado na inicialização do programa.\n");
		exit(EXIT_FAILURE);
	}
	else if(argc > 2){
		printf("Somente o primeiro argumento passado para o programa será usado.\n");
		printf("Todos os outros serão ignorados.\n\n");
	}

	FILE *file = NULL;
	if((file = fopen(argv[1], "r")) == NULL){
		printf("Não foi possível abrir o arquivo '%s'. Saindo do programa...\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	return file;
}

Eleicao LeEleicao(FILE *file){
	int i, k, total_listas;
	Eleicao eleicao;

	fscanf(file, "%d\n", &total_listas);
	eleicao.votos = (Voto*) malloc(sizeof(Voto) * total_listas);
	eleicao.candidatos = NULL;
	eleicao.total_listas = total_listas;

	char *line = malloc(sizeof(char) * (LINE_MAX_SIZE + 1));
	for(i = 0; i < total_listas; i++){
		fscanf(file, "%d\n", &eleicao.votos[i].num_votos);
		line = fgets(line, LINE_MAX_SIZE, file);
		ChangeNewLineToNull(line);
		if(eleicao.candidatos == NULL){
			SalvaCandidatos(line, &eleicao);
		}
		eleicao.votos[i].ordem_candidatos = malloc(sizeof(int) * eleicao.total_candidatos);

		char *token = strtok(line, " ");
		for(k = 0; token != NULL; k++){
			eleicao.votos[i].ordem_candidatos[k] = IndexCandidato(eleicao, token);
			token = strtok(NULL, " ");
		}
	}
	free(line);
	return eleicao;
}

void ChangeNewLineToNull(char *string){
	int size = strlen(string);
	if(string[size - 1] == '\n'){
		string[size - 1] = '\0';
	}
}

