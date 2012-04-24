#include "lista.h"

Lista *NewLista() {
	Lista *lista = (Lista*) malloc(sizeof(Lista));
	lista->primeiro = (Apontador) malloc(sizeof(Celula));
	lista->primeiro->video_id = -1;
	lista->primeiro->chunk_index = -1;
	lista->primeiro->chunk_size = -1;
	lista->primeiro->total_acessos = -1;
	lista->ultimo = lista->primeiro;
	lista->primeiro->prox = NULL;
	return lista;
}

int ListaVazia(Lista *lista) {
	return (lista->primeiro == lista->ultimo);
}

// insere o item na posição seguinte à apontada por p
void Insere(Lista *lista, Apontador p, int video_id, int chunk_index, int chunk_size) {
	if (p == NULL) {
		printf("Erro ao inserir: p == NULL!\n");
		exit(EXIT_FAILURE);
	}
	Apontador aux = p->prox;
	p->prox = (Apontador) malloc(sizeof(Celula));
	p->prox->video_id = video_id;
	p->prox->chunk_index = chunk_index;
	p->prox->chunk_size = chunk_size;
	p->prox->total_acessos = 1;
	p->prox->prox = aux;
	if (p == lista->ultimo) lista->ultimo = p->prox;
	if (lista->primeiro == lista->ultimo) lista->ultimo = lista->primeiro->prox;
}

//o item a ser retirado é seguinte ao apontado por p
// retorna o tamanho do chunk retirado;
int Retira(Lista *lista, Apontador p) {
	if (ListaVazia(lista) || p == NULL || p->prox == NULL) {
		printf("Erro ao retirar da lista!   :(\n");
		if (ListaVazia(lista)) printf(" lista vazia!\n\n");
		else if (p == NULL) printf(" p == NULL!\n\n");
		else if (p->prox == NULL) printf(" p->prox == NULL\n\n");
		else printf(" ???\n\n");
		exit(EXIT_FAILURE);
	}
	Apontador q = p->prox;
	p->prox = q->prox;
	if (p->prox == NULL) lista->ultimo = p;
	int freed_size = q->chunk_size;
	free(q);
	return freed_size;
}

// Retira o último item da lista
int RetiraUltimo(Lista *lista) {
	if (!ListaVazia(lista)) {
		Apontador aux = lista->primeiro;
		while (aux->prox->prox != NULL) {
			aux = aux->prox;
		}
		return Retira(lista, aux);
	}
	return 0;
}

// Coloca o item seguinte ao apontado por p na primeira
// posição da lista
void SendToFirstPosition(Lista *lista, Apontador p) {
	if (ListaVazia(lista) || p == NULL || p->prox == NULL) {
		printf("Erro ao anviar para o topo da lista!\n");
		if (ListaVazia(lista)) printf(" lista vazia!\n\n");
		else if (p == NULL) printf(" p == NULL!\n\n");
		else if (p->prox == NULL) printf(" p->prox == NULL\n\n");
		else printf(" ???\n\n");
		return;
	}

	if (p != lista->primeiro) {
		Apontador aux = p->prox;
		p->prox = aux->prox;
		aux->prox = lista->primeiro->prox;
		lista->primeiro->prox = aux;
		if (lista->ultimo == aux) lista->ultimo = p;
	}

}

// Incrementa o total de acessos do chunk seguinte ao apontado
// por p, e reordena por total de acessos
void OrderByAcessos(Lista *lista) {
	Apontador menor, aux, cabeca = lista->primeiro;
	int menor_acesso;
	while (lista->primeiro->prox != NULL) {
		menor_acesso = 999999;
		aux = lista->primeiro;
		while (aux->prox != NULL) {
			if (aux->prox->total_acessos < menor_acesso) {
				menor_acesso = aux->prox->total_acessos;
				menor = aux;
			}
			aux = aux->prox;
		}
		SendToFirstPosition(lista, menor);
		lista->primeiro = lista->primeiro->prox;
	}
	lista->primeiro = cabeca;
	RedoUltimoPointer(lista);
}

void ImprimeLista(Lista *lista) {
	Apontador aux = lista->primeiro;

	while (aux->prox != NULL) {
		printf("%d %d %d (%d)", aux->prox->video_id, aux->prox->chunk_index, aux->prox->chunk_size, aux->prox->total_acessos);
		if (aux == lista->primeiro)
			printf(" primeiro\n");
		else if (aux->prox == lista->ultimo)
			printf(" ultimo\n");
		else
			printf("\n");

		aux = aux->prox;
	}
	printf("\n");
}

void RedoUltimoPointer(Lista *lista) {
	Apontador aux = lista->primeiro;
	while (aux->prox != NULL) {
		aux = aux->prox;
	}
	lista->ultimo = aux;
}

void FreeLista(Lista *lista) {
	Apontador aux = lista->primeiro;
	while (!ListaVazia(lista)) {
		Retira(lista, aux);
	}
	free(lista->primeiro);
	free(lista);
}
