/*
 * Quadruplas.cpp
 *
 *  Created on: 30/11/2009
 *      Author: rogerfsg
 */

#include "quadruplas.hpp"

/* construtor */
Quadrupla::Quadrupla(){

}

/* construtor */
Quadrupla::Quadrupla( string op_enter, string a, string b, string c)
: op(op_enter){
//	cout <<"Quadrupla " << op_enter << "  " << a << "  " << b << "  " << c << endl ;
	ops[0] = a;
	ops[1] = b;
	ops[2] = c;
}

/* retorna operador */
string Quadrupla::get_operador( void ){
	return op;
}

/* muda operador para novo */
void Quadrupla::set_operador( string novo ){
	op = novo;
}

/* retorna operando pos */
string Quadrupla::get_operado_pos( int pos ){
	return ops[pos];
}

/* muda valor do operando pos para v */
void Quadrupla::set_ops( int pos, string v ){

	if(pos < 0 || pos > 3)
		cout <<"ERRO : Quadrupla::set_ops() : indice invalido" << endl;
	else
		ops[pos] = v;
}

/* retorna a quadrupla representada por s */
Quadrupla Quadrupla::stringToQuadrupla( string s ){

	//cout << "linha = " << s << endl;
	size_t found;
	found=s.find_first_of(":");

//	procuro por ":"
	if ( found != string::npos )
	{
		int first_letter = 0;

		while(s[first_letter] == '\t' || s[first_letter] == ' ' ) first_letter++;
		return Quadrupla( s.substr(first_letter, found ), VAZIO, VAZIO, VAZIO);
	}
	else{
		//		op, arg1, arg2, result
		//maximo de palavras possiveis numa instrucao
		string op[6];

		for(int i = 0; i < 6; i++) op[i] = VAZIO;

		int op_index = 0;

		char empty = ' ';
		unsigned int index = 0;

		//vou ate o primeiro caracter da quadrupla
		while( s[index] == empty || s[index] == '\t' || s[index] == 13) index++;

		int first_index = index;

		for (; index < s.length(); index++){

			if( s[index] == empty || index == s.length() - 1 || s[index] == '\t' ){

				if(index == s.length() - 1)
					op[op_index] = s.substr(first_index, index - first_index  + 1);
				else
					op[op_index] = s.substr(first_index, index - first_index  );


				//cout << " OP " << op_index << " :: " << op[op_index] << ";" << endl;
				op_index ++;

				if(index == s.length() - 1|| s[index] == '\n' || s[index] == EOF)
					break;

				while(s[index] == empty || s[index] == '\t' || s[index] == 13){
					index++;
				}
				//cout << "INDICE " << index << "		: " << s.length()<< endl;

				first_index = index;
				index --;
			}
		}

		//atualizo o marcador do inicio da proxima quadrupla
		//iffalse x < y goto L5
		if( op[0].compare("iffalse") == 0){
			if(op_index == 6)
				return Quadrupla( op[2], op[1], op[3], op[5]);
			//os dois abaixo NAO TENHO CERTEZA ERRO
			//iffalse a goto L6
			else if(op_index == 4)
				return Quadrupla( "!=", op[1], "0", op[3]);
			else{
				cout << "QUADRUPLA : " << s << "	NAO EXISTENTE" << endl;
				exit(0);
			}
		}
		else if(op[0].compare("if") == 0 ){
			if(op_index == 6) //iffalse i >= j goto L8
				return Quadrupla( op[2], op[1], op[3], op[5]);
			else if(op_index == 4)
				return Quadrupla( "==", op[1], "1", op[3]);
			else{
				cout << "QUADRUPLA : " << s << "	NAO EXISTENTE" << endl;
				exit(0);
			}
		}
		else if(op[0].compare("goto") == 0)
			return Quadrupla( op[0], op[1], VAZIO, VAZIO);
		//		x = t [ t1 ]
		else if(op[3].compare("[") == 0 && op[5].compare("]") == 0)
			return Quadrupla( "LOAD", op[2], op[4], op[0]);
		//		x [ t1 ] = t
		else if(op[1].compare("[") == 0 && op[3].compare("]") == 0)
			return Quadrupla( "STORE", op[2], op[5], op[0]);
		//a = a + 1
		else if(op_index == 5)
			return Quadrupla( op[3], op[2], op[4], op[0]);
		//a = minus 1
		else if(op_index == 4) // minus, 1, VAZIO, a
			return Quadrupla( op[2], op[3], VAZIO, op[0]);
		//a = t5
		else if(op_index == 3)
			return Quadrupla( op[1], op[2], VAZIO, op[0]);
		else{
			cout << "QUADRUPLA : " << s << "	NAO EXISTENTE" << endl;
			exit(0);
		}

	}
	return Quadrupla();

}

void Quadrupla::imprimeQuadrupla(){
//	cout <<"op			arg1			arg2			result" << ENDL;
	cout << op << "			" << ops[0] << "			" << ops[1] << "			" << ops[2] << endl;
}

/*=================================================================================================*/

Quadruplas::Quadruplas()
{
	quadruplas.resize(0);
}

Quadrupla Quadruplas::getQuadrupla( int pos )
{
	return quadruplas[pos];
}

void Quadruplas::addQuadrupla( Quadrupla q )
{
	quadruplas.push_back(q);
}

int Quadruplas::getNumQuadruplas()
{
	return quadruplas.size();
}

void Quadruplas::imprimeQuadruplas()
{
	Quadrupla q;
	cout << "Impressao das quadruplas" << endl;
	cout << "---------------------" << endl;
	cout <<"OP			ARG_1			ARG_2			RESULT" << endl;
	for ( unsigned int i = 0; i < quadruplas.size(); i++ )
	{
		q = quadruplas[i];
		q.imprimeQuadrupla();
	}
	cout << "---------------------" << endl << endl;
}
