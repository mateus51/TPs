/*
 * main.cpp
 *
 *  Created on: 30/11/2009
 *      Author: rogerfsg
 */

#include "quadruplas.hpp"
#include "tabela.hpp"
#include "tradutor.hpp"

#include <fstream>

#include <stdlib.h>
#include <stdio.h>
using namespace std;

void leArqEntrada( string file_name, Quadruplas &Q )
{
	string s;
	Quadrupla q;

	ifstream input( file_name.c_str(), ios::in );

	if ( !input )
	{
		cout << "O arquivo " << file_name << " nao existe. O programa terminara agora!" << endl;
		exit(1);
	}
	else
	{

		while ( getline( input, s ) )
		{
			size_t found = s.find_first_of(":");

			int first_index = 0;
			bool validade = false;

			if(found != string::npos){

				unsigned int last_index = found + 1;

				while (last_index < s.length())
				{

					string palavra = s.substr(first_index, last_index - first_index + 1);

					q = q.stringToQuadrupla( palavra );
					Q.addQuadrupla( q );

					first_index = found + 1;

					while(s[first_index] == '\t' || s[first_index] == ' ' )
						first_index++;

					found = s.find_first_of(":",found + 1);

					//atualizo o marcador do inicio da proxima quadrupla
					if(last_index == s.length() - 1) break;
					else{
						if(found == string::npos)			last_index = s.length() - 1;
						else 								last_index = found + 1;
					}

					validade = true;
				}
			}
			else{
				if(s.length() > 0 ){
					//gera a quadrupla com a lnha inteira
					q = q.stringToQuadrupla( s );
					Q.addQuadrupla( q );
				}
			}
		}
	}
	input.close();
}

int main( int argc, char *argv[] )
{
	string file_name_in;
	string file_name_out;
	Tradutor T;
	Quadruplas Q;
	if( argc < 3 )
	{
		cout << "Escreva o nome do arquivo de entrada: " << endl;
		cin >> file_name_in;
		cout << "Escreva o nome do arquivo de saida: " << endl;
		cin >> file_name_out;
	}
	else
	{
		file_name_in = argv[1];
		file_name_out = argv[2];
	}

	string interpretador = "java teste.Main < " + file_name_in + " > Codigo_Intermediario";
	cout << "Interpretador : " << interpretador << endl;
	system (interpretador.c_str());

	leArqEntrada( "Codigo_Intermediario", Q );
	cout << endl;
	Q.imprimeQuadruplas();

	T.traduzQuadruplas( Q );
	T.imprimeProgramaTAM( file_name_out );
	cout << endl;
	return 0;
}
