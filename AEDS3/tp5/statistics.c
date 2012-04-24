#include "statistics.h"

void GenerateAllStatistics(PilhaTemporal *temporal, Lista *videos) {
	GenerateStatistics(temporal->distancia_de_pilha, temporal->array_size, "Distâncias de Pilha");
	GenerateStatisticsEspacial(videos);
	GenerateCDFTemporal(temporal->distancia_de_pilha, temporal->array_size);
	GenerateChartsVideos(videos);
	GenerateChartTemporal(temporal->distancia_de_pilha, temporal->array_size);
	system("rm *.plot *.data");
}

void GenerateStatistics(int *array, int size, char *title) {
	double media = gsl_stats_int_mean(array, 1, size);
	double desvio_padrao = gsl_stats_int_sd_m(array, 1, size, media);
	double coef_var = desvio_padrao / media;
	FILE *file = fopen("estatisticas.txt", "a");
	if (file) {
		fprintf(file, "%s\n", title);
		fprintf(file, "  média:          %f\n", media);
		fprintf(file, "  desvio padrão:  %f\n", desvio_padrao);
		fprintf(file, "  coef. variação: %f\n\n", coef_var);
		fclose(file);
	}
}

void GenerateStatisticsEspacial(Lista *videos) {
	int total_itens = 0;
	char *string = (char*) calloc(50, sizeof(char));
	Apontador aux = videos->primeiro->prox;
	while (aux != NULL) {
		sprintf(string, "Localidade Espacial Video %d", aux->item->video->id);
		total_itens += aux->item->video->array_size;
		GenerateStatistics(aux->item->video->localidade_espacial, aux->item->video->array_size, string);
		aux = aux->prox;
	}
	free(string);

	int *espacial_acc = (int*) calloc(total_itens, sizeof(int));
	int *pointer = espacial_acc;
	aux = videos->primeiro->prox;
	while (aux != NULL) {
		memmove(pointer, aux->item->video->localidade_espacial, aux->item->video->array_size);
		pointer += aux->item->video->array_size;
		aux = aux->prox;
	}

	GenerateStatistics(espacial_acc, total_itens, "Localidade Espacial Todos os Vídeos");
	free(espacial_acc);
}

void PlotHistogram(int *distancias, int array_size, int total_bins, int upper_limit, char *filename) {
	gsl_histogram *histograma = gsl_histogram_alloc(total_bins);
	gsl_histogram_set_ranges_uniform (histograma, 0.0, (double) upper_limit);

	int i;
	for (i = 0; i < array_size; i++) {
		gsl_histogram_increment(histograma, distancias[i]);
	}

	FILE *grafico = fopen(filename, "w");
	if (!grafico) {
		printf("Não foi possível criar o arquivo 'grafico'\n");
	}
	else {
		for (i = 0; i < total_bins; i++) {
			fprintf(grafico, "%d %f\n", i, gsl_histogram_get(histograma, i));
		}
	}
	fclose(grafico);

	gsl_histogram_free(histograma);
}

void GenerateCDF(int *array, int array_size, int total_bins) {
	gsl_histogram *histograma = gsl_histogram_alloc(total_bins);
	gsl_histogram_set_ranges_uniform (histograma, 0.0, (double) total_bins);

	int i;
	for (i = 0; i < array_size; i++) {
		gsl_histogram_increment(histograma, array[i]);
	}

	double prob;
	int hist, total = 0;
	FILE *cdf = fopen("cdf.data", "w");
	if (!cdf) {
		printf("Não foi possível criar o arquivo 'cdf.plot'.\n");
	}
	else {
		for (i = 0; i < total_bins; i++) {
			hist = gsl_histogram_get(histograma, i);
			total += hist;
			prob = (double) total / (double) array_size;
			fprintf(cdf, "%f %f\n", (double) i, prob);
		}
	}
	fclose(cdf);
	gsl_histogram_free(histograma);
}

void GenerateChartsVideos(Lista *videos) {
	char *string = (char*) calloc(50, sizeof(char));
	Apontador aux = videos->primeiro->prox;
	while (aux != NULL) {
		PlotHistogram(aux->item->video->localidade_espacial, aux->item->video->array_size, 20, 20, "espacial.data");
		sprintf(string, "video%d_espacial.png", aux->item->video->id);
		FILE *file = fopen("espacial.plot", "w");
		fprintf(file, "set terminal png\n");
		fprintf(file, "set style fill solid 1.00 border -1\n");
		fprintf(file, "set style data histogram\n");
		fprintf(file, "set style histogram cluster gap 1\n");
		fprintf(file, "set xtics 2\n");
		fprintf(file, "set border 3\n");
		fprintf(file, "set nokey\n");
		fprintf(file, "set xtics nomirror\n");
		fprintf(file, "set ytics nomirror\n");
		fprintf(file, "set xrange [0:20]\n");
		fprintf(file, "set ylabel \"Frequência\"\n");
		fprintf(file, "set xlabel \"Distância Entre Chunks\"\n");
		fprintf(file, "set output \"%s\"\n", string);
		fprintf(file, "plot 'espacial.data' using 2 t \"D. Pilha\"\n");
		fclose(file);
		system("gnuplot espacial.plot");
		aux = aux->prox;
	}
	free(string);
}

void GenerateChartTemporal(int *distancias_de_pilha, int size) {
	PlotHistogram(distancias_de_pilha, size, 200, 200, "temporal.data");

	FILE *file = fopen("temporal.plot", "w");
	fprintf(file, "set terminal png\n");
	fprintf(file, "set style fill solid 1.00 noborder\n");
	fprintf(file, "set style data histogram\n");
	fprintf(file, "set style histogram cluster gap 20\n");
	fprintf(file, "set xtics 15\n");
	fprintf(file, "set border 3\n");
	fprintf(file, "set nokey\n");
	fprintf(file, "set xtics nomirror\n");
	fprintf(file, "set ytics nomirror\n");
	fprintf(file, "set xrange [0:200]\n");
	fprintf(file, "set ylabel \"Frequência\"\n");
	fprintf(file, "set xlabel \"Distâncias De Pilha\"\n");
	fprintf(file, "set output \"distancias_de_pilha.png\"\n");
	fprintf(file, "plot 'temporal.data' using 2 t \"D. Pilha\"\n");
	fclose(file);
	system("gnuplot temporal.plot");
}

void GenerateCDFTemporal(int *array, int array_size) {
	GenerateCDF(array, array_size, 200);
	FILE *file = fopen("cdf.plot", "w");
	fprintf(file, "set terminal png\n");
	fprintf(file, "set output \"cdf_temporal.png\"\n");
	fprintf(file, "set ylabel \"Probabilidade\"\n");
	fprintf(file, "set xlabel \"Distâncias De Pilha\"\n");
	fprintf(file, "set nokey\n");
	fprintf(file, "set grid\n");
	fprintf(file, "set border 3\n");
	fprintf(file, "set xtics nomirror\n");
	fprintf(file, "set ytics nomirror\n");
	fprintf(file, "plot 'cdf.data' with lines\n");
	fclose(file);
	system("gnuplot cdf.plot");
}
