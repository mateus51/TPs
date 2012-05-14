/*
 * tabela.cpp
 *
 *  Created on: 30/11/2009
 *      Author: rogerfsg
 */

#include "tabela.hpp"

Tabela::Tabela()
{
	L = 0;    /* Considera-se que a primeira posicao da tabela eh a de indice 0.
							L eh o final da arvore binaria */
	Raiz = -1;

	nivel = 1;           /* O primeiro nivel  o 1 */

	escopo[nivel] = 0;   /* escopo[1] contem o indice do primeiro elemento */
}

/**************************************************************************

Implementacoes

***************************************************************************/

/************  Funcao que define os erros provaveis de ocorrer  **********/

void Tabela::Erro(int num)
{
	//	char opcao;
	switch (num) {
	case 1: //printf("Tabela de Simbolos cheia\n");
		break;

	case 2: //printf("Este item nao foi encontrado\n");
		break;

	case 3: //printf("Este item ja foi inserido\n");
		break;
	}
}

/*******************     Funcao de entrada num bloco   ********************/
void Tabela::Entrada_Bloco()
{
	// Limpa a tela
	//	clrscr();

	nivel++;

	if (nivel > NMax)
		Erro(1);

	else escopo[nivel] = L;

	//printf("\nEntrada no nivel  %d\n\n",nivel);
}

/********************  Funcao de saida de um bloco  ***********************/
void Tabela::Saida_Bloco()
{

	int i;

	L= escopo[nivel];

	if (Raiz >= L)

		Raiz =0;

	else for (i=0;i<=(L-1); i++)

	{

		if (TabelaS[i].esq >= L)

			TabelaS[i].esq = -1;

		if (TabelaS[i].dir >= L)

			TabelaS[i].dir = -1;

	}

	//printf("\nSaida do nivel %d",nivel);

	nivel--;
}

/****************  Funcao que pesquisa item na tabela  *******************/
int Tabela::Get_Entry(const char * x)   /* Pesquisa o simbolo "x" e retorna o indice
						da Tabela de simbolos onde ele se encontra */
{
	int S, K, aux;
	S = Raiz;
	K = -1;

	while (S != -1)
	{
		aux = strcmp(TabelaS[S].nome,x);

		if (aux == 0)
		{
			K = S;
			S = TabelaS[S].dir;
		}

		else if (x < TabelaS[S].nome) 	S = TabelaS[S].esq;

		else S = TabelaS[S].dir;

	}

	if (K != -1) /*Verificar se eh -1 ou 0 */
	{
//		printf("O item esta no nivel  %d\n", TabelaS[K].nivel);
//		printf("               Indice %u\n",K);
	}

	else{
		Erro(2);
		return -1;
	}

	return (K);  /* Retorna o indice no vetor TabelaS do elemento procurado*/

}

char * Tabela::PegaAtributo(int indice){
	return TabelaS[indice].atributo;
}


/***************  Funcao que instala o item na tabela  *****************/
/* Instala o simbolo "X" com o atributo atribut na Tabela de Simbolos */
void Tabela::Instala(const char * X, const char * atribut)
{
	//cout << " Instala : " << X << "		: atrib :: " << atribut << endl;
//	getchar();
	int S, i, k, aux;

	//	clrscr();

	S = Raiz;

	i = Raiz;

	k = -1;

	while (S != -1)   /* Enquanto nao achar um nodo folha  */
	{

		i=S;

		aux = strcmp(TabelaS[S].nome,X);

		if (aux == 0)

		{
			k = S;

			S = TabelaS[S].dir;

			if (i >= escopo[nivel]) Erro(3);

		}

		else if ( X < TabelaS[S].nome )		S = TabelaS[S].esq;
		else 								S = TabelaS[S].dir;
	}

	if ( (k > escopo[nivel] ) || ( L >= NMax + 1 ) )	Erro(1);
	else
	{
		TabelaS[L].nivel = nivel;

		aux = strlen(atribut);

		for (k = 0; k<= aux-1; k++)
			TabelaS[L].atributo[k] = atribut[k];
		for(; k < 10; k++ )
			TabelaS[L].atributo[k] = '\0';

		TabelaS[L].esq = TabelaS[L].dir = -1;

		aux = strlen(X);

		for (k = 0; k<=(aux-1); k++)

			TabelaS[L].nome[k] = X[k];

		if (Raiz == -1) Raiz= L;

		else if (X < TabelaS[i].nome)

			TabelaS[i].esq = L;

		else TabelaS[i].dir = L;
		L++;
	}
}

void Tabela::imprimir()
{

	int i;

	//	clrscr();

	for (i=0; i<=L-1; i++)

	{

		printf("\n\nNome : ");

		printf("%s", TabelaS[i].nome);

		printf("\n");

		printf("Atributo : ");

		printf("%s", TabelaS[i].atributo);

		printf("\n");

		printf("Nivel : ");

		printf("%i", TabelaS[i].nivel);

		printf("\n");

		printf("Esquerdo : ");

		if (TabelaS[i].esq == -1) printf("0");

		else printf("%i", TabelaS[i].esq);

		printf("\n");

		printf("Direito : ");

		if (TabelaS[i].dir == -1) printf("0");

		else printf("%i", TabelaS[i].dir);

		printf("\n");

		printf("\n"); }

}

