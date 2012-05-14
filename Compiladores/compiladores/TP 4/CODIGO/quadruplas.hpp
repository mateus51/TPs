/*
 * Quadruplas.hpp
 *
 *  Created on: 30/11/2009
 *      Author: rogerfsg
 */


#ifndef QUADRUPLA_H_
#define QUADRUPLA_H_


#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <vector>

using namespace std;

#define NUM_OPERANDOS	3
#define VAZIO		"\0"

class Quadrupla
{
public:
	string op;                                  /* operador */

//	op, r, n, d
//O numero op (0 a 15) define o
//codigo da operacao. O numeror (0 a 15) de ne o registrador a ser usado, enquanto n frequentemente (0 a
//255) de ne o tamanho do operando. Por ultimo, d (-32768 a 32767) usualmente de ne um deslocamento
//de um endereco (possivelmente negativo) d e r de nem em conjunto o endereco do operando (d +
//registrador r ). Alem disso, comentarios sao iniciados com caractere ' ' e terminam no nal da linha. Um
//exemplo de um arquivo de instrucoes e mostrado abaixo.

	string ops[NUM_OPERANDOS];                  /* operandos 0, 1 e 2 */
public:
	Quadrupla();                                /* construtor */
	Quadrupla( string op_enter, string a, string b, string c); /* construtor */

	string get_operador( void );                      /* retorna operador */

	void set_operador( string novo );                 /* muda operador para novo */

	string get_operado_pos( int pos );                  /* retorna operando pos */

	void set_ops( int pos, string v );          /* muda valor do operando pos para v */

	Quadrupla stringToQuadrupla( string s );    /* retorna a quadrupla representada por s */

	void imprimeQuadrupla();
};

class Quadruplas{
public:
	vector<Quadrupla> quadruplas;

	Quadruplas();

	Quadrupla getQuadrupla( int pos );
	int getNumQuadruplas();
	void imprimeQuadruplas();

	void addQuadrupla(Quadrupla q);
};



#endif

