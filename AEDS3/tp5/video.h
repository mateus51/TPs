#ifndef VIDEO_H
#define VIDEO_H

#include <stdlib.h>

typedef struct {
	int video_id;
	int index;
	int size;
	int popularidade;
} VideoChunk;

typedef struct {
	int id;
	int last_chunk_access;
	int *localidade_espacial;
	int array_size;
} Video;

VideoChunk *NewVideoChunk(int video_id, int chunk_index, int size);

void FreeVideo(Video *video);

#endif
