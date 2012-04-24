#ifndef __LISTA_H__
#define __LISTA_H__

#include <stdlib.h>
#include <stdio.h>
#include "boolean.h"


typedef struct TipoCelula* Apontador;

typedef struct TipoCelula {
  Apontador prox;
  Apontador prev;
  int video_id;
  int chunk_index;
  int chunk_size;
  int total_acessos;
} Celula;

typedef struct {
  Apontador primeiro, ultimo;
} Lista;


Lista *NewLista();

int ListaVazia(Lista *lista);

void Insere(Lista *lista, Apontador p, int video_id, int chunk_index, int chunk_size);

int Retira(Lista *lista, Apontador p);

int RetiraUltimo(Lista *lista);

void SendToFirstPosition(Lista *lista, Apontador p);

void OrderByAcessos(Lista *lista);

void ImprimeLista(Lista *lista);

void RedoUltimoPointer(Lista *lista);

void FreeLista(Lista *lista);

#endif
