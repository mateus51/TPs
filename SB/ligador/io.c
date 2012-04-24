#include "io.h"

// Nome do arquivo de saída
char *output_file = NULL;

// Array com os nomes dos arquivos a serem linkados
char **object_files = NULL;
int total_object_files;

void GetArgs(int argc, char *argv[]) {
	int c;
	char *main_object = NULL;
	extern char *optarg;
	extern int optind, optopt;
    while ((c = getopt(argc, argv, ":o:m:")) != -1) {
        switch (c) {
			case 'm':
				main_object = optarg;
				//main_object = (char*) calloc(strlen(optarg) + 1, sizeof(char));
				//strcpy(main_object, optarg);
				break;
			case 'o':
				output_file = optarg;
				break;
			case '?':
				printf("Argumento -%c desconhecido.\n", optopt);
				break;
			case ':':
				printf("O argumento -%c necessita de um argumento.\n", optopt);
				exit(EXIT_FAILURE);
        }
	}

    if (main_object == NULL) {
    	printf("O programa principal deve ser informado através da opção '-m'\n");
    	exit(EXIT_FAILURE);
    }
    else if (output_file == NULL) {
    	printf("O nome do programa a ser gerado deve ser informado através da opção '-o'\n");
    	exit(EXIT_FAILURE);
    }

    total_object_files = argc - optind + 1;
    object_files = (char**) calloc(total_object_files, sizeof(char*));
    object_files[0] = main_object;
    int i;
    for (i = 1; i < total_object_files; i++) {
    	object_files[i] = argv[optind + i - 1];
    }

}

