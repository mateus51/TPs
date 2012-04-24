#ifndef TEMPORAL_H
#define TEMPORAL_H

#include <stdlib.h>
#include "boolean.h"
#include "lista.h"

typedef struct {
	Lista *lista_acessos;
	int *distancia_de_pilha;
	int array_size;
} PilhaTemporal;

PilhaTemporal *NewPilhaTemporal();

void CalculaDistanciasDePilha(PilhaTemporal *temporal, int video_id, int chunk_index, int size);

void AddDistanciaDePilha(PilhaTemporal *temporal, int dist);

void AddNewChunk(PilhaTemporal *temporal, int video_id, int chunk_index, int size);

void PrintTemporal(PilhaTemporal *temporal);

void FreePilhaTemporal(PilhaTemporal *temporal);

void WriteTemporalFile(PilhaTemporal *temporal);

void WritePopularidadeFile(Lista *chunks);;

#endif
