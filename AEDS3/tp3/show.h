#ifndef SHOW_H
#define SHOW_H

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

typedef struct {
	int num_musicas;
	int vol_inicial;
	int vol_limite;
	int *volumes;
} Show;

Show *NewShow();

void FreeShow(Show *show);

void PrintShow(Show *show);

void fb(Show *show);

void pd(Show *show);

int **NewPdTable(Show *show);

void FreePdTable(int **table, int n);

void PrintPdTable(Show *show, int **table);


#endif
