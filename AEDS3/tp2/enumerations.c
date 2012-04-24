#include "enumerations.h"

/*
 * Cria uma nova struct permutação, e inicializa as variáveis
 */
Permutation *NewPermutation(int size) {
	Permutation *permutation = (Permutation*) malloc(sizeof(Permutation));
	permutation->size = size;
	permutation->column_value = GenerateColumnValues(size);
	permutation->perm_array = (int*) calloc(permutation->size, sizeof(int));
	permutation->total_permutations = permutation->size * permutation->column_value[0];
	return permutation;
}

/*
 * Desaloca toda a memória alocada para a permutação.
 */
void FreePermutation(Permutation *permutation) {
	free(permutation->column_value);
	free(permutation->perm_array);
	free(permutation);
}

/*
 * Cria o array usado para gerar as permutações de acordo
 * com o número passado.
 *		n -> número de elementos do conjunto
 */
int *GenerateColumnValues(int n) {
    int i;
    int *column_value = (int*) calloc(n, sizeof(int));

    column_value[n-1] = 1;
    for (i = n-2; i >= 0; i--){
        column_value[i] = column_value[i+1]*(n-i-1);
    }

    return column_value;
}

/*
 * Gera uma nova permutação, de acordo com o número rank,
 * passado como parâmetro.
 */
void Num2Perm(int rank, Permutation *permutation) {
    int i, j;
    int r[permutation->size], available[permutation->size];

    for (i = 0; i < permutation->size; i++) {
        r[i] = rank / permutation->column_value[i];
        rank = rank % permutation->column_value[i];
    }

    for (i = 0; i < permutation->size; i++) {
        available[i] = i;
    }

    for (i = 0; i < permutation->size; i++) {
    	permutation->perm_array[i] = available[r[i]];
        for (j = r[i]; j < permutation->size-1-i; j++) {
            available[j] = available[j+1];
        }
    }
}

/*
 * Imprime uma permutação.
 */
void PrintPermutation(Permutation *permutation) {
	int i;
	for (i = 0; i < permutation->size; i++) {
		printf("%2d", permutation->perm_array[i]);
	}
	printf("\n");
}









/*
 * Cria uma nova combinação, e inicializa as variáveis.
 */
Combination *NewCombination(int size) {
	Combination *combination = (Combination*) malloc(sizeof(Combination));
	combination->size = size;
	combination->comb = (int*) calloc(2, sizeof(int));
	combination->C = GenerateMatrixC(size);
	combination->total_combinations = combination->C[size][2];
	return combination;
}

/*
 * Desaloca todo o espaço usado por uma combinação.
 */
void FreeCombination(Combination *combination) {
	int i;
	for (i = 0; i <= combination->size; i++) {
		free(combination->C[i]);
	}
	free(combination->C);
	free(combination->comb);
	free(combination);
}

/*
 * Gera a matriz usada para gerar as combinações de acordo
 * com o número passado.
 * 		n -> número de elementos do conjunto
 */
int **GenerateMatrixC(int n) {
    int i, j;
    int **C = (int**) calloc(n+1, sizeof(int*));
    for (i = 0; i <= n; i++) {
        C[i] = (int*) calloc(n+1, sizeof(int));
        for (j = 0; j <= n; j++) {
            C[i][j] = 0;
        }
    }
    for (i = 0; i <= n; i++) {
        C[i][0]=1;
        C[i][i]=1;
    }
    for (i = 2; i <= n; i++) {
        for (j = 1; j < i; j++) {
            C[i][j] = C[i-1][j-1] + C[i-1][j];
        }
    }
    return C;
}

/*
 * Gera uma nova combinação, de acordo com o número rank,
 * passado como parâmetro.
 */
void Num2Comb(int rank, Combination *combination) {
    int i, j, leftover, k = 2;
    int complement[combination->size];
    leftover = combination->total_combinations - rank - 1;
    j = combination->size - 1;
    for (i = k-1; i >= 0; i--) {
        for (;leftover < combination->C[j][i+1]; j--)
        ;
        complement[i] = j;
        leftover -= combination->C[j][i+1];
        j--;
    }
    for (i = 0; i < k; i++) {
    	combination->comb[i] = combination->size - 1 - complement[k-1-i];
    }
}

/*
 * Imprime uma combinação.
 */
void PrintCombination(Combination *combination) {
    int i;
    for (i = 0; i < 2; i++)
        printf("%d ", combination->comb[i]);
    printf("\n");
}




/*
 * Calcula n!.
 */
int Fatorial(int n) {
	int i, result;
	result = 1;
	for (i = 2; i <= n; i++) {
		result *= i;
	}
	return result;
}

/*
 * Calcula C(n, 2) = n! / (k! * (n-k)!)
 */
int Combinatorial(int n) {
	return Fatorial(n) / (Fatorial(n-2) * 2);
}
