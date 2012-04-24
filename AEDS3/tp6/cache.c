#include "cache.h"

Cache *NewCache(int tamanho) {
	Cache *cache = (Cache*) malloc(sizeof(Cache));
	cache->tamanho = tamanho;
	cache->espaco_livre = tamanho;
	cache->ocupacao = 0;
	cache->soma_ocupacoes = 0;
	cache->total_acessos = 0;
	cache->total_hits = 0;
	cache->chunks = NewLista();
	return cache;
}

void InsereChunk(Cache *cache, int video_id, int chunk_index, int chunk_size) {
	extern int estrategia;

	// abrindo espaço na cache
	while (cache->espaco_livre < chunk_size) {
		RetiraChunk(cache);
	}

	// insere novo chunk na cache de acordo com a estratégia utilizada
	switch (estrategia) {
		case FIFO:
			Insere(cache->chunks, cache->chunks->ultimo, video_id, chunk_index, chunk_size);
			break;

		case LRU:
			Insere(cache->chunks, cache->chunks->primeiro, video_id, chunk_index, chunk_size);
			break;

		case CUSTOM:
			Insere(cache->chunks, cache->chunks->primeiro, video_id, chunk_index, chunk_size);
			break;
	}

	cache->espaco_livre -= chunk_size;
	cache->ocupacao += chunk_size;
}

void RetiraChunk(Cache *cache) {
	extern int estrategia;
	int freed_size;

	switch (estrategia) {
		case FIFO:
			freed_size = Retira(cache->chunks, cache->chunks->primeiro);
			break;

		case LRU:
			freed_size = RetiraUltimo(cache->chunks);
			break;

		case CUSTOM:
			OrderByAcessos(cache->chunks);
			freed_size = Retira(cache->chunks, cache->chunks->primeiro);
			break;
	}

	cache->espaco_livre += freed_size;
	cache->ocupacao -= freed_size;

}

int PesquisaCache(Cache *cache, int video_id, int chunk_index) {
	Apontador aux = cache->chunks->primeiro;
	extern int estrategia;
	while (aux->prox != NULL) {
		if (aux->prox->video_id == video_id && aux->prox->chunk_index == chunk_index) {

			switch (estrategia) {
				case LRU:
					SendToFirstPosition(cache->chunks, aux);
					break;
				case CUSTOM:
					aux->prox->total_acessos++;
					break;
			}

			return HIT;
		}
		aux = aux->prox;
	}
	return MISS;
}

void SimulaCache(FILE *log) {
	int video_id, chunk_index, chunk_size, result;
	extern int cache_size;
	Cache *cache = NewCache(cache_size);
	char *line = (char*) calloc(LINE_MAX_SIZE, sizeof(char));

	while (fgets(line, LINE_MAX_SIZE, log) != NULL) {
		RemoveNewlineChar(line);

		cache->total_acessos++;

		sscanf(line, "%d %d %d", &video_id, &chunk_index, &chunk_size);
		printf("%d %d %d ", video_id, chunk_index, chunk_size);
		result = PesquisaCache(cache, video_id, chunk_index);
		printf("%d ", result);

		switch (result) {
			case HIT:
				cache->total_hits++;
				break;

			case MISS:
				InsereChunk(cache, video_id, chunk_index, chunk_size);
				break;
		}

		cache->soma_ocupacoes += cache->ocupacao;

		printf("%d\n", cache->ocupacao);

	}

	PrintFinalInfo(cache);

	free(line);
	FreeCache(cache);
}

void PrintFinalInfo(Cache *cache) {
	double porcentagem_acertos = ((double) cache->total_hits / (double) cache->total_acessos) * 100;
	double media_ocupacao = (double) cache->soma_ocupacoes / (double) cache->total_acessos;
	double porcentagem_media_ocupacao = (media_ocupacao / (double) cache->tamanho) * 100;
	double ganho_da_cache = (porcentagem_acertos + porcentagem_media_ocupacao) / 2;
	printf("%.2f %.2f %.2f\n", porcentagem_acertos, porcentagem_media_ocupacao, ganho_da_cache);
}

void FreeCache(Cache *cache) {
	FreeLista(cache->chunks);
	free(cache);
}
