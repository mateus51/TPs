/*
 * tradutor.cpp
 *
 *  Created on: 30/11/2009
 *      Author: rogerfsg
 */

#include "tradutor.hpp"
#include <fstream>

void Tradutor::imprimeProgramaTAM( string file_name )
{
	ofstream output( file_name.c_str(), ios::out );
	cout << "\n\nCT		Impressao do Programa TAM					" << endl;
	cout << "------------------------" << endl;

	for ( unsigned int i = 0; i < instrucoesTAM.size(); i++ )
	{
		cout << i << "		"<< instrucoesTAM[i] << endl;
		output << instrucoesTAM[i] ;
		if( instrucoesTAM[i].compare("HALT") == 0) break;
	}

	cout << "------------------------" << endl;
	output.close();
}

Tradutor::Tradutor()	:
						instrucoesTAM(MAX_DATA)
						{
	SB = 0;
	CT = 0; // numero de instrucoes ate o momento
	ST = 0;
						}

string Tradutor::getInstrucao(){
	string saida;
	return saida;
}

void Tradutor::setInstrucao( string s ){

}

void Tradutor::traduzQuadruplas( Quadruplas Q ){
	tabela.Entrada_Bloco();
	//	Para toda quadrupla
	//cout << "Traduz Quadruplas" << endl;
	for(unsigned int i = 0 ; i < Q.quadruplas.size(); i++){
		traduzQuadrupla(Q.quadruplas[i]);
	}

	Quadrupla finaliza(VAZIO, VAZIO, VAZIO, VAZIO);
	traduzQuadrupla(finaliza);
	//corrigindo labels pendentes
	int c; string cend;
	for ( unsigned int i = 0; i < instrucoesTAM.size(); i++ ){
		string inst = instrucoesTAM[i];

		if(inst[0]  == 'A' ){ //se for label pendente
			//se A pendentede em JUMPIF
			//se B pendente em GOTO
			inst[0] = 'L';
			if((c = tabela.Get_Entry(inst.c_str()) )!= -1){
				cend = tabela.PegaAtributo(c);

				instrucoesTAM[i] = "JUMPIF (1) " + cend + " [CB]";

				//cout << "NOVA INST1: " << instrucoesTAM[i] << endl;

			}
		}
		else if(inst[0]  == 'B' ){ //se for label pendente
			inst[0] = 'L';
			//se A pendentede em JUMPIF
			//se B pendente em GOTO
			if((c = tabela.Get_Entry(inst.c_str()) )!= -1){
				cend = tabela.PegaAtributo(c);
				instrucoesTAM[i] = "goto " + cend ;
				//cout << "NOVA INST2: " << instrucoesTAM[i] << endl;

			}
		}

	}

	tabela.Saida_Bloco();
}


