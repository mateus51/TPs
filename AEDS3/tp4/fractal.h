#ifndef FRACTAL_H
#define FRACTAL_H

#include "grafo.h"

void CheckIfIsFractal(Grafo *grafo);

boolean EhFractal(Grafo *grafo, int vertice_central, int *count);

int ProfundidadeFractal(int n, int total_grafos_roda);

int IsPowerOfThree(int n);

#endif
