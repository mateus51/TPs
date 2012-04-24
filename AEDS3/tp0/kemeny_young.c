#include "kemeny_young.h"

void MontaMatriz(Eleicao *eleicao){
	int i, j, k;

	/* Inicializando matriz... */
	eleicao->matrix = malloc(sizeof(int*) * eleicao->total_candidatos);
	for(i = 0; i < eleicao->total_candidatos; i++){
		eleicao->matrix[i] = malloc(sizeof(int) * eleicao->total_candidatos);
		for(j = 0; j < eleicao->total_candidatos; j++){
			eleicao->matrix[i][j] = 0;
		}
	}

	/* Montando matriz... */
	for(k = 0; k < eleicao->total_listas; k++){
		for(i = 0; i < eleicao->total_candidatos; i++){
			for(j = i + 1; j < eleicao->total_candidatos; j++){
				eleicao->matrix[eleicao->votos[k].ordem_candidatos[i]][eleicao->votos[k].ordem_candidatos[j]] += eleicao->votos[k].num_votos;
			}
		}
	}
}

int CalculaScore(Eleicao *eleicao, int *result){
	int i, j;
	int score = 0;
	for(i = 0; i < eleicao->total_candidatos; i++){
		for(j = i + 1; j < eleicao->total_candidatos; j++){
			score += eleicao->matrix[result[i]][result[j]];
		}
	}
	return score;
}

void SalvaResultado(Eleicao *eleicao, int score, int *result){
	eleicao->resultado.score = score;
	int i;
	for(i = 0; i < eleicao->total_candidatos; i++){
		eleicao->resultado.ordem[i] = result[i];
	}
}

void CalculaMaiorScore(Eleicao *eleicao, int *result, int start, int n){
	int i, score;
	if(start == n-1){
		score = CalculaScore(eleicao, result);
		if(score > eleicao->resultado.score){
			SalvaResultado(eleicao, score, result);
		}
	}
	else{
		for (i = start; i < n; i++){
			int tmp = result[i];
			result[i] = result[start];
			result[start] = tmp;
			CalculaMaiorScore(eleicao, result, start+1, n);
			result[start] = result[i];
			result[i] = tmp;
		}
	}
}

void CalculaResultado(Eleicao *eleicao){
	eleicao->resultado.score = 0;
	eleicao->resultado.ordem = (int *) malloc(sizeof(int) * eleicao->total_candidatos);

	/* Monta a matriz com todos os votos */
	MontaMatriz(eleicao);

	/* Array usado para gerar todas as permutações dos candidatos */
	int *result = (int *) malloc(sizeof(int) * eleicao->total_candidatos);
	int i;
	for(i = 0; i < eleicao->total_candidatos; i++){
		result[i] = i;
	}

	/* Gera resursivamente todas as permutacoes de um array */
	CalculaMaiorScore(eleicao, result, 0, eleicao->total_candidatos);

	free(result);
}

void KemenyYoung(int argc, char *argv[]){
	int i, total_instancias;

	FILE *file = ParseParams(argc, argv);

	fscanf(file, "%d\n", &total_instancias);

	for(i = 0; i < total_instancias; i++){
		Eleicao eleicao = LeEleicao(file);
		CalculaResultado(&eleicao);
		ImprimeResultado(eleicao);
		FreeEleicao(&eleicao);
	}

	fclose(file);
}
