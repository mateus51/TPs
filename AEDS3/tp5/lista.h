#ifndef LISTA_H
#define LISTA_H

#include <stdlib.h>
#include <stdio.h>
#include "video.h"

typedef struct {
	VideoChunk *chunk;
	Video *video;
} Item;

typedef struct TipoCelula* Apontador;

typedef struct TipoCelula {
  Item *item;
  Apontador prox;
} Celula;

typedef struct {
  Apontador primeiro, ultimo;
} Lista;


Lista *NewLista();

int ListaVazia(Lista *lista);

void Insere(Lista *lista, Item *x);

void Retira(Apontador p, Lista *lista);

void SendToFirstPosition(Lista *lista, Apontador p);

void ImprimeLista(Lista *lista);

void FreeLista(Lista *lista);

void SortByVideoId(Lista *lista);

void SortByVideoIdAndChunkIndex(Lista *lista);

#endif
