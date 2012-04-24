#ifndef ESPACIAL_H
#define ESPACIAL_H

#include "lista.h"
#include "boolean.h"

void CalculaLocalidadeEspacial(Lista *videos, int video_id, int chunk_index);

void UpdateLocalidadeEspacial(Video *video, int chunk_index);

void AddNewVideo(Lista *videos, int video_id, int chunk_index);

void PrintEspacial(Lista *videos);

void WriteEspacialFile(Lista *videos);

#endif
