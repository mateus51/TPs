#include "video.h"

VideoChunk *NewVideoChunk(int video_id, int chunk_index, int size) {
	VideoChunk *chunk = (VideoChunk*) malloc(sizeof(VideoChunk));
	chunk->video_id  = video_id;
	chunk->index = chunk_index;
	chunk->size = size;
	chunk->popularidade = 1;
	return chunk;
}

void FreeVideo(Video *video) {
	if (video->localidade_espacial != NULL)
		free(video->localidade_espacial);
	free(video);
}
