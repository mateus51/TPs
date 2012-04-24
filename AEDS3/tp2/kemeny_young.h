#ifndef KEMENY_YOUNG_H
#define KEMENY_YOUNG_H

#include <pthread.h>
#include <math.h>
#include "io.h"
#include "enumerations.h"
#include "eleicao.h"


/*
 * struct armazena os parâmetros a serem passados para as threads que
 * calculam as permutações dos candidatos paralelamente
 */
typedef struct {
	Permutation *permutation;
	Eleicao *eleicao;
	int start_perm;
	int end_perm;
} PermutationParams;


/*
 * struct armazena os parâmetros a serem passados para as threads que
 * calculam as combinações dos candidatos paralelamente
 */
typedef struct {
	Combination *combination;
	int start_comb;
	int end_comb;
	Eleicao *eleicao;
	int *score;
	int *result;
} CombinationParams;



void CalculaResultado(Eleicao *eleicao);

void MontaMatriz(Eleicao *eleicao);

void CalculaMaiorScoreSerial (Eleicao *eleicao);

void CalculaMaiorScoreParalelo (Eleicao *eleicao);

void *PermutacaoParalela(void *args);

int CalculaScoreSerial(Eleicao *eleicao, int *result);

int CalculaScoreParalelo(Eleicao *eleicao, int *result);

void *CombinacaoParalela(void* args);


#endif
