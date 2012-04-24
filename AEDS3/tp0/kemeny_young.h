#ifndef KEMENY_YOUNG_H
#define KEMENY_YOUNG_H

#include "io.h"

void MontaMatriz(Eleicao *eleicao);

int CalculaScore(Eleicao *eleicao, int *result);

void SalvaResultado(Eleicao *eleicao, int score, int *result);

void CalculaMaiorScore(Eleicao *eleicao, int *v, int start, int n);

void CalculaResultado(Eleicao *eleicao);

void KemenyYoung(int argc, char *argv[]);

#endif
