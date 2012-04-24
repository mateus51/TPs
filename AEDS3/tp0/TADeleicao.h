#ifndef TADELEICAO_H
#define TADELEICAO_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct {
	int *ordem_candidatos;
	int num_votos;
} Voto;

typedef struct {
	int score;
	int *ordem;
} Resultado;

typedef struct {
	char **candidatos;
	Voto *votos;
	Resultado resultado;
	int **matrix;
	int total_candidatos;
	int total_listas;
} Eleicao;

void SalvaCandidatos(char *line, Eleicao *eleicao);

int IndexCandidato(Eleicao eleicao, char* candidato);

void ImprimeEleicao(Eleicao eleicao);

void ImprimeResultado(Eleicao eleicao);

void FreeEleicao(Eleicao *eleicao);

#endif
