%{
#include "sym_table.c"

extern YYSTYPE yylval;

/* Tabela de símbolos. Declarada globalmente para estar disponível
 * tanto para o Lex quanto para o Yacc.
 * Foi declarado dessa forma para o endereço ser conhecido
 * em tempo de compilação. */
SymbolTable table = DEFAULT_TABLE;
SymbolTable *sym_table = (SymbolTable*) &table;
//sym_table->initialized = False;

int linha_atual = 0;
int coluna_atual = 0;
int total_tokens = 0;

/* Considera-se que a primeira posicao da tabela eh a de indice 0. L eh o final da arvore binaria */
 L = 0;
 Raiz = -1;
 nivel = 1; /* O primeiro nivel é o 1 */
 escopo[nivel] = 0;   /* escopo[1] contem o indice do primeiro elemento */

// FIXME: Procurar token na tabela antes de adicionar um novo.
void installToken(char *tok, char *lex) {
	if (!sym_table->initialized)
		initTable(sym_table);

	if (!strcmp("ID", tok)) {
	    total_tokens++;
	    Token *token = newToken(tok, lex, linha_atual, coluna_atual);
	    addToken(sym_table, token);
	    printf("\n\n\n\ninstalled token! linha atual:  %d\n", linha_atual);
	    printf("\n\n\n\n                 token->linha: %d\n\n", token->linha);
    }
	coluna_atual += strlen(lex);
}

%}
LETTER              [a-zA-Z]
DIGIT               [0-9]
ID                  {LETTER}({LETTER}|{DIGIT})*
UNSIGNED_INTEGER    {DIGIT}{DIGIT}*
SIGN                (\+|-)?
SCALE_FACTOR        E({SIGN})({UNSIGNED_INTEGER})
UNSIGNED_REAL       {UNSIGNED_INTEGER}(\.({DIGIT})*)?({SCALE_FACTOR})?
INTEGER_CONSTANT    {UNSIGNED_INTEGER}
REAL_CONSTANT       {UNSIGNED_REAL}
CHAR_CONSTANT       '.'
RELOP               =|<|<=|>|>=|!=
ADDOP               \+|-|or
MULOP               \*|\/|div|mod|and
COMMA               ,
COLON               :
SEMICOLON           ;
NEWLINE             \n
SPACES             [\ \t\b\012]+
LT				   <
%%
{NEWLINE}				 linha_atual++; coluna_atual = 0;
{SPACES}				 installToken("SPACES", yytext);
{COMMA}                   return(COMMA);
{COLON}                   return(COLON);
{SEMICOLON}               return(SEMICOLON);
PROCEDURE                 return(PROC);
sin                       return(SIN);
log                       return(LOG);
cos                       return(COS);
ord                       return(ORD);
abs                       return(ABS);
sqrt                      return(SQRT);
exp                       return(EXP);
eof                       return(EOFILE);
eoln                      return(EOLN);
program                   return(PROGRAM);
integer                   return(INTEGER);
real                      return(REAL);
boolean                   return(BOOLEAN);
char                      return(CHAR);
value                     return(VALUE);
reference                 return(REFERENCE);
begin                     return(BEGIN_TOK);
end                       return(END);
if                        return(IF);
then                      return(THEN);
else                      return(ELSE);
repeat                    return(REPEAT);
until                     return(UNTIL);
read                      return(READ);
write                     return(WRITE);
false                     return(FALSE);
true                      return(TRUE);
:=                        return(ATRIB);
\(                        return(LPAR);
\)                        return(RPAR);
NOT                       return(NOT);
\<						  return(LT);
>						  return(GT);
>=						  return(GE);
\<=						  return(LE);
=						  return(EQ);
!=						  return(NE);
{ADDOP}                  yylval.integer = yytext[0];  return(ADDOP);
{MULOP}                  yylval.integer = yytext[0];  return(MULOP);
{INTEGER_CONSTANT}       yylval.integer = atoi(yytext);  return(INTEGER_CONSTANT);
{REAL_CONSTANT}          yylval.real = (int) atof(yytext);  return(REAL_CONSTANT);
{CHAR_CONSTANT}          yylval.integer = yytext[0];  return(CHAR_CONSTANT);
{ID}                     yylval.string = strdup(yytext);  return(ID);
%%
#ifndef yywrap
yywrap() { return 1; }
#endif

