#include "grafo.h"

// Aloca espaço para um novo grafo, e retorna um pointer para ele.
Grafo *NewGraph(int total_vertices) {
	Grafo *grafo = (Grafo*) malloc(sizeof(Grafo));
	grafo->adj = (int**) calloc(total_vertices, sizeof(int*));
	int i;
	for(i = 0; i < total_vertices; i++)
		grafo->adj[i] = (int*) calloc(total_vertices, sizeof(int));

	grafo->graus = (int*) calloc((size_t) total_vertices, sizeof(int));
	grafo->total_vertices = total_vertices;
	//grafo->vertice_maior_grau = grafo->vertice_menor_grau = 0;
	return grafo;
}

// Lê um grafo de um arquivo
Grafo *ReadGraphFromFile(FILE *file) {
	int total_vertices, v1, v2;
	char *line = (char*) calloc(LINE_MAX_SIZE, sizeof(char));

	fscanf(file, "%d\n", &total_vertices);

	//printf(" leu total_vertices: %d\n", total_vertices);

	Grafo *grafo = NewGraph(total_vertices);

	fgets(line, LINE_MAX_SIZE, file);
	RemoveNewlineChar(line);

	char *token = strtok(line, ",");
	while (token != NULL) {
		sscanf(token, "%d %d", &v1, &v2);
		InsereAresta(grafo, v1, v2);
		token = strtok(NULL, ",");
	}

	free(line);

	return grafo;
}

/*
void CheckMaxMinGrau(Grafo *grafo, int v1, int v2) {
	if (grafo->graus[v1] > grafo->graus[grafo->vertice_maior_grau])
		grafo->vertice_maior_grau = v1;
	else if (grafo->graus[v1] < grafo->graus[grafo->vertice_menor_grau])
		grafo->vertice_maior_grau = v1;
}
*/

// Libera toda a memória utilizada por um grafo
void FreeGraph(Grafo *grafo) {
	int i;
	for (i = 0; i < grafo->total_vertices; i++)
		free(grafo->adj[i]);

	free(grafo->adj);
	free(grafo->graus);
	free(grafo);
}

// Insere uma aresta no grafo
void InsereAresta(Grafo *grafo, int v1, int v2) {
	if (!grafo->adj[v1][v2]) {
		grafo->adj[v1][v2] = grafo->adj[v2][v1] = 1;
		grafo->graus[v1]++;
		grafo->graus[v2]++;
	}
}

// Remove uma aresta do grafo
void RetiraAresta(Grafo *grafo, int v1, int v2) {
	if (grafo->adj[v1][v2]) {
		grafo->adj[v1][v2] = grafo->adj[v2][v1] = 0;
		grafo->graus[v1]--;
		grafo->graus[v2]--;
	}
}

// Verifica se existe uma aresta entre dois vértices
boolean ExisteAresta(Grafo *grafo, int v1, int v2) {
	if (grafo->adj[v1][v2]) return TRUE;
	return FALSE;
}

// Retorna o primeiro da lista de adjacência
int PrimeiroAdj(Grafo *grafo, int v1) {
	int v2;
	for (v2 = 0; v2 < grafo->total_vertices; v2++) {
		if (grafo->adj[v1][v2]) return v2;
	}
	return -1;
}

// Retorna o próximo da lista de adjacência
int ProxAdj (Grafo *grafo, int v1, int currentAdj) {
	int v2;
	for (v2 = currentAdj + 1; v2 < grafo->total_vertices; v2++) {
		if (grafo->adj[v1][v2]) return v2;
	}
	return -1;
}

// Retorna a lista de adjacência de um vértice
int *ListaAdj(Grafo *grafo, int v1) {
	int *adj = NULL;//(int*) calloc(grafo->graus[v1], sizeof(int));
	int i, count = 0;
	for(i = 0; i < grafo->total_vertices; i++) {
		if (ExisteAresta(grafo, v1, i)) {
			count++;
			adj = (int*) realloc(adj, sizeof(int) * count);
			adj[count-1] = i;
		}
	}
	return adj;
}

// Retorna o total de vértices com grau N no grafo
int NumVerticesGrauN(Grafo *grafo, int n) {
	int i, count = 0;
	for (i = 0; i < grafo->total_vertices; i++) {
		if (grafo->graus[i] == n) count++;
	}
	return count;
}

// Calcula quantos vértices com grau diferente existem no grafo
int TotalGraus(Grafo *grafo) {
	int i, j, count = 1;
	boolean achou;
	int *graus = (int*) malloc(sizeof(int));
	graus[0] = grafo->graus[0];
	for (i = 1; i < grafo->total_vertices; i++) {
		achou = FALSE;

		for (j = 0; j < count; j++) {
			if (grafo->graus[i] == graus[j]) {
				achou = TRUE;
				break;
			}
		}
		if (!achou) {
			count++;
			graus = (int*) realloc(graus, sizeof(int) * count);
			graus[count-1] = grafo->graus[i];
		}
	}
	free(graus);
	return count;
}

// Retorna o vértice com maior grau.
// Se mais de um vértice possuir o maior grau, retorna
// o primeiro deles.
int VerticeMaiorGrau(Grafo *grafo) {
	int i, max = 0;
	for (i = 1; i < grafo->total_vertices; i++) {
		if (grafo->graus[i] > grafo->graus[max]) max = i;
	}
	return max;
}

// Retorna o vértice com menor grau.
// Se mais de um vértice possuir o menor grau, retorna
// o primeiro deles.
int VerticeMenorGrau(Grafo *grafo) {
	int i, min = 0;
	for (i = 1; i < grafo->total_vertices; i++) {
		if (grafo->graus[i] < grafo->graus[min]) min = i;
	}
	return min;
}

