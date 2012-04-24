#ifndef PERMUTATION_H
#define PERMUTATION_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int total_permutations;
	int size;
	int *column_value;
	int *perm_array;
} Permutation;

typedef struct {
	int total_combinations;
	int size;
	int **C;
	int *comb;
} Combination;

Permutation *NewPermutation(int size);

int *GenerateColumnValues(int n);

void Num2Perm(int rank, Permutation *permutation);

void FreePermutation(Permutation *permutation);

void PrintPermutation(Permutation *permutation);



Combination *NewCombination(int size);

int **GenerateMatrixC(int n);

void Num2Comb(int rank, Combination *combination);

void FreeCombination(Combination *combination);

void PrintCombination(Combination *combination);




int Fatorial(int n);

int Combinatorial(int n);


#endif
