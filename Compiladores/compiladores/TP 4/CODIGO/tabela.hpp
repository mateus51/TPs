/*
 * tabela.h
 *
 *  Created on: 30/11/2009
 *      Author: rogerfsg
 */


#ifndef TABELA_H_
#define TABELA_H_

#include <string.h>
#include <stdio.h>
#include <string.h>
#include <iostream>


using namespace std;

#define NMax 100000     /* Numero maximo de niveis possiveis */

struct Arvore_Tabela{

	char nome[10];     /* Contem o nome do Simbolo */

	int  nivel;        /* Contem o nivel do Simbolo relacionado */

	char atributo[10]; /* Contem o atributo do  relacionado */

	int  esq;          /* Filho da esquerda do simbolo relacionado */

	int  dir;	   /* Filho da direita do simbolo relacionado */

};

class Tabela{

private:
	Arvore_Tabela TabelaS[100];     /* Vetor de struct que contem a tabela de simbolos */

public:

	int escopo[10];

	int nivel;    /* inteiro que contem o numero do nivel atual */

	int L;     /* inteiro que contem o indice do ultimo elemento da Tabela de Simbolos */

	int Raiz;   /* inteiro que contem o indice do primeiro elemento da Tabela de Simbolos */

	Tabela();

	void Entrada_Bloco(void);

	void Erro(int numero);

	void Saida_Bloco(void);

	int  Get_Entry(const char * x);

	void Instala(const char *name, const char * atributo);

	char * PegaAtributo(int indice);

	void imprimir(void);

};

#endif
