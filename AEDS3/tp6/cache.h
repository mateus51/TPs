#ifndef __CACHE_H__
#define __CACHE_H__

#include "lista.h"
#include "io.h"


#define MISS 0
#define HIT  1

#define FIFO   0
#define LRU    1
#define CUSTOM 2

typedef struct {
	int tamanho;
	int ocupacao;
	long long int soma_ocupacoes;
	int espaco_livre;
	int total_hits;
	int total_acessos;
	Lista *chunks;
} Cache;

Cache *NewCache(int tamanho);

void InsereChunk(Cache *cache, int video_id, int chunk_index, int chunk_size);

void RetiraChunk(Cache *cache);

int PesquisaCache(Cache *cache, int video_id, int chunk_index);

void SimulaCache(FILE *log);

void PrintFinalInfo(Cache *cache);

void FreeCache(Cache *cache);

#endif
