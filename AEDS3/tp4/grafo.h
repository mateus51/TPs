#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "boolean.h"

typedef struct {
  int **adj;
  int *graus;
  int total_vertices;
  //int vertice_maior_grau;
  //int vertice_menor_grau;
} Grafo;

#define LINE_MAX_SIZE 2501



Grafo *NewGraph(int total_vertices);

Grafo *ReadGraphFromFile(FILE *file);

void FreeGraph(Grafo *grafo);

void InsereAresta(Grafo *grafo, int v1, int v2);

void RetiraAresta(Grafo *grafo, int v1, int v2);

boolean ExisteAresta(Grafo *grafo, int v1, int v2);

int PrimeiroAdj(Grafo *grafo, int v1);

int ProxAdj (Grafo *grafo, int currentAdj, int v1);

int *ListaAdj(Grafo *grafo, int v1);

int NumVerticesGrauN(Grafo *grafo, int n);

int TotalGraus(Grafo *grafo);

int VerticeMaiorGrau(Grafo *grafo);

int VerticeGrauIntermediario(Grafo *grafo);

boolean EhGrafoRoda(Grafo *grafo, int vertice_central);

void DesfazRoda(Grafo *grafo, int vertice_central);

Grafo *ConstroiSubgrafoCiclo(Grafo *grafo, int vertice_central);

boolean EhCiclo(Grafo *grafo);

void PrintGraph(Grafo *grafo);

void RemoveNewlineChar(char *string);

#endif
