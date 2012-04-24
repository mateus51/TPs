#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"

#define TRUE 1
#define FALSE 0

typedef struct {
	int total_chr_lidos;
	int total_voltas;
	int encontrou_padrao;
} Resultado;

Resultado KMP(char *search_string, FILE *file) {
	int estado_atual, total_chr_lidos, fim_chars;
	int search_string_size = strlen(search_string);
	char chr;
	Resultado resultado;
	resultado.total_voltas = 0;
	resultado.total_chr_lidos = 0;
	resultado.encontrou_padrao = FALSE;
	int automato[] = {-1, 0};
	estado_atual = total_chr_lidos = 0;
	while ((chr = fgetc(file)) != EOF) {
		fim_chars = FALSE;
		if(estado_atual > 0 && search_string[estado_atual] != chr) resultado.total_voltas++;
		while (estado_atual > -1 && search_string[estado_atual] != chr){
			estado_atual = automato[estado_atual];
		}
		estado_atual++;
		resultado.total_chr_lidos++;
		if (estado_atual >= search_string_size) {
			printf("%d\n", resultado.total_chr_lidos - estado_atual + 1);
			estado_atual = automato[estado_atual];
			resultado.total_voltas++;
			fim_chars = TRUE;
			resultado.encontrou_padrao = TRUE;
		}
	}
	if(fim_chars) resultado.total_voltas--;
	return resultado;
}

int main(int argc, char *argv[]){
	char *search_string = "1";
	char *filename = ParseParams(argc, argv);
	FILE *file = NULL;
	if((file = fopen(filename, "r")) == NULL){
		printf("Não foi possível abrir o arquivo '%s'\nSaindo do programa...\n", filename);
		exit(EXIT_FAILURE);	}
	printf("Padrão %s encontrado em:\n", search_string);
	Resultado resultado = KMP(search_string, file);
	if(!resultado.encontrou_padrao) printf("\n");
	printf("%d caracteres lidos.\n", resultado.total_chr_lidos);
	char *estado_string = resultado.total_voltas == 1 ? "estado" : "estados";
	printf("Voltou %d %s no total.\n", resultado.total_voltas, estado_string);
	return 0;
}
