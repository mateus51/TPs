#ifndef MV_H
#define MV_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "io.h"

#define TRUE 1
#define FALSE 0

// Tamanho da memória
#define MEM_SIZE 1000

// Tamanho máximo de uma linha no programa, incluindo comentários
#define LINE_MAX_SIZE 150

#define LOAD  1
#define STORE 2
#define JMP   3
#define JPG   4
#define JPE   5
#define JPL   6
#define JPNE  7
#define PUSH  8
#define POP   9
#define READ  10
#define WRITE 11
#define CALL  12
#define RET   13
#define ADD   14
#define SUB   15
#define XOR   16
#define AND   17
#define OR    18
#define HALT  19

typedef struct {
	int PC;
	int SP;
	int AC;
	int MEM[MEM_SIZE];
} MaquinaVirtual;



MaquinaVirtual *NewMV();

void LoadProgram(MaquinaVirtual *mv, char *filename);

void RunMV(MaquinaVirtual *mv);

void PrintMvState(MaquinaVirtual *mv, int instruction);



#endif