void Tradutor::traduzQuadrupla( Quadrupla q ){
	int a, b, c;

	string aend, bend ,cend;

	if(q.op.find_first_of("+*-/=") != string::npos || q.op.compare("minus") == 0){
		//		b = 1 operador = ops[0]
		if((b = tabela.Get_Entry(q.ops[0].c_str() )) != -1){
			bend = tabela.PegaAtributo(b);
			adicionaInstrucao("LOAD (1) " + bend);
		}
		else{
			//coloco 0 na pilha
			b = atoi( q.ops[0].c_str() );
			if(b > 0)
				adicionaInstrucao("LOADL " + Int_to_String(b));
			else
				adicionaInstrucao("LOADL 0");

		}

		if(q.op.compare("=") != 0){
			//		ops[1] = 2 operador
			if((c = tabela.Get_Entry(q.ops[1].c_str())) != -1){
				cend = tabela.PegaAtributo(c);
				adicionaInstrucao("LOAD (1) " + cend + " [SB]");
			}
			else{
				c = atoi(q.ops[1].c_str());
				if(c > 0)
					adicionaInstrucao("LOADL " + Int_to_String(c));
				else	//coloco 0 na pilha
					adicionaInstrucao("LOADL 0");
			}
		}

		//Se nao se encontra na tabela entao adiciono-o, somente para o termo que recebe o Resultado
		if(q.op.compare("=") != 0)
			adicionaInstrucao("CALL " + operacaoTAM(q.get_operador()) );

		//		Segundo operado
		if((a = tabela.Get_Entry(q.ops[2].c_str())) != -1){
			aend = tabela.PegaAtributo(a);
			adicionaInstrucao("STORE (1) " + aend + " [SB]");
		}
		else{
			adicionaVariavel(q.ops[2], 1, false);
		}
	}
	//if if i < j goto l , ou ifelse ..
	else if(q.op.compare("!=") == 0 || q.op.compare("==") == 0 ||
			q.op.compare("<=") == 0 ||q.op.compare("<") == 0 || q.op.compare(">") == 0 || q.op.compare(">=") == 0 ){
		//cout << " TraduzQuadrupla 2" << endl;
		//operador i < j
		//i
		if((a = tabela.Get_Entry(q.ops[0].c_str() )) != -1){
			aend = tabela.PegaAtributo(a);
			adicionaInstrucao("LOAD (1) " + aend + " [SB]");
		}
		else{
			//coloco 0 na pilha
			a = atoi(q.ops[0].c_str());
			if( a  > 0)
				adicionaInstrucao("LOADL " + Int_to_String(a));
			else
				adicionaInstrucao("LOADL 0");
		}

		//j
		if((b = tabela.Get_Entry(q.ops[1].c_str())) != -1){
			bend = tabela.PegaAtributo(b);
			adicionaInstrucao("LOAD (1) " + bend + " [SB]");
		}
		else{
			//coloco 0 na pilha
			b = atoi(q.ops[1].c_str());
			if(b > 0)
				adicionaInstrucao("LOADL " + Int_to_String(b));
			else
				adicionaInstrucao("LOADL 0");
		}

		//Se nao se encontra na tabela entao adiciono-o, somente para o termo que recebe o Resultado
		//operacao da condicao
		adicionaInstrucao("CALL " + operacaoTAM(q.get_operador()) );

		//ops[2] = endereco da label do desvio
		//endereco do goto esta em c
		if((c = tabela.Get_Entry(q.ops[2].c_str())) != -1){

			cend = tabela.PegaAtributo(c);
			//			cout << "LABEL : " << q.ops[2] << "			c :"<< cend << endl;
			adicionaInstrucao("JUMPIF (1) " + cend + " [CB]");

		}
		else{ //para as labels ainda nao definidas, nao seto essa instrucao
			string inst = q.ops[2];
			inst[0] = 'A';
			adicionaInstrucao( inst);

			//			cout << "ERRO LABEL : " << c << " INDEFINIDA " << endl;
			//			char * atributo ;
			//			sprintf (atributo, "%d", ST);
			//			ST++;
			//			//pega atributo
			//			tabela.Instala(q.ops[2].c_str(), atributo);
		}
	}
	else if(q.op.compare("goto") == 0){
		//cout << " TraduzQuadrupla 3" << endl;
		//pego o endereco do label do goto = ops[0]
		if((a = tabela.Get_Entry(q.ops[0].c_str())) != -1){
			aend = tabela.PegaAtributo(a);
			adicionaInstrucao("LOADL " + aend);
			adicionaInstrucao("JUMPI" );
		}
		else{
			string inst = q.ops[0];
			inst[0] = 'B';
			adicionaInstrucao( inst);

			//			cout << "ERRO LABEL : " << inst << " INDEFINIDA" <<endl;
		}
	}
	//		x = t [ t1 ]
	//  else if(op[3].compare("[") == 0 && op[5].compare("]"))
	//	return Quadrupla( "LOAD", op[2], op[4], op[0]);
	//op[0] = t
	//op[1] = t1
	//op[2] = x
	else if(q.op.compare("LOAD") == 0){
		//cout << " TraduzQuadrupla 5" << endl;
		//cout << " TraduzQuadrupla 5.1" << endl;

		int endereco = 0 ;
		//t1
		if((b = tabela.Get_Entry(q.ops[1].c_str())) != -1){
			//cout << " TraduzQuadrupla 5.2" << endl;
			bend = tabela.PegaAtributo(b);
			//somo t + t1
			endereco += atoi(bend.c_str());
		}

		//t
		if((a = tabela.Get_Entry(q.ops[0].c_str())) != -1){
			aend = tabela.PegaAtributo(a);
			endereco = atoi(aend.c_str());
			//cout << "End.:" << endereco << endl;
		}
		else{ //adiciono a variavel na tabela
			adicionaVariavel(q.ops[0], MAX_ARRAY_SIZE_INT, true);
		}

		//cout << " TraduzQuadrupla 5.0" << endl;
		adicionaInstrucao("LOAD ( 1 ) " + Int_to_String(endereco) + " [SB]");
		//cout << " TraduzQuadrupla 5.1" << endl;

		//x
		//cout << " TraduzQuadrupla 5.3" << endl;
		if((c = tabela.Get_Entry(q.ops[2].c_str())) != -1){
			//cout << " TraduzQuadrupla 5.2 : " <<  c << endl;
			cend = tabela.PegaAtributo(c);
			adicionaInstrucao("STORE (1) " +  cend + " [SB]");
			//cout << " TraduzQuadrupla 5.4" << endl;
		}
		else{ //adiciono a variavel na tabela
			//cout <<"OP = " << q.ops[2] << endl;
			//cout << " TraduzQuadrupla 5.5" << endl;
			adicionaVariavel(q.ops[2], 1, false);
		}

		//cout << " TraduzQuadrupla 5 SAIU" << endl;
	}
	else if(q.op.find_first_of("L")  != string::npos){ //se for label

		string atributo ;
		atributo = Int_to_String(CT);

		//marco a localizacao como atributo da label
		tabela.Instala(q.op.c_str(), atributo.c_str());
	}
	//		x [ t1 ] = t
	// return Quadrupla( "STORE", op[2], op[5], op[0]);
	else if(q.op.compare("STORE") == 0){
		//ops[0] = t1
		//ops[1] = t
		//ops[2] = x
		//cout << " TraduzQuadrupla 6 " << endl;
		//ops[1] = t
		if((c = tabela.Get_Entry(q.ops[1].c_str())) != -1){
			cend = tabela.PegaAtributo(c);
			//			cout << " CEND : " << cend << "			c : " << c<< endl;

			adicionaInstrucao("LOAD (1)" + cend + " [SB]");
		}
		else adicionaInstrucao("LOADL 0" );
		//ops[2] = x
		int endereco = 0;
		if((a = tabela.Get_Entry(q.ops[2].c_str())) != -1){

			aend = tabela.PegaAtributo(a);
			endereco = atoi(aend.c_str());
		}
		else{ //adiciono a variavel na tabela
			//GRAVO X
			adicionaVariavel(q.ops[2], MAX_ARRAY_SIZE_INT, true);
		}

		//ops[0] = t1
		if((b = tabela.Get_Entry(q.ops[0].c_str())) != -1){
			bend = tabela.PegaAtributo(b);
			endereco += atoi(bend.c_str());
		}
		else{ //adiciono a variavel na tabela
			adicionaVariavel(q.ops[0], 1, true);
		}
		adicionaInstrucao("STORE (1) " + Int_to_String(endereco) + " [SB]" );
	}
	else if((unsigned int )q.op.compare(VAZIO) == 0){ //se chegar uma quadrupla com op vazia significa que as operacoes
		//acabaram
		adicionaInstrucao("HALT" );
	}
	else
		cout << "Instrucao nao encontradao" << endl;


}

