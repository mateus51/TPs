#include "expansor.h"

extern char verbose;

Macro **LeMacros(FILE *file) {
	Macro **macros = NULL;
	char *line = (char*) calloc(LINE_MAX_SIZE, sizeof(char));
	int counter = 0;
	boolean reading_macro = FALSE;

	while ((line = fgets(line, LINE_MAX_SIZE, file)) != NULL) {
		RemoveNewlineChar(line);
		RemoveCommentFromLine(line);

		if (verbose)
			printf("%s\n", line);

		// Se ler a pseudo-instrução END, para a leitura
		if (!strcmp(line, "END")) {
			macros = AppendNullPointer(macros, counter);
			free(line);
			return macros;
		}

		// Só processa a linha se ela não estiver em branco
		if (strlen(line)) {

			// Se estiver lendo uma definição de macro
			if (reading_macro) {

				// Se não for a pseudo-instrução ENDMACRO
				if (strcmp(line, "ENDMACRO")) {
					AddInstruction(macros[counter-1], line);
				}
				else {
					reading_macro = FALSE;
				}
			}

			else {
				char *token = strtok(line, " ");

				// Se o primeiro token da linha for um label
				char *dois_pontos = strchr(token, ':');
				if (dois_pontos != NULL) {
					token = strtok(NULL, " ");

					// se for uma definição de macro
					if (!strcmp(token, "BEGINMACRO")) {
						reading_macro = TRUE;
						*dois_pontos = '\0';
						counter++;
						macros = (Macro**) realloc(macros, sizeof(Macro*) * counter);
						token = strtok(NULL, " ");
						macros[counter-1] = NewMacro(line, token);
					}
				}
			}
		}
	}

	macros = AppendNullPointer(macros, counter);
	free(line);
	return macros;
}

void WriteFile(FILE *file, Macro **macros) {
	extern char *output_file;
	FILE *output = fopen(output_file, "w");
	if (output == NULL) {
		printf("Não foi possível criar o arquivo %s   :(\n", output_file);
		exit(EXIT_FAILURE);
	}

	char *line = (char*) calloc(LINE_MAX_SIZE, sizeof(char));
	char *line_bkp = (char*) calloc(LINE_MAX_SIZE, sizeof(char));
	boolean reading_macro = FALSE;
	char *dois_pontos;
	int index;

	while ((line = fgets(line, LINE_MAX_SIZE, file)) != NULL) {
		RemoveNewlineChar(line);
		strcpy(line_bkp, line);
		RemoveCommentFromLine(line);

		// Só processa a linha se ela não estiver em branco
		if (strlen(line)) {

			char *token = strtok(line, " ");

			// Se ler a pseudo-instrução END, pára a leitura
			if (!strcmp(token, "END")) {
				fprintf(output, "END");
				free(line);
				free(line_bkp);
				fclose(output);
				return;
			}

			// Se não estiver em uma definição de macro
			if (!reading_macro) {

				// Se o primeiro token da linha for um label, passa para o próximo
				dois_pontos = strchr(token, ':');
				if (dois_pontos != NULL) {
					token = strtok(NULL, " ");
				}

				index = IsMacro(macros, token);

				// se for uma definição de macro
				if (!strcmp(token, "BEGINMACRO")) {
					reading_macro = TRUE;
				}

				// se for uma chamada de macro
				else if (index != -1) {

					// se tiver um label, mantem o label
					if (strcmp(line, token))
						fprintf(output, "%s ", line);

					token = strtok(NULL, " ");
					ExpandMacro(macros, index, output, token);
				}

				// é uma instrução normal
				else {
					fprintf(output, "%s\n", line_bkp);
				}
			}

			// Se estiver em uma definição de macro
			else {
				if (!strcmp(line, "ENDMACRO")) {
					reading_macro = FALSE;
				}
			}
		}
	}

	free(line);
	free(line_bkp);
	fclose(output);
}

Macro **AppendNullPointer(Macro **macros, int counter) {
	macros = (Macro**) realloc(macros, sizeof(Macro*) * (counter + 1));
	macros[counter] = NULL;
	return macros;
}

void RemoveNewlineChar(char *string) {
	int size = strlen(string);
	if (string[size-1] == '\n') string[size-1] = '\0';
}

void RemoveCommentFromLine(char *string) {
	char *ponto_e_virgula = strchr(string, ';');
	if (ponto_e_virgula != NULL)
		*ponto_e_virgula = '\0';
}
