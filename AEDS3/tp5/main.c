#include <string.h>
#include "io.h"
#include "temporal.h"
#include "espacial.h"

#ifdef __GENERATE_STATS__
	#include "statistics.h"
#endif

int main (int argc, char *argv[]) {

	int video_id, chunk_index, size;
	PilhaTemporal *temporal = NewPilhaTemporal();
	Lista *videos = NewLista();

	FILE *file = ParseParams(argc, argv);

	while (!feof(file)) {
		fscanf(file, "%d %d %d\n", &video_id, &chunk_index, &size);
		CalculaDistanciasDePilha(temporal, video_id, chunk_index, size);
		CalculaLocalidadeEspacial(videos, video_id, chunk_index);
	}

	fclose(file);





	int soma = 0;
	Apontador aux = temporal->lista_acessos->primeiro;
	while (aux->prox != NULL) {
		soma += aux->prox->item->chunk->size;
		aux = aux->prox;
	}
	printf("soma dos tamanhos: %d\n", soma);















	WriteTemporalFile(temporal);

	SortByVideoId(videos);
	WriteEspacialFile(videos);

	SortByVideoIdAndChunkIndex(temporal->lista_acessos);
	WritePopularidadeFile(temporal->lista_acessos);

#ifdef __GENERATE_STATS__
		GenerateAllStatistics(temporal, videos);
#endif

	FreePilhaTemporal(temporal);
	FreeLista(videos);

	return EXIT_SUCCESS;
}
