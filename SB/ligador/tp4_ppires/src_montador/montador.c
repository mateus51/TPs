#include "montador.h"

TabelaDeSimbolos *ConstroiTabelaDeSimbolos(FILE *file) {
	TabelaDeSimbolos *tabela = (TabelaDeSimbolos*) malloc(sizeof(TabelaDeSimbolos));
	tabela->ILC = NULL;
	tabela->simbolos = NULL;
	tabela->total_simbolos = 0;
	tabela->total_linhas = 0;

	int ILC = 0;

	char *line = (char*) calloc(LINE_MAX_SIZE, sizeof(char));
	char *line_bkp = (char*) calloc(LINE_MAX_SIZE, sizeof(char));

	while ((line = fgets(line, LINE_MAX_SIZE, file)) != NULL) {
		RemoveNewlineChar(line);
		RemoveCommentFromLine(line);

		if (!strcmp(line, "END")) {
			tabela->total_linhas = ILC;
			free(line);
			free(line_bkp);
			return tabela;
		}

		// Só processa a linha se ela não estiver em branco
		if (strlen(line)) {

			strcpy(line_bkp, line);
			ILC += 2;
			char *token = strtok(line, " ");

			// Se o primeiro token da linha for um label
			char *dois_pontos = strchr(token, ':');
			if (dois_pontos != NULL) {
				*dois_pontos = '\0';
				AdicionaSimbolo(tabela, token, ILC-1);

				char *inst_token = strtok(line_bkp, " ");
				inst_token = strtok(NULL, " ");

				if (!strcmp(inst_token, "RET") || !strcmp(inst_token, "HALT") || !strcmp(inst_token, "WORD"))
					ILC--;
			}

			// Se não for label, só corrige o ILC, caso necessário
			else {
				if (!strcmp(token, "RET") || !strcmp(token, "HALT") || !strcmp(token, "WORD"))
					ILC--;
			}
		}
	}

	free(line);
	free(line_bkp);
	return tabela;
}

void AdicionaSimbolo(TabelaDeSimbolos *tabela, char *simbolo, int ILC) {
	tabela->total_simbolos++;

	tabela->ILC = (int*) realloc(tabela->ILC, sizeof(int) * tabela->total_simbolos);

	tabela->simbolos = (char**) realloc(tabela->simbolos, sizeof(char*) * tabela->total_simbolos);
	tabela->simbolos[tabela->total_simbolos - 1] = (char*) calloc(strlen(simbolo) + 1, sizeof(char));

	tabela->ILC[tabela->total_simbolos - 1] = ILC;
	strcpy(tabela->simbolos[tabela->total_simbolos - 1], simbolo);
}

void TraduzPrograma(FILE *file, TabelaDeSimbolos *tabela) {

	FILE *prog = OutputFileWithSymbolTable(tabela);

	int opcode, operand, ILC = 0;
	char *line = (char*) calloc(LINE_MAX_SIZE, sizeof(char));

	while ((line = fgets(line, LINE_MAX_SIZE, file)) != NULL) {
		RemoveNewlineChar(line);
		RemoveCommentFromLine(line);

		if (!strcmp(line, "END")) {
			free(line);
			fclose(prog);
			return;
		}

		if (strlen(line)) {
			ILC += 2;
			char *token = strtok(line, " ");

			// Se o primeiro token for um label, passa para o próximo token
			if (strchr(token, ':') != NULL) {
				token = strtok(NULL, " ");
			}

			// Se for a pseudo-instrução WORD
			if (!strcmp(token, "WORD")) {
				ILC--;
				token = strtok(NULL, " ");

				operand = atoi(token);
				fprintf(prog, "%d\n", operand);
			}

			// Se for uma instrução normal
			else {

				opcode = GetOpcodeFromToken(token);
				fprintf(prog, "%d\n", opcode);

				if (opcode != HALT && opcode != RET) {
					token = strtok(NULL, " ");

					operand = atoi(token);

					// Se operando for uma palavra, olha na tabela de símbolos
					if (strcmp(token, "0") && operand == 0) {
						operand = GetOperandFromSymbol(tabela, token, ILC);
						if (operand == 0) {
							fprintf(prog, "%s\n", token);
						}
						else {
							fprintf(prog, "%d\n", operand);
						}
					}
					else {
						fprintf(prog, "%d\n", operand);
					}
				}
				else {
					ILC--;
				}
			}
		}
	}
	free(line);
	fclose(prog);
}

FILE *OutputFileWithSymbolTable(TabelaDeSimbolos *tabela) {
	extern char *exec_name;
	FILE *file = fopen(exec_name, "w");
	if (!file) {
		printf("Não foi possível criar o arquivo %s\n", exec_name);
		exit(EXIT_FAILURE);
	}

	fprintf(file, "#TOTAL_LINES %d\n", tabela->total_linhas);

	int i;
	for (i = 0; i < tabela->total_simbolos; i++) {
		fprintf(file, "%s %d\n", tabela->simbolos[i], tabela->ILC[i]);
	}
	fprintf(file, "#END_SYMBOL_TABLE\n");

	return file;
}

int GetOpcodeFromToken(char *token) {
	if      (!strcmp(token, "LOAD"))  return LOAD;
	else if (!strcmp(token, "STORE")) return STORE;
	else if (!strcmp(token, "JMP"))   return JMP;
	else if (!strcmp(token, "JPG"))   return JPG;
	else if (!strcmp(token, "JPE"))   return JPE;
	else if (!strcmp(token, "JPL"))   return JPL;
	else if (!strcmp(token, "JPNE"))  return JPNE;
	else if (!strcmp(token, "PUSH"))  return PUSH;
	else if (!strcmp(token, "POP"))   return POP;
	else if (!strcmp(token, "READ"))  return READ;
	else if (!strcmp(token, "WRITE")) return WRITE;
	else if (!strcmp(token, "CALL"))  return CALL;
	else if (!strcmp(token, "RET"))   return RET;
	else if (!strcmp(token, "ADD"))   return ADD;
	else if (!strcmp(token, "SUB"))   return SUB;
	else if (!strcmp(token, "XOR"))   return XOR;
	else if (!strcmp(token, "AND"))   return AND;
	else if (!strcmp(token, "OR"))    return OR;
	else if (!strcmp(token, "HALT"))  return HALT;
	else return 0;
}

int GetOperandFromSymbol(TabelaDeSimbolos *tabela, char *token, int ILC) {
	//printf("  ILC: %d\n", ILC);
	int i;
	for (i = 0; i < tabela->total_simbolos; i++) {
		if (!strcmp(token, tabela->simbolos[i])) return tabela->ILC[i] - ILC - 1;
	}
	return 0;
}

void ImprimeTabela(TabelaDeSimbolos *tabela) {
	//printf("imprimindo...\n");
	int i;
	for (i = 0; i < tabela->total_simbolos; i++) {
		printf(" %s %5d\n", tabela->simbolos[i], tabela->ILC[i]);
	}
}

void FreeTabela(TabelaDeSimbolos *tabela) {
	int i;
	for (i = 0; i < tabela->total_simbolos; i++)
		free(tabela->simbolos[i]);

	free(tabela->simbolos);
	free(tabela->ILC);
	free(tabela);
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
