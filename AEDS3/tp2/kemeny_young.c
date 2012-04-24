#include "kemeny_young.h"

pthread_mutex_t permutation_result = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t score_mutex = PTHREAD_MUTEX_INITIALIZER;

extern char permutacao_serial;
extern char score_serial;


/*
 * Calcula o resultado de uma eleição, e armazena na struct
 * apontada por eleicao.
 */
void CalculaResultado(Eleicao *eleicao) {

	// Monta a matriz com todos os votos
	MontaMatriz(eleicao);

	// Faz o cálculo serial das permuataçoes dos candidatos.
	if (permutacao_serial)
		CalculaMaiorScoreSerial(eleicao);

	// Faz o cálculo paralelo das permuataçoes dos candidatos.
	else
		CalculaMaiorScoreParalelo(eleicao);

}

/*
 * Monta a matriz com os votos dos eleitores.
 */
void MontaMatriz(Eleicao *eleicao) {
	int i, j, k;

	// Inicializando matriz...
	eleicao->matrix = malloc(sizeof(int*) * eleicao->total_candidatos);
	for(i = 0; i < eleicao->total_candidatos; i++){
		eleicao->matrix[i] = malloc(sizeof(int) * eleicao->total_candidatos);
		for(j = 0; j < eleicao->total_candidatos; j++){
			eleicao->matrix[i][j] = 0;
		}
	}

	// Montando matriz...
	for(k = 0; k < eleicao->total_listas; k++){
		for(i = 0; i < eleicao->total_candidatos; i++){
			for(j = i + 1; j < eleicao->total_candidatos; j++){
				eleicao->matrix[eleicao->votos[k].ordem_candidatos[i]][eleicao->votos[k].ordem_candidatos[j]] += eleicao->votos[k].num_votos;
			}
		}
	}
}

/*
 * Calcula o resultado de uma eleição gerando as permutações dos candidatos
 * de forma serial.  Não cria nenhuma nova thread.
 */
void CalculaMaiorScoreSerial (Eleicao *eleicao) {
	Permutation *permutation = NewPermutation(eleicao->total_candidatos);

	int i, k, score;
	for (k = 0; k < permutation->total_permutations; k++) {
		Num2Perm(k, permutation);

		if (score_serial)
			score = CalculaScoreSerial(eleicao, permutation->perm_array);
		else
			score = CalculaScoreParalelo(eleicao, permutation->perm_array);

		if (score >= eleicao->resultado.score) {
			eleicao->resultado.score = score;
			for (i = 0; i < eleicao->total_candidatos; i++) {
				eleicao->resultado.ordem[i] = permutation->perm_array[i];
			}
		}
	}

	FreePermutation(permutation);
}

/*
 * Calcula o resultado de uma eleição gerando as permutações dos candidatos
 * de forma paralela.
 */
void CalculaMaiorScoreParalelo (Eleicao *eleicao) {
	extern int total_threads_nivel1;

	// Calculando qtas permutações cada thread vai calcular.
	int total_permutations = Fatorial(eleicao->total_candidatos);
	int perm_offset = (int) ceil((float) total_permutations / (float) total_threads_nivel1);

	// Montando array de parâmetros para serem passados para as threads.
	PermutationParams params[total_threads_nivel1];
	int t;
	for(t = 0; t < total_threads_nivel1; t++){
		params[t].permutation = NewPermutation(eleicao->total_candidatos);
		params[t].eleicao = eleicao;
		params[t].start_perm = t * perm_offset;
		params[t].end_perm = ((t + 1) * perm_offset) - 1;
	}

	// Criando array de threads.
	pthread_t threads[total_threads_nivel1];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	// Cria as threads, e manda cada uma executar um pedaço do cálculo das permutações.
	int rc;
	for(t = 0; t < total_threads_nivel1; t++){
		rc = pthread_create(&threads[t], &attr, PermutacaoParalela, (void*) &params[t]);
		if (rc){
			printf("ERROR: return code from pthread_create() is %d\n\n", rc);
			exit(EXIT_FAILURE);
		}
	}

	// Espera as threads terminarem o trabalho, para continuar com a execução.
	pthread_attr_destroy(&attr);
	for(t = 0; t < total_threads_nivel1; t++) {
		rc = pthread_join(threads[t], NULL);
		if (rc) {
			printf("ERROR: return code from pthread_join() is %d\n\n", rc);
			exit(EXIT_FAILURE);
		}
	}
}

/*
 * Função a ser executada pelas threads que geram as permutações.
 */