void Tradutor::adicionaVariavel(string operador, int tamanho_enter, bool aumenta_pilha){
	//cout << "Adiciona Variavel " << endl;
	string tamanho = Int_to_String(tamanho_enter);

	if(aumenta_pilha == true)
		adicionaInstrucao("PUSH " + tamanho);
	string atributo = Int_to_String(ST);
	//cout << "Instala 2 : ST : " << ST << "		 : tamanho : " << tamanho_enter << endl;
	ST += tamanho_enter;
	//gravo t1

	tabela.Instala(operador.c_str(), atributo.c_str());

	adicionaInstrucao("STORE (" + tamanho +  ") " +  atributo + " [SB]");
};

string Tradutor::Int_to_String(int i){

	std::string s;
	std::stringstream out;
	out << i;
	s = out.str();

	return s;
}

string Tradutor::operacaoTAM(string op){
	string saida;
	if(op.compare(">=") == 0) return "ge";

	else if(op.compare("==") == 0) return "eq";

	else if(op.compare("!=") == 0) return "ne";

	else if(op.compare("<=") == 0) return "le";

	else if(op.compare("<") == 0) return "lt";

	else if(op.compare(">") == 0) return "gt";

	else if(op.compare("*") == 0) return "mult";

	else if(op.compare("/") == 0) return "div";

	else if(op.compare("+") == 0) return "succ";

	else if(op.compare("-") == 0) return "sub";

	//	else if(op.compare("=") == 0) return "id";

	else if(op.compare("minus") == 0) return "neg";

	else return "ERROR_OPERADOR : " + op + ";";

}

void Tradutor::adicionaInstrucao( string inst ){
	//	conta a adicao da nova instrucao
	//cout << "Instrucao : "<< inst << endl;

	instrucoesTAM[CT] = inst ;

	CT++;


}




