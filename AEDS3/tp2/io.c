#include "io.h"

int total_threads_nivel1, total_threads_nivel2;
char permutacao_serial, score_serial, benchmark = 0;

FILE* ParseParams(int argc, char *argv[]){
	if(argc < 4){
		printf("Devem ser passados 4 argumentos na inicialização do programa:\n");
		printf("  ./tp2 <arquivo> <numero de threads nivel 1> <numero de threads nivel 2>\n\n");
		exit(EXIT_FAILURE);
	}
	else if(argc > 4){
		benchmark = !strcmp(argv[4], "bench");

		if (!benchmark){
			printf("Somente o 3 primeiros argumentos passados para o programa serão usados.\n");
			printf("Todos os outros serão ignorados.\n\n");
		}
		else if (argc > 5) {
			printf("Somente o 4 primeiros argumentos passados para o programa serão usados.\n");
			printf("Todos os outros serão ignorados.\n\n");
		}
	}

	total_threads_nivel1 = atoi(argv[2]);
	permutacao_serial = (total_threads_nivel1 == 0);

	total_threads_nivel2 = atoi(argv[3]);
	score_serial = (total_threads_nivel2 == 0);

	FILE *file = NULL;
	if((file = fopen(argv[1], "r")) == NULL){
		printf("Não foi possível abrir o arquivo '%s'. Saindo do programa...\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	return file;
}

Eleicao *LeEleicao(FILE *file){
	int i, k, total_listas;
	Eleicao *eleicao = (Eleicao*) malloc(sizeof(Eleicao));

	fscanf(file, "%d\n", &total_listas);
	eleicao->votos = (Voto*) malloc(sizeof(Voto) * total_listas);
	eleicao->candidatos = NULL;
	eleicao->total_listas = total_listas;

	char *line = malloc(sizeof(char) * (LINE_MAX_SIZE + 1));
	for(i = 0; i < total_listas; i++){
		fscanf(file, "%d\n", &eleicao->votos[i].num_votos);
		line = fgets(line, LINE_MAX_SIZE, file);
		ChangeNewLineToNull(line);
		if(eleicao->candidatos == NULL){
			SalvaCandidatos(line, eleicao);
		}
		eleicao->votos[i].ordem_candidatos = malloc(sizeof(int) * eleicao->total_candidatos);

		char *token = strtok(line, " ");
		for(k = 0; token != NULL; k++){
			eleicao->votos[i].ordem_candidatos[k] = IndexCandidato(eleicao, token);
			token = strtok(NULL, " ");
		}
	}
	free(line);

	eleicao->resultado.score = 0;
	eleicao->resultado.ordem = (int*) malloc(sizeof(int) * eleicao->total_candidatos);

	return eleicao;
}

void ChangeNewLineToNull(char *string){
	int size = strlen(string);
	if(string[size - 1] == '\n'){
		string[size - 1] = '\0';
	}
}

