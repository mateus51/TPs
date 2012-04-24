#include "mv.h"

MaquinaVirtual *NewMV(Args *args){
	MaquinaVirtual *mv = (MaquinaVirtual*) malloc(sizeof(MaquinaVirtual));
	mv->PC = args->PC;
	mv->SP = args->SP;
	mv->AC = 0;
	int i;
	for(i = 0; i < MEM_SIZE; i++) mv->MEM[i] = 0;
	return mv;
}

void LoadProgram(MaquinaVirtual *mv, char *filename){
	FILE *file = fopen(filename, "r");
	if (!file){
		printf("Não foi possível abrir o arquivo %s.\nSaindo do programa...\n", filename);
		exit(EXIT_FAILURE);
	}

	extern int load_exe_from;
	int i;
	char *line = (char*) malloc(sizeof(char) * LINE_MAX_SIZE);
	for(i = load_exe_from; !feof(file); i++){
		line = fgets(line, LINE_MAX_SIZE, file);
		if (line != NULL) mv->MEM[i] = atoi(line);
		else i--;
		//fscanf(file, "%d\n", &mv->MEM[i]);
	}
	free(line);
	fclose(file);
}

void RunMV(MaquinaVirtual *mv){
	int instruction, M, input;
	extern char verbose;

	while (TRUE){
		instruction = mv->MEM[mv->PC++];

		if (verbose) PrintMvState(mv, instruction);

		switch (instruction){
			case LOAD:
				M = mv->MEM[mv->PC++];
				mv->AC = mv->MEM[mv->PC + M];
				break;
			case STORE:
				M = mv->MEM[mv->PC++];
				mv->MEM[mv->PC + M] = mv->AC;
				break;
			case JMP:
				M = mv->MEM[mv->PC++];
				mv->PC = mv->PC + M;
				break;
			case JPG:
				M = mv->MEM[mv->PC++];
				if (mv->AC > 0) mv->PC = mv->PC + M;
				break;
			case JPE:
				M = mv->MEM[mv->PC++];
				if (mv->AC == 0) mv->PC = mv->PC + M;
				break;
			case JPL:
				M = mv->MEM[mv->PC++];
				if (mv->AC < 0) mv->PC = mv->PC + M;
				break;
			case JPNE:
				M = mv->MEM[mv->PC++];
				if (mv->AC != 0) mv->PC = mv->PC + M;
				break;
			case PUSH:
				M = mv->MEM[mv->PC++];
				mv->SP--;
				mv->MEM[mv->SP] = mv->MEM[mv->PC + M];
				break;
			case POP:
				M = mv->MEM[mv->PC++];
				mv->MEM[mv->PC + M] = mv->MEM[mv->SP];
				mv->SP++;
				break;
			case READ:
				M = mv->MEM[mv->PC++];
				printf("insira um inteiro > ");
				scanf("%d", &input);
				printf("\n");
				mv->MEM[mv->PC + M] = input;
				break;
			case WRITE:
				M = mv->MEM[mv->PC++];
				printf("%d\n\n", mv->MEM[mv->PC + M]);
				break;
			case CALL:
				M = mv->MEM[mv->PC++];
				mv->SP--;
				mv->MEM[mv->SP] = mv->PC;
				mv->PC += M;
				break;
			case RET:
				mv->PC = mv->MEM[mv->SP];
				mv->SP++;
				break;
			case ADD:
				M = mv->MEM[mv->PC++];
				mv->AC += mv->MEM[mv->PC + M];
				break;
			case SUB:
				M = mv->MEM[mv->PC++];
				mv->AC -= mv->MEM[mv->PC + M];
				break;
			case XOR:
				M = mv->MEM[mv->PC++];
				mv->AC ^= mv->MEM[mv->PC + M];
				break;
			case AND:
				M = mv->MEM[mv->PC++];
				mv->AC &= mv->MEM[mv->PC + M];
				break;
			case OR:
				M = mv->MEM[mv->PC++];
				mv->AC |= mv->MEM[mv->PC + M];
				break;
			case HALT:
				return;
		}
	}
}

void PrintMvState(MaquinaVirtual *mv, int instruction){
	switch (instruction){
		case LOAD:  printf("LOAD\n");  break;
		case STORE: printf("STORE\n"); break;
		case JMP:   printf("JMP\n");   break;
		case JPG:   printf("JPG\n");   break;
		case JPE:   printf("JPE\n");   break;
		case JPL:   printf("JPL\n");   break;
		case JPNE:  printf("JPNE\n");  break;
		case PUSH:  printf("PUSH\n");  break;
		case POP:   printf("POP\n");   break;
		case READ:  printf("READ\n");  break;
		case WRITE: printf("WRITE\n"); break;
		case CALL:  printf("CALL\n");  break;
		case RET:   printf("RET\n");   break;
		case ADD:   printf("ADD\n");   break;
		case SUB:   printf("SUB\n");   break;
		case XOR:   printf("XOR\n");   break;
		case AND:   printf("AND\n");   break;
		case OR:    printf("OR\n");    break;
		case HALT:  printf("HALT\n");  break;
	}
	printf(" PC: %d (%d)\n SP: %d (%d)\n AC: %d\n\n", mv->PC, mv->MEM[mv->PC], mv->SP, mv->MEM[mv->SP], mv->AC);
}

