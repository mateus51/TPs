
FILE *file;

void initFile(char *filename) {
	if ((file = fopen(filename, "w")) == NULL) {
		printf("Error opening file!\n");
		exit(EXIT_FAILURE);
	}
}

void emitlabel(int i) {
	fprintf(file, "L%d:", i);
}

void emit(char *str) {
	fprintf(file, "\t%s\n", str);
}
