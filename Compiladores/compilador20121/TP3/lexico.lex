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

// FIXME: Procurar token na tabela antes de adicionar um novo.
void installToken(char *tok, char *lex) {
	if (!sym_table->initialized)
		initTable(sym_table);

	if (!strcmp("ID", tok)) {
	    total_tokens++;
	    Token *token = newToken(tok, lex, linha_atual, coluna_atual);
	    addToken(sym_table, token);
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
{COMMA}                  installToken("COMMA", yytext); return(COMMA);
{COLON}                  installToken("COLON", yytext); return(COLON);
{SEMICOLON}              installToken("SEMICOLON", yytext); return(SEMICOLON);
PROCEDURE                installToken("PROC", yytext); return(PROC);
sin                      installToken("SIN", yytext); return(SIN);
log                      installToken("LOG", yytext); return(LOG);
cos                      installToken("COS", yytext); return(COS);
ord                      installToken("ORD", yytext); return(ORD);
abs                      installToken("ABS", yytext); return(ABS);
sqrt                     installToken("SQRT", yytext); return(SQRT);
exp                      installToken("EXP", yytext); return(EXP);
eof                      installToken("EOFILE", yytext); return(EOFILE);
eoln                     installToken("EOLN", yytext); return(EOLN);
program                  installToken("PROGRAM", yytext); return(PROGRAM);
integer                  installToken("INTEGER", yytext); return(INTEGER);
real                     installToken("REAL", yytext); return(REAL);
boolean                  installToken("BOOLEAN", yytext); return(BOOLEAN);
char                     installToken("CHAR", yytext); return(CHAR);
value                    installToken("VALUE", yytext); return(VALUE);
reference                installToken("REFERENCE", yytext); return(REFERENCE);
begin                    installToken("BEGIN_TOK", yytext); return(BEGIN_TOK);
end                      installToken("END", yytext); return(END);
if                       installToken("IF", yytext); return(IF);
then                     installToken("THEN", yytext); return(THEN);
else                     installToken("ELSE", yytext); return(ELSE);
repeat                   installToken("REPEAT", yytext); return(REPEAT);
until                    installToken("UNTIL", yytext); return(UNTIL);
read                     installToken("READ", yytext); return(READ);
write                    installToken("WRITE", yytext); return(WRITE);
false                    installToken("FALSE", yytext); return(FALSE);
true                     installToken("TRUE", yytext); return(TRUE);
:=                       installToken("ATRIB", yytext); return(ATRIB);
\(                       installToken("LPAR", yytext); return(LPAR);
\)                       installToken("RPAR", yytext); return(RPAR);
NOT                      installToken("NOT", yytext); return(NOT);
\<						 installToken("LT", yytext); return(LT);
>						 installToken("GT", yytext); return(GT);
>=						 installToken("GE", yytext); return(GE);
\<=						 installToken("LE", yytext); return(LE);
=						 installToken("EQ", yytext); return(EQ);
!=						 installToken("NE", yytext); return(NE);
{ADDOP}                  yylval.integer = yytext[0]; installToken("ADDOP", yytext); return(ADDOP);
{MULOP}                  yylval.integer = yytext[0]; installToken("MULOP", yytext); return(MULOP);
{INTEGER_CONSTANT}       yylval.integer = atoi(yytext); installToken("INTEGER_CONSTANT", yytext); return(INTEGER_CONSTANT);
{REAL_CONSTANT}          yylval.real = (int) atof(yytext); installToken("REAL_CONSTANT", yytext); return(REAL_CONSTANT);
{CHAR_CONSTANT}          yylval.integer = yytext[0]; installToken("CHAR_CONSTANT", yytext); return(CHAR_CONSTANT);
{ID}                     yylval.string = strdup(yytext); installToken("ID", yytext); return(ID);
%%
#ifndef yywrap
yywrap() { return 1; }
#endif

