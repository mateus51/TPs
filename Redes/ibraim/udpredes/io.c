#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
//#include <ctype.h>			//biblioteca da funcao tolower
#include "io.h"
//#define TAMPALAVRA 30

///////////////////////////////////////////////////////////////////////////////////////////////////
/*void LePalavra(char *word, FILE *arquivo){
    char *picaStr;
    fscanf(arquivo, "%s", word);
    if(strlen(word)>0){
        picaStr=strtok(word," ,.<>;:/?|'!@#$%&*()-_=+[{]}"); //tira simbolos da palavra
        int i;
        for(i=0; i<strlen(picaStr); i++) picaStr[i]=tolower(picaStr[i]); //a palavra fica toda em minuscula.
        strcpy(word, picaStr);
    }
}*/
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
void PegaPalavra(char *string, char *palavra){
	char *picaStr;	
	picaStr=strtok(string," ,.<>;:/?|'!@#$%&*()-_=+[{]}");
	int i;
	for(i=0; i<strlen(picaStr); i++) picaStr[i]=tolower(picaStr[i]); //a palavra fica toda em minuscula.
	strcpy(palavra, picaStr);
}
*/
///////////////////////////////////////////////////////////////////////////////////////////////////
/*void LeQtLinhas(FILE *arquivo, int *qtLinhas){
   	int tam=100;			//pode-se atribuir a tam uma constante, TAMSTRINGMAX.
    char *string=malloc(tam*sizeof(char));
    (*qtLinhas)=0;
    fgets(string, tam, arquivo);
    while(!feof(arquivo)){
       if(strlen(string)>1) (*qtLinhas)++;
       fgets(string, tam, arquivo);
    }
	rewind(arquivo);
	free(string);
}*/
///////////////////////////////////////////////////////////////////////////////////////////////////
/*void LeString(char *string, int tam, FILE *arquivo){
	fgets(string, tam, arquivo);
}*/
///////////////////////////////////////////////////////////////////////////////////////////////////
void LimpaString(char *string, int tam){
	while(tam>0){
		tam--;
		string[tam]=0;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
void PegaPalavra(char *string, int tam, char *word, int espacos){
	if(strlen(string)>0){
		char *picaStr=malloc(tam*sizeof(char));
		int i, j;

		for(i=0; espacos>=0 && i<strlen(string); i++){
			LimpaString(picaStr, tam);
			for(j=0; string[i]!=' ' && (32<=string[i] && string[i]<=126); j++){
				picaStr[j]=string[i];
				i++;
			}
			espacos--;
		}
		strcpy(word, picaStr);
		free(picaStr);
	}
}
*/
///////////////////////////////////////////////////////////////////////////////////////////////////
/*void TrataOpcoes(char *opcao1, char *opcao2){
	if(strcmp("-i", opcao1) || strcmp("-o", opcao2)){ printf("\nERRO: Opcoes invalidas ou invertidas.\n"); exit(1);}
}*/
///////////////////////////////////////////////////////////////////////////////////////////////////

