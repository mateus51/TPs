#include "macro.h"

// Cria uma nova macro. Recebe o argumento da macro como argumento.
// Se a macro não tiver argumentos, deve ser passado NULL.
Macro *NewMacro(char *name, char *arg) {
	Macro *macro = (Macro*) malloc(sizeof(Macro));
	macro->instructions = NULL;
	macro->total_instructions = 0;
	macro->name = (char*) calloc(strlen(name) + 1, sizeof(char));
	strcpy(macro->name, name);
	if (arg != NULL) {
		macro->arg = (char*) calloc(strlen(arg) + 1, sizeof(char));
		strcpy(macro->arg, arg);
	}
	else {
		macro->arg = NULL;
	}

	return macro;
}

void ExpandMacro(Macro **macros, int index, FILE *file, char *arg) {
	int i, index2;
	char *instruction_bkp = (char*) calloc(LINE_MAX_SIZE, sizeof(char));
	char *dois_pontos;

	for (i = 0; i < macros[index]->total_instructions; i++) {
		strcpy(instruction_bkp, macros[index]->instructions[i]);
		char *token = strtok(instruction_bkp, " ");

		// Se o primeiro token da instrucao for um label, passa para o próximo
		dois_pontos = strchr(token, ':');
		if (dois_pontos != NULL) {
			token = strtok(NULL, " ");
		}

		// se a instrução é uma chamada de macro
		if ((index2 = IsMacro(macros, token)) != -1) {

			// se tiver um label, mantem o label
			if (strcmp(instruction_bkp, token))
				fprintf(file, "%s ", instruction_bkp);

			token = strtok(NULL, " ");
			ExpandMacro(macros, index2, file, token);
		}

		// se a macro não possuir argumento
		else if (macros[index]->arg == NULL) {
			fprintf(file, "%s\n", macros[index]->instructions[i]);
		}

		else {
			// se tiver um label, mantem o label
			if (strcmp(instruction_bkp, token))
				fprintf(file, "%s ", instruction_bkp);


			fprintf(file, "%s", token);
			token = strtok(NULL, " ");

			// se a instrucao tiver um argumento
			if (token != NULL) {
				// se o argumento da instrucao for o da macro
				if (!strcmp(token, macros[index]->arg)) {
					fprintf(file, " %s\n", arg);
				}
				else {
					fprintf(file, " %s\n", token);
				}
			}
			else {
				fprintf(file, "\n");
			}

		}
	}
	free(instruction_bkp);
}

// Verifica se uma instrução é uma macro
int IsMacro(Macro **macros, char *token) {
	int i;
	for (i = 0; macros[i] != NULL; i++) {
		if (!strcmp(token, macros[i]->name)) return i;
	}
	return -1;
}

void FreeMacro(Macro *macro) {
	int i;
	for (i = 0; i < macro->total_instructions; i++)
		free(macro->instructions[i]);
	free(macro->instructions);
	free(macro->name);
	if (macro->arg != NULL) free(macro->arg);
	free(macro);
}

void FreeArrayMacros(Macro **macros) {
	int i;
	for (i = 0; macros[i] != NULL; i++)
		FreeMacro(macros[i]);

	free(macros);
}

void PrintMacro(Macro *macro) {
	printf("%s(", macro->name);
	if (macro->arg != NULL) {
		printf("%s)\n", macro->arg);
	}
	else {
		printf(")\n");
	}
	int i;
	for (i = 0; i < macro->total_instructions; i++) {
		printf("  %s\n", macro->instructions[i]);
	}
	printf("\n");
}

void AddInstruction(Macro *macro, char *instruction) {
	macro->total_instructions++;
	macro->instructions = (char**) realloc(macro->instructions, sizeof(char*) * macro->total_instructions);
	macro->instructions[macro->total_instructions - 1] = (char*) calloc(strlen(instruction) + 1, sizeof(char));
	strcpy(macro->instructions[macro->total_instructions - 1], instruction);
}
