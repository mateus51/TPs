#include "lista.h"

Lista *NewLista() {
	Lista *lista = (Lista*) malloc(sizeof(Lista));
	lista->primeiro = (Apontador) malloc(sizeof(Celula));
	lista->ultimo = lista->primeiro;
	lista->primeiro->prox = NULL;
	return lista;
}

int ListaVazia(Lista *lista) {
	return (lista->primeiro == lista->ultimo);
}

// insere o item na primeira posição da lista
void Insere(Lista *lista, Item *x) {
	Apontador aux = lista->primeiro->prox;
	lista->primeiro->prox = (Apontador) malloc(sizeof(Celula));
	lista->primeiro->prox->item = x;
	lista->primeiro->prox->prox = aux;
	if (ListaVazia(lista)) lista->ultimo = lista->primeiro->prox;
}

//o item a ser retirado é seguinte ao apontado por p
void Retira(Apontador p, Lista *lista) {
	  if (ListaVazia(lista) || p == NULL || p->prox == NULL) {
		  printf("Bug na lista!   :(\n");
		  return;
	  }
	  Apontador q = p->prox;
	  p->prox = q->prox;
	  if (p->prox == NULL) lista->ultimo = p;
	  if (q->item->chunk != NULL)
		  free(q->item->chunk);
	  if (q->item->video != NULL)
		  FreeVideo(q->item->video);
	  free(q->item);
	  free(q);
}

// Coloca o item seguinte ao apontado por p na primeira
// posição da lista
void SendToFirstPosition(Lista *lista, Apontador p) {
	if (ListaVazia(lista) || p == NULL || p->prox == NULL) {
		printf("Erro ao enviar para o topo da lista!\n");
		if (ListaVazia(lista)) printf(" lista vazia!\n\n");
		else if (p == NULL) printf(" p == NULL!\n\n");
		else if (p->prox == NULL) printf(" p->prox == NULL\n\n");
		else printf(" ???\n\n");
		return;
	}

	Apontador aux = p->prox;
	p->prox = aux->prox;
	aux->prox = lista->primeiro->prox;
	lista->primeiro->prox = aux;
	if (lista->ultimo == aux) lista->ultimo = p;
}

void ImprimeLista(Lista *lista) {
	Apontador aux = lista->primeiro->prox;

	while (aux != NULL) {
		printf("%d/%d  ", aux->item->chunk->video_id, aux->item->chunk->index);
		aux = aux->prox;
	}
	printf("\n");

}

void FreeLista(Lista *lista) {
	Apontador aux = lista->primeiro;
	while (!ListaVazia(lista)) {
		Retira(aux, lista);
	}
	free(lista->primeiro);
	free(lista);
}

// Ordena a lista de acordo com o video_id
// Só para listas com Video* != NULL
void SortByVideoId(Lista *lista) {
	Apontador menor, aux, cabeca = lista->primeiro;
	int menor_id;
	while (lista->primeiro->prox != NULL) {
		menor_id = 999999;
		aux = lista->primeiro;
		while (aux->prox != NULL) {
			if (aux->prox->item->video->id < menor_id) {
				menor_id = aux->prox->item->video->id;
				menor = aux;
			}
			aux = aux->prox;
		}
		SendToFirstPosition(lista, menor);
		lista->primeiro = lista->primeiro->prox;
	}
	lista->primeiro = cabeca;
}

// Ordena a lista de acordo com o video_id e o chunk_index
// Só para listas com VideoChunk* != NULL
void SortByVideoIdAndChunkIndex(Lista *lista) {
	Apontador menor, aux, cabeca = lista->primeiro;
	int menor_video, menor_chunk;
	while (lista->primeiro->prox != NULL) {
		menor_video = 999999;
		aux = lista->primeiro;
		while (aux->prox != NULL) {
			if (aux->prox->item->chunk->video_id < menor_video) {
				menor_chunk = aux->prox->item->chunk->index;
				menor_video = aux->prox->item->chunk->video_id;
				menor = aux;
			}
			else if (aux->prox->item->chunk->video_id == menor_video) {
				if (aux->prox->item->chunk->index < menor_chunk) {
					menor_chunk = aux->prox->item->chunk->index;
					menor = aux;
				}
			}
			aux = aux->prox;
		}
		SendToFirstPosition(lista, menor);
		lista->primeiro = lista->primeiro->prox;
	}
	lista->primeiro = cabeca;
}