// Retorna o vértice com grau intermediário, em um grafo q possui
// vértices com 3 graus diferentes.
// Se mais de um vértice possuir o grau intermediário, retorna
// o primeiro deles.
int VerticeGrauIntermediario(Grafo *grafo) {
	int min = VerticeMenorGrau(grafo);
	int max = VerticeMaiorGrau(grafo);
	int i;

	for (i = 0; i < grafo->total_vertices; i++) {
		//printf(" min: %d\n max: %d\n i: %d\n", grafo->graus[max], grafo->graus[min], grafo->graus[i]);
		if (grafo->graus[i] > grafo->graus[min] && grafo->graus[i] < grafo->graus[max]) {
			//printf("i: %d\n\n", i);
			return i;
		}
	}
	return -1;
}

// Verifica se um vertice é o vértice central de um grafo roda
boolean EhGrafoRoda(Grafo *grafo, int vertice_central) {
	Grafo *subgrafo_ciclo = ConstroiSubgrafoCiclo(grafo, vertice_central);

	boolean eh_roda = EhCiclo(subgrafo_ciclo);

	FreeGraph(subgrafo_ciclo);

	return eh_roda;
}

void DesfazRoda(Grafo *grafo, int vertice_central) {
	int adj, adj_ciclo;
	adj = PrimeiroAdj(grafo, vertice_central);
	while (adj != -1) {
		adj_ciclo = PrimeiroAdj(grafo, adj);
		while (adj_ciclo != -1) {
			// Se fizer parte da roda
			if (ExisteAresta(grafo, adj_ciclo, vertice_central)) {
				RetiraAresta(grafo, adj, adj_ciclo);
			}
			adj_ciclo = ProxAdj(grafo, adj, adj_ciclo);
		}
		RetiraAresta(grafo, vertice_central, adj);
		adj = ProxAdj(grafo, vertice_central, adj);
	}
}

// Constroi o subgrafo ciclo em volta do vértice central de
// um grafo roda
Grafo *ConstroiSubgrafoCiclo(Grafo *grafo, int vertice_central) {

	Grafo *subgrafo = NewGraph(grafo->graus[vertice_central]);

	int i;
	int *vertices = (int*) calloc(subgrafo->total_vertices, sizeof(int));
	for (i = 0; i < subgrafo->total_vertices; i++)
		vertices[i] = -1;

	int v1, v2, adj, sub_adj, vcount = 0;
	boolean achou = FALSE;

	adj = PrimeiroAdj(grafo, vertice_central);

	while (adj != -1) {

		// Pegando vertice 1
		achou = FALSE;
		for (i = 0; i <= vcount; i++) {
			if (vertices[i] == adj) {
				v1 = i;
				achou = TRUE;
				break;
			}
		}
		if (!achou) {
			v1 = vcount;
			vertices[vcount] = adj;
			vcount++;
		}


		sub_adj = PrimeiroAdj(grafo, adj);
		while (sub_adj != -1) {
			if (ExisteAresta(grafo, vertice_central, sub_adj) && sub_adj != vertice_central) {

				// Pegando vertice 2
				achou = FALSE;
				for (i = 0; i <= vcount; i++) {
					if (vertices[i] == sub_adj) {
						v2 = i;
						achou = TRUE;
						break;
					}
				}
				if (!achou) {
					v2 = vcount;
					vertices[vcount] = sub_adj;
					vcount++;
				}

				//printf("  (ConstroiSubgrafoCiclo): adicionando aresta %d %d\n", v1, v2);
				InsereAresta(subgrafo, v1, v2);

			}
			sub_adj = ProxAdj(grafo, adj, sub_adj);
		}
		adj = ProxAdj(grafo, vertice_central, adj);
	}

	free(vertices);
	return subgrafo;
}

// Verifica se um grafo é um ciclo
boolean EhCiclo(Grafo *grafo) {

	//printf("vendo se é ciclo...\n");

	//PrintGraph(grafo);

	int num_vertices_grau2 = NumVerticesGrauN(grafo, 2);

	if (num_vertices_grau2 == grafo->total_vertices) {

		//printf("num_vertices_grau2 = %d\n", num_vertices_grau2);

		int i, prox, vertice_inicial, current_vertice, last_vertice;
		vertice_inicial = current_vertice = last_vertice = 0;

		for (i = 0; i < grafo->total_vertices; i++) {
			//printf("  current: %d\n", current_vertice);
			prox = PrimeiroAdj(grafo, current_vertice);
			if (prox == last_vertice) prox = ProxAdj(grafo, current_vertice, prox);
			if (prox == vertice_inicial && i != grafo->total_vertices-1) return FALSE;
			last_vertice = current_vertice;
			current_vertice = prox;
		}
		return current_vertice == vertice_inicial;

	}
	else return FALSE;
}

void PrintGraph(Grafo *grafo) {
	printf("%d vertices\n", grafo->total_vertices);
	//printf("%d arestas\n\n", grafo->total_arestas);
	printf("%d vertices de grau 3\n", NumVerticesGrauN(grafo, 3));
	printf("%d graus diferentes\n", TotalGraus(grafo));
	int i, j;
	for(i = 0; i < grafo->total_vertices; i++) {
		for(j = 0; j < grafo->total_vertices; j++) {
			if (grafo->adj[i][j]) printf("%3d ->%3d    ", i, j);
		}
		printf("\n");
	}
}

void RemoveNewlineChar(char *string) {
	int size = strlen(string);
	if (string[size-1] == '\n')
		string[size-1] = '\0';
}
