#include "temporal.h"

PilhaTemporal *NewPilhaTemporal() {
	PilhaTemporal *temporal = (PilhaTemporal*) malloc(sizeof(PilhaTemporal));
	temporal->array_size = 0;
	temporal->lista_acessos = NewLista();
	temporal->distancia_de_pilha = NULL;
	return temporal;
}

void CalculaDistanciasDePilha(PilhaTemporal *temporal, int video_id, int chunk_index, int size) {
	boolean achou = FALSE;
	int counter = 0;
	Apontador aux = temporal->lista_acessos->primeiro;
	while (aux->prox != NULL) {

		if (aux->prox->item->chunk->video_id == video_id) {
			if (aux->prox->item->chunk->index == chunk_index) {
				aux->prox->item->chunk->popularidade++;
				SendToFirstPosition(temporal->lista_acessos, aux);
				AddDistanciaDePilha(temporal, counter);
				achou = TRUE;
				break;
			}
		}

		counter++;
		aux = aux->prox;
	}
	if (!achou) {
		AddNewChunk(temporal, video_id, chunk_index, size);
	}
}

void AddDistanciaDePilha(PilhaTemporal *temporal, int dist) {
	temporal->array_size++;
	temporal->distancia_de_pilha = (int*) realloc(temporal->distancia_de_pilha, sizeof(int) * temporal->array_size);
	temporal->distancia_de_pilha[temporal->array_size - 1] = dist;
}

void AddNewChunk(PilhaTemporal *temporal, int video_id, int chunk_index, int size) {
	Item *item = (Item*) malloc(sizeof(Item));
	item->chunk = NewVideoChunk(video_id, chunk_index, size);
	item->video = NULL;
	Insere(temporal->lista_acessos, item);
}

void PrintTemporal(PilhaTemporal *temporal) {
	printf("total de elementos: %d\n", temporal->array_size);
	int i;
	for (i = 0; i < temporal->array_size; i++) {
		printf("    %d\n", temporal->distancia_de_pilha[i]);
	}
}

void FreePilhaTemporal(PilhaTemporal *temporal) {
	FreeLista(temporal->lista_acessos);
	free(temporal->distancia_de_pilha);
	free(temporal);
}

void WriteTemporalFile(PilhaTemporal *temporal) {
	FILE *localidade_temporal = fopen("localidadetemporal.txt", "w");
	if (!localidade_temporal) {
		printf("Não foi possível criar o arquivo localidadetemporal.txt\n");
	}
	else {
		int i;
		for (i = 0; i < temporal->array_size - 1; i++) {
			fprintf(localidade_temporal, "%d,", temporal->distancia_de_pilha[i]);
		}
		fprintf(localidade_temporal, "%d", temporal->distancia_de_pilha[i]);
		fclose(localidade_temporal);
	}
}

void WritePopularidadeFile(Lista *chunks) {
	FILE *popularidade = fopen("popularidade.txt", "w");
	if (!popularidade) {
		printf("Não foi possível ciar o arquivo popularidade.txt\n");
	}
	else {
		Apontador aux = chunks->primeiro->prox;
		while (aux != NULL) {
			fprintf(popularidade, "%d,%d,%d\n", aux->item->chunk->video_id, aux->item->chunk->index, aux->item->chunk->popularidade);
			aux = aux->prox;
		}
	}
	fclose(popularidade);
}