void *PermutacaoParalela(void *args) {
	PermutationParams *params = (PermutationParams*) args;
	int i, j, score, greatest_score;
	greatest_score = 0;
	int result[params->eleicao->total_candidatos];

	/* Gera todas as permutações no intervalo definido, */
	/* e salva em uma variável local                    */
	for (i = params->start_perm; i <= params->end_perm; i++) {
		if (i < params->permutation->total_permutations) {
			Num2Perm(i, params->permutation);

			if (score_serial)
				score = CalculaScoreSerial(params->eleicao, params->permutation->perm_array);
			else
				score = CalculaScoreParalelo(params->eleicao, params->permutation->perm_array);

			if (score > greatest_score) {
				greatest_score = score;
				for (j = 0; j < params->eleicao->total_candidatos; j++) {
					result[j] = params->permutation->perm_array[j];
				}
			}
		}
	}

	FreePermutation(params->permutation);

	// Depois de salvar o resultado parcial em variáveis locais,
	// um mutex é utilizado para atualizar o resultado global.
	pthread_mutex_lock(&permutation_result);
		if (greatest_score > params->eleicao->resultado.score) {
			params->eleicao->resultado.score = greatest_score;
			for (i = 0; i < params->eleicao->total_candidatos; i++) {
				params->eleicao->resultado.ordem[i] = result[i];
			}
		}
	pthread_mutex_unlock(&permutation_result);

	pthread_exit(NULL);
}


/*
 * Cacula o score de uma permutação específica dos candidatos,
 * de forma serial. Não cria nenhuma nova thread.
 */
int CalculaScoreSerial(Eleicao *eleicao, int *result) {
	int i, j;
	int score = 0;
	for (i = 0; i < eleicao->total_candidatos; i++) {
		for (j = i+1; j < eleicao->total_candidatos; j++) {
			score += eleicao->matrix[result[i]][result[j]];
		}
	}
	return score;
}

/*
 * Cacula o score de uma permutação específica dos candidatos,
 * de forma paralela.
 */
int CalculaScoreParalelo(Eleicao *eleicao, int *result) {
	extern int total_threads_nivel2;

	// pointer compartilhado por todas as threads.
	int *score = (int*) malloc(sizeof(int));
	*score = 0;

	int total_combinations = Combinatorial(eleicao->total_candidatos);
	int comb_offset = (int) ceil((float) total_combinations / (float) total_threads_nivel2);

	/* Montando array de parâmetros para serem passados para as threads. */
	CombinationParams params[total_threads_nivel2];
	int t;
	for(t = 0; t < total_threads_nivel2; t++){
		params[t].combination = NewCombination(eleicao->total_candidatos);
		params[t].start_comb = t * comb_offset;
		params[t].end_comb = ((t + 1) * comb_offset) - 1;
		params[t].eleicao = eleicao;
		params[t].score = score;
		params[t].result = result;
	}

	/* Criando array de threads. */
	pthread_t threads[total_threads_nivel2];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	/* Cria as threads, e manda cada uma executar um pedaço do cálculo das permutações. */
	int rc;
	for(t = 0; t < total_threads_nivel2; t++){
		rc = pthread_create(&threads[t], &attr, CombinacaoParalela, (void*) &params[t]);
		if (rc){
			printf("\nERROR: return code from pthread_create() is %d\n\n", rc);
			exit(EXIT_FAILURE);
		}
	}

	/* Espera as threads terminarem o trabalho, para continuar com a execução. */
	for(t = 0; t < total_threads_nivel2; t++) {
		rc = pthread_join(threads[t], NULL);
		if (rc) {
			printf("\nERROR: return code from pthread_join() is %d\n\n", rc);
			exit(EXIT_FAILURE);
		}
	}

	pthread_attr_destroy(&attr);

	int return_value = *score;
	free(score);

	return return_value;
}

/*
 * Função a ser executada pelas threads que geram as combinações dos candidatos.
 */
void *CombinacaoParalela(void* args) {
	CombinationParams *params = (CombinationParams*) args;

	// Calculando o score parcial.
	int i, score = 0;
	for (i = params->start_comb; i <= params->end_comb; i++) {
		if (i < params->combination->total_combinations) {
			Num2Comb(i, params->combination);
			//printf("%d -> %d %d\n", i, params->combination->comb[0], params->combination->comb[1]);
			score += params->eleicao->matrix[params->result[params->combination->comb[0]]][params->result[params->combination->comb[1]]];
		}
	}

	FreeCombination(params->combination);

	// Atualiza o resultado global.
	pthread_mutex_lock(&score_mutex);
		*(params->score) += score;
	pthread_mutex_unlock(&score_mutex);

	pthread_exit(NULL);
}
