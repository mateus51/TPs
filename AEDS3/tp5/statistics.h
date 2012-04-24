#ifndef STATISTICS_H
#define STATISTICS_H

#include <gsl/gsl_statistics_int.h>
#include <gsl/gsl_histogram.h>
#include <stdio.h>
#include <string.h>
#include "temporal.h"

void GenerateAllStatistics(PilhaTemporal *temporal, Lista *videos);

void GenerateStatistics(int *array, int size, char *title);

void GenerateStatisticsEspacial(Lista *videos);

void PlotHistogram(int *distancias, int array_size, int total_bins, int upper_limit, char *filename);

void GenerateCDF(int *array, int array_size, int total_bins);

void GenerateChartsVideos(Lista *videos);

void GenerateChartTemporal(int *distancias_de_pilha, int size);

void GenerateCDFTemporal(int *array, int array_size);

#endif
