#include "ligador.h"

void BuildMasterSymbolTable(TabelaDeSimbolos *tabela) {
	extern char **object_files;
	extern int total_object_files;
	char *line = (char*) calloc(LINE_MAX_SIZE, sizeof(char));
	char *simbolo = (char*) calloc(SYMBOL_MAX_SIZE, sizeof(char));
	int ILC, file_total_lines, total_lines = 0;
	FILE *file = NULL;
	int i;
	for (i = 0; i < total_object_files; i++) {

		file = fopen(object_files[i], "r");
		if (!file) {
			printf("Não foi possível ler o arquivo %s\n:(\n\n", object_files[i]);
			exit(EXIT_FAILURE);
		}

		fscanf(file, "%*s %d\n", &file_total_lines);

		//printf("\n\n%s total lines: %d\n", object_files[i], file_total_lines);

		line = fgets(line, LINE_MAX_SIZE, file);
		RemoveNewlineChar(line);

		while (strcmp(line, "#END_SYMBOL_TABLE")) {
			sscanf(line, "%s %d", simbolo, &ILC);
			AdicionaSimbolo(tabela, simbolo, ILC + total_lines);

			line = fgets(line, LINE_MAX_SIZE, file);
			RemoveNewlineChar(line);
		}

		total_lines += file_total_lines;
		fclose(file);
	}
	free(line);
	free(simbolo);
}

void LinkObjects(TabelaDeSimbolos *tabela) {
	extern char *output_file;
	extern char **object_files;
	extern int total_object_files;

	FILE *file = fopen(output_file, "w");
	if (!file) {
		printf("Não foi possível criar o arquivo %s\n\n:(\n", output_file);
		exit(EXIT_FAILURE);
	}

	//FILE *object = NULL;
	char *line = (char*) calloc(LINE_MAX_SIZE, sizeof(char));
	int operand, ILC = 0;

	int i;
	for (i = 0; i < total_object_files; i++) {

		FILE *object = fopen(object_files[i], "r");
		if (!object) {
			printf("Não foi possível ler o arquivo %s\n\n:(\n", object_files[i]);
			exit(EXIT_FAILURE);
		}

		//printf("\nProcessando %s...\n", object_files[i]);

		// Passando batido pela tabela de símbolos.
		do {
			fgets(line, LINE_MAX_SIZE, object);
			RemoveNewlineChar(line);
		} while (strcmp(line, "#END_SYMBOL_TABLE"));


		// Lendo o programa de verdade
		while (fgets(line, LINE_MAX_SIZE, object) != NULL) {
			RemoveNewlineChar(line);
			ILC++;

			// Se a linha for uma referência externa
			operand = atoi(line);
			if (operand == 0 && line[0] != '0') {
				operand = GetOperandFromSymbol(tabela, line, ILC);
			}
			fprintf(file, "%d\n", operand);
		}
		fclose(object);
	}
	free(line);
	fclose(file);
}

int GetOperandFromSymbol(TabelaDeSimbolos *tabela, char *token, int ILC) {
	//printf("  ILC: %d\n", ILC);
	int i;
	for (i = 0; i < tabela->total_simbolos; i++) {
		if (!strcmp(token, tabela->simbolos[i])) return tabela->ILC[i] - ILC - 1;
	}
	return 0;
}

void RemoveNewlineChar(char *string) {
	int size = strlen(string);
	if (string[size-1] == '\n') string[size-1] = '\0';
}
