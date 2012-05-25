%{

extern YYSTYPE yylval;

int linha_atual = 0;
int coluna_atual = 0;
int total_tokens = 0;


void installToken(char *lex) {
//	if (!symbol_table->initialized)
//		printf("Table NOT initialized!!\n");

//	printf("\n\nLEX : %s(%d, %d)\n", lex, linha_atual, coluna_atual);

	installId(symbol_table, lex, linha_atual, coluna_atual);
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
{SPACES}				 coluna_atual += strlen(yytext);
{COMMA}                  coluna_atual += strlen(yytext); return(COMMA);
{COLON}                  coluna_atual += strlen(yytext); return(COLON);
{SEMICOLON}              coluna_atual += strlen(yytext); return(SEMICOLON);
PROCEDURE                coluna_atual += strlen(yytext); return(PROC);
sin                      coluna_atual += strlen(yytext); return(SIN);
log                      coluna_atual += strlen(yytext); return(LOG);
cos                      coluna_atual += strlen(yytext); return(COS);
ord                      coluna_atual += strlen(yytext); return(ORD);
abs                      coluna_atual += strlen(yytext); return(ABS);
sqrt                     coluna_atual += strlen(yytext); return(SQRT);
exp                      coluna_atual += strlen(yytext); return(EXP);
eof                      coluna_atual += strlen(yytext); return(EOFILE);
eoln                     coluna_atual += strlen(yytext); return(EOLN);
program                  coluna_atual += strlen(yytext); return(PROGRAM);
integer                  coluna_atual += strlen(yytext); return(INTEGER);
real                     coluna_atual += strlen(yytext); return(REAL);
boolean                  coluna_atual += strlen(yytext); return(BOOLEAN);
char                     coluna_atual += strlen(yytext); return(CHAR);
value                    coluna_atual += strlen(yytext); return(VALUE);
reference                coluna_atual += strlen(yytext); return(REFERENCE);
begin                    coluna_atual += strlen(yytext); return(BEGIN_TOK);
end                      coluna_atual += strlen(yytext); return(END);
if                       coluna_atual += strlen(yytext); return(IF);
then                     coluna_atual += strlen(yytext); return(THEN);
else                     coluna_atual += strlen(yytext); return(ELSE);
repeat                   coluna_atual += strlen(yytext); return(REPEAT);
until                    coluna_atual += strlen(yytext); return(UNTIL);
read                     coluna_atual += strlen(yytext); return(READ);
write                    coluna_atual += strlen(yytext); return(WRITE);
false                    coluna_atual += strlen(yytext); return(FALSE);
true                     coluna_atual += strlen(yytext); return(TRUE);
:=                       coluna_atual += strlen(yytext); return(ATRIB);
\(                       coluna_atual += strlen(yytext); return(LPAR);
\)                       coluna_atual += strlen(yytext); return(RPAR);
NOT                      coluna_atual += strlen(yytext); return(NOT);
\<						 coluna_atual += strlen(yytext); return(LT);
>						 coluna_atual += strlen(yytext); return(GT);
>=						 coluna_atual += strlen(yytext); return(GE);
\<=						 coluna_atual += strlen(yytext); return(LE);
=						 coluna_atual += strlen(yytext); return(EQ);
!=						 coluna_atual += strlen(yytext); return(NE);
{ADDOP}                  yylval.integer = yytext[0]; coluna_atual += strlen(yytext); return(ADDOP);
{MULOP}                  yylval.integer = yytext[0]; coluna_atual += strlen(yytext); return(MULOP);
{INTEGER_CONSTANT}       yylval.integer = atoi(yytext); coluna_atual += strlen(yytext); return(INTEGER_CONSTANT);
{REAL_CONSTANT}          yylval.real = (int) atof(yytext); coluna_atual += strlen(yytext); return(REAL_CONSTANT);
{CHAR_CONSTANT}          yylval.integer = yytext[0]; coluna_atual += strlen(yytext); return(CHAR_CONSTANT);
{ID}                     installToken(yytext); yylval.string = strdup(yytext); coluna_atual += strlen(yytext); return(ID);
%%
#ifndef yywrap
yywrap() { return 1; }
#endif

