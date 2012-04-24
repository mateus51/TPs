#include "espacial.h"

void CalculaLocalidadeEspacial(Lista *videos, int video_id, int chunk_index) {
	boolean achou = FALSE;

	Apontador aux = videos->primeiro;
	while (aux->prox != NULL) {
		if (aux->prox->item->video->id == video_id) {
			achou = TRUE;
			UpdateLocalidadeEspacial(aux->prox->item->video, chunk_index);
			break;
		}

		aux = aux->prox;
	}

	if (!achou) {
		AddNewVideo(videos, video_id, chunk_index);
	}
}

void UpdateLocalidadeEspacial(Video *video, int chunk_index) {
	video->array_size++;
	video->localidade_espacial = (int*) realloc(video->localidade_espacial, sizeof(int) * video->array_size);
	int diferenca = video->last_chunk_access - chunk_index;
	if (diferenca < 0) diferenca = chunk_index - video->last_chunk_access;
	video->localidade_espacial[video->array_size - 1] = diferenca;
	video->last_chunk_access = chunk_index;
}

void AddNewVideo(Lista *videos, int video_id, int chunk_index) {
	Item *item = (Item*) malloc(sizeof(Item));
	item->video = (Video*) malloc(sizeof(Video));
	item->video->id = video_id;
	item->video->last_chunk_access = chunk_index;
	item->video->localidade_espacial = NULL;
	item->video->array_size = 0;
	item->chunk = NULL;
	Insere(videos, item);
}

void PrintEspacial(Lista *videos) {
	int i;
	Apontador aux = videos->primeiro->prox;
	while (aux != NULL) {
		printf("Vídeo %d: ", aux->item->video->id);
		for (i = 0; i < aux->item->video->array_size; i++) {
			printf("%3d", aux->item->video->localidade_espacial[i]);
		}
		printf("\n");

		aux = aux->prox;
	}
}

void WriteEspacialFile(Lista *videos) {
	FILE *localidade_espacial = fopen("localidadeespacial.txt", "w");
	if (!localidade_espacial) {
		printf("Não foi possível criar o arquivo localidadeespacial.txt\n");
	}
	else {
		int i;
		Apontador aux = videos->primeiro->prox;
		while (aux != NULL) {
			for (i = 0; i < aux->item->video->array_size - 1; i++) {
				fprintf(localidade_espacial, "%d,", aux->item->video->localidade_espacial[i]);
			}
			fprintf(localidade_espacial, "%d", aux->item->video->localidade_espacial[i]);
			if (aux->prox != NULL) {
				fprintf(localidade_espacial, ",");
			}
			aux = aux->prox;
		}
		fclose(localidade_espacial);
	}
}
