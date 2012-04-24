#include "TADeleicao.h"

void SalvaCandidatos(char *line, Eleicao *eleicao){
	char *string = malloc(sizeof(char) * (strlen(line) + 1));
	strcpy(string, line);
	char *token = strtok(string, " ");
	int num_candidatos = 0;
	while(token != NULL){
		num_candidatos++;
		eleicao->candidatos = realloc(eleicao->candidatos, sizeof(char*) * num_candidatos);
		eleicao->candidatos[num_candidatos - 1] = malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(eleicao->candidatos[num_candidatos - 1], token);
		token = strtok(NULL, " ");
	}
	eleicao->total_candidatos = num_candidatos;
	free(string);
}

int IndexCandidato(Eleicao eleicao, char* candidato){
	int i;
	for(i = 0; i < eleicao.total_candidatos; i++){
		if(strcmp(candidato, eleicao.candidatos[i]) == 0){
			return i;
		}
	}
	return -1;
}

void ImprimeEleicao(Eleicao eleicao){
	int j;
	printf("-------------------\n\n");
	printf("Candidatos:\n");
	for(j = 0; j < eleicao.total_candidatos; j++){
		printf("  - %s\n", eleicao.candidatos[j]);
	}
	printf("\nVotos:\n");
	for(j = 0; j < eleicao.total_listas; j++){
		printf("%d - %d %d %d %d\n", eleicao.votos[j].num_votos, eleicao.votos[j].ordem_candidatos[0], eleicao.votos[j].ordem_candidatos[1], eleicao.votos[j].ordem_candidatos[2], eleicao.votos[j].ordem_candidatos[3]);
	}
	printf("-------------------\n\n");
}

void ImprimeResultado(Eleicao eleicao){
	int i;
	for(i = 0; i < eleicao.total_candidatos; i++)
		printf("%s ", eleicao.candidatos[eleicao.resultado.ordem[i]]);
	printf("%d\n", eleicao.resultado.score);
}

void FreeEleicao(Eleicao *eleicao){
	int i;

	for(i = 0; i < eleicao->total_candidatos; i++){
		free(eleicao->matrix[i]);
		free(eleicao->candidatos[i]);
	}
	free(eleicao->matrix);
	free(eleicao->candidatos);

	for(i = 0; i < eleicao->total_listas; i++){
		free(eleicao->votos[i].ordem_candidatos);
	}
	free(eleicao->votos);

	free(eleicao->resultado.ordem);
}
