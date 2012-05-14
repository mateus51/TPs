/*
 * tradutor.hpp
 *
 *  Created on: 30/11/2009
 *      Author: rogerfsg
 */


#ifndef TRADUTOR_H_
#define TRADUTOR_H_

#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <vector>
using namespace std;

#include "quadruplas.hpp"
#include "tabela.hpp"


#define MAX_DATA 10000
#define MAX_ARRAY_SIZE_INT 100
#define MAX_ARRAY_SIZE_CHAR "100"


class Tradutor {

private:

	Tabela tabela;
	string instrucao;
	vector<string> instrucoesTAM;

	int SB ;
	int ST, LB, LT;
//	Acompanha o codigo = numero de instrucoes ate o momento
	int CT ;

//	map<string, string (*)(Quadrupla &q, Tabela &t)> opcodes;

public:

	Tradutor();

	string getInstrucao();

	void setInstrucao( string s );

	void traduzQuadruplas( Quadruplas Q );

	void traduzQuadrupla( Quadrupla q );

	void adicionaInstrucao( string inst );

	void imprimeProgramaTAM( string file_name );

	string operacaoTAM(string op);

	string Int_to_String(int i);

	void adicionaVariavel(string operador, int tamanho_enter, bool aumenta_pilha);
};


#endif


