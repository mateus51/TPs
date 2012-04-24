#include "automata_constructor.h"

int* preKMP(char *search_string){
   int i, j;
   int string_size = strlen(search_string);
   int *automato = (int*) malloc(sizeof(int) * (string_size + 1));

   i = 0;
   j = -1;
   automato[0] = -1;

   while (i < string_size) {
      while (j > -1 && search_string[i] != search_string[j]){
    	  j = automato[j];
      }
      i++;
      j++;
      if (search_string[i] == search_string[j]){
    	  automato[i] = automato[j];
      }
      else {
    	  automato[i] = j;
      }
   }
   return automato;
}

void WriteFile(int argc, char *argv[]){
	char *search_string = ParseParams(argc, argv);
	int *KmpNext = preKMP(search_string);

	int size = strlen(search_string) + 1;
	int i;

	FILE *file = fopen("tp1-2.c", "w");
	if(!file){
		printf("Não foi possível criar o arquivo 'tp1-2.c'.\nSaindo do programa...\n");
		exit(EXIT_FAILURE);
	}
	fprintf(file, "#include <stdio.h>\n");
	fprintf(file, "#include <stdlib.h>\n");
	fprintf(file, "#include <string.h>\n");
	fprintf(file, "#include \"io.h\"\n\n");

	fprintf(file, "#define TRUE 1\n");
	fprintf(file, "#define FALSE 0\n\n");

	fprintf(file, "typedef struct {\n");
	fprintf(file, "	int total_chr_lidos;\n");
	fprintf(file, "	int total_voltas;\n");
	fprintf(file, "	int encontrou_padrao;\n");
	fprintf(file, "} Resultado;\n\n");

	fprintf(file, "Resultado KMP(char *search_string, FILE *file) {\n");
	fprintf(file, "	int estado_atual, total_chr_lidos, fim_chars;\n");
	fprintf(file, "	int search_string_size = strlen(search_string);\n");
	fprintf(file, "	char chr;\n");
	fprintf(file, "	Resultado resultado;\n");
	fprintf(file, "	resultado.total_voltas = 0;\n");
	fprintf(file, "	resultado.total_chr_lidos = 0;\n");
	fprintf(file, "	resultado.encontrou_padrao = FALSE;\n");
	fprintf(file, "	int automato[] = {");
	for(i = 0; i < size - 1; i++)
		fprintf(file, "%d, ", KmpNext[i]);
	fprintf(file, "%d};\n", KmpNext[i]);
	fprintf(file, "	estado_atual = total_chr_lidos = 0;\n");
	fprintf(file, "	while ((chr = fgetc(file)) != EOF) {\n");
	fprintf(file, "		fim_chars = FALSE;\n");
	fprintf(file, "		if(estado_atual > 0 && search_string[estado_atual] != chr) resultado.total_voltas++;\n");
	fprintf(file, "		while (estado_atual > -1 && search_string[estado_atual] != chr){\n");
	fprintf(file, "			estado_atual = automato[estado_atual];\n");
	fprintf(file, "		}\n");
	fprintf(file, "		estado_atual++;\n");
	fprintf(file, "		resultado.total_chr_lidos++;\n");
	fprintf(file, "		if (estado_atual >= search_string_size) {\n");
	fprintf(file, "			printf(\"%%d\\n\", resultado.total_chr_lidos - estado_atual + 1);\n");
	fprintf(file, "			estado_atual = automato[estado_atual];\n");
	fprintf(file, "			resultado.total_voltas++;\n");
	fprintf(file, "			fim_chars = TRUE;\n");
	fprintf(file, "			resultado.encontrou_padrao = TRUE;\n");
	fprintf(file, "		}\n");
	fprintf(file, "	}\n");
	fprintf(file, "	if(fim_chars) resultado.total_voltas--;\n");
	fprintf(file, "	return resultado;\n");
	fprintf(file, "}\n\n");

	fprintf(file, "int main(int argc, char *argv[]){\n");
	fprintf(file, "	char *search_string = \"%s\";\n", search_string);
	fprintf(file, "	char *filename = ParseParams(argc, argv);\n");
	fprintf(file, "	FILE *file = NULL;\n");
	fprintf(file, "	if((file = fopen(filename, \"r\")) == NULL){\n");
	fprintf(file, "		printf(\"Não foi possível abrir o arquivo '%%s'\\nSaindo do programa...\\n\", filename);\n");
	fprintf(file, "		exit(EXIT_FAILURE);");
	fprintf(file, "	}\n");

	fprintf(file, "	printf(\"Padrão %%s encontrado em:\\n\", search_string);\n");
	fprintf(file, "	Resultado resultado = KMP(search_string, file);\n");
	fprintf(file, "	if(!resultado.encontrou_padrao) printf(\"\\n\");\n");
	fprintf(file, "	printf(\"%%d caracteres lidos.\\n\", resultado.total_chr_lidos);\n");
	fprintf(file, "	char *estado_string = resultado.total_voltas == 1 ? \"estado\" : \"estados\";\n");
	fprintf(file, "	printf(\"Voltou %%d %%s no total.\\n\", resultado.total_voltas, estado_string);\n");
	fprintf(file, "	return 0;\n");
	fprintf(file, "}\n");

	if(file) fclose(file);
	free(KmpNext);
}
