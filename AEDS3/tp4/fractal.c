#include "fractal.h"

void CheckIfIsFractal(Grafo *grafo) {

	int total_graus = TotalGraus(grafo);
	int num_vertices_grau3 = NumVerticesGrauN(grafo, 3);

	//Pode ser fractal com d = 0 e h = 3
	if (total_graus == 1) {

		// Grafo roda com h = 3
		if (num_vertices_grau3 == 4) {
			printf("0 3");
		}

		else {
			printf("-1");
		}
	}

	//Pode ser fractal com d = 0 e h > 3 ou d > 0 e h = 3
	else if (total_graus == 2) {
		int pow3;

		// Grafo roda com h > 3
		if (num_vertices_grau3 == grafo->total_vertices - 1) {
			int vertice_central = VerticeMaiorGrau(grafo);
			int h = grafo->graus[vertice_central];
			if (EhGrafoRoda(grafo, vertice_central)) {
				printf("0 %d", h);
			}
			else {
				printf("-1");
			}
			//printf("grafo roda com h > 3\n\n");
		}

		// Fractal com d > 0 e h = 3
		else if ((pow3 = IsPowerOfThree(num_vertices_grau3 - 1))) {
			printf("%d 3", pow3 - 1);
			//printf("Fractal com d > 0 e h = 3\n\n");
		}

		else {
			printf("-1");
		}

	}

	// Pode ser fractal com d > 0
	else if (total_graus == 3) {

		int vertice_central = VerticeGrauIntermediario(grafo);
		int h = grafo->graus[vertice_central];
		int d = 0;
		int count = 0;
		int eh_fractal = EhFractal(grafo, vertice_central, &count);

		if (eh_fractal) {
			d = ProfundidadeFractal(h, count);
			if (d == -1) {
				printf("-1");
			}
			else {
				printf("%d %d", d, h);
			}
		}
		else {
			printf("-1");
		}
	}

	// Não pode ser um fractal roda
	else {
		printf("-1");
	}

	extern boolean benchmark;
	if (!benchmark) printf("\n");
}

boolean EhFractal(Grafo *grafo, int vertice_central, int *count) {
	boolean eh_roda = EhGrafoRoda(grafo, vertice_central);

	if (eh_roda) {
		*count += 1;
		int adj = PrimeiroAdj(grafo, vertice_central);

		// Se não chegou na borda do grafo
		if (grafo->graus[adj] != 3) {
			int *lista_adj = ListaAdj(grafo, vertice_central);
			int total_adj = grafo->graus[vertice_central];

			DesfazRoda(grafo, vertice_central);

			boolean eh_fractal = FALSE;
			int i;
			for (i = 0; i < total_adj; i++) {
				eh_fractal = EhFractal(grafo, lista_adj[i], count);
				if (!eh_fractal) {
					free(lista_adj);
					return FALSE;
				}
			}
			free(lista_adj);
			return TRUE;
		}

		else {
			return TRUE;
		}
	}

	else {
		return FALSE;
	}
}

int ProfundidadeFractal(int n, int total_grafos_roda) {
	int i, count = 0;
	for (i = 0; i < 1000; i++) {
		count += pow(n, i);
		if (count >= total_grafos_roda) break;
	}

	if (count > total_grafos_roda) {
		return -1;
	}
	else {
		return i;
	}
}

int IsPowerOfThree(int n) {
	int count = 0;

	if (n == 0) return 0;

	while (n % 3 == 0) {
	    n /= 3;
	    count++;
	}

	if (n == 1)
		return count;

	else
		return 0;
}
