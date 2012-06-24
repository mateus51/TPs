%{

extern YYSTYPE yylval;
extern YYLTYPE yylloc;


void updateLineInfo() {
	//extern int linha_atual, coluna_atual;
	//printf("updating line...\n  - previous: %d\n\n", linha_atual);
	//linha_atual = linha_atual + 1;
	//coluna_atual = 0;
	
	
	yylloc.first_line++;
	yylloc.last_line++;
	yylloc.first_column = yylloc.last_column = 0;
}

void updateColumnInfo(int total_chr) {
	//extern int coluna_atual;
	//printf("updating column...\n  - previous: %d\n  - delta: %d\n", coluna_atual, total_chr);
	//coluna_atual += total_chr;
	
	
	//yylloc.last_column = yylloc.first_column + total_chr - 1;
	
	yylloc.first_column = yylloc.last_column + 1;

	yylloc.last_column = yylloc.first_column + total_chr - 1;
}


int installToken(char *lex) {

	if (DBG) {
		//printf("\n\nLEX : %s(%d, %d)\n", lex, linha_atual, coluna_atual);
		printTable(symbol_table);
	}

	// if reading declarations
	if (!reading_code) {
		//printf("LEX: installing token '%s'\n  line: %d\n  f column: %d\n  l column: %d\n", lex, yylloc.first_line, yylloc.first_column, yylloc.last_column);
		return installId(symbol_table, lex, yylloc.first_line, yylloc.first_column);
	}
	else
		return getSymbol(symbol_table, lex);
}

void printLocInfo(char *lex) {
	printf("Location Info: '%s'\n  l: %d/%d\n  c: %d/%d\n", lex, yylloc.first_line, yylloc.last_line, yylloc.first_column, yylloc.last_column);
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
ADDOP               \+|-
MULOP               \*|\/
COMMA               ,
COLON               :
SEMICOLON           ;
NEWLINE            [\r\n\f]
SPACES             [ \t\v]+

%%
{NEWLINE}				 updateLineInfo();
{SPACES}				 updateColumnInfo(strlen(yytext));
{COMMA}                  updateColumnInfo(strlen(yytext)); return(COMMA);
{COLON}                  updateColumnInfo(strlen(yytext)); return(COLON);
{SEMICOLON}              updateColumnInfo(strlen(yytext)); return(SEMICOLON);
PROCEDURE                updateColumnInfo(strlen(yytext)); return(PROC);
sin                      updateColumnInfo(strlen(yytext)); return(SIN);
log                      updateColumnInfo(strlen(yytext)); return(LOG);
cos                      updateColumnInfo(strlen(yytext)); return(COS);
ord                      updateColumnInfo(strlen(yytext)); return(ORD);
abs                      updateColumnInfo(strlen(yytext)); return(ABS);
sqrt                     updateColumnInfo(strlen(yytext)); return(SQRT);
exp                      updateColumnInfo(strlen(yytext)); return(EXP);
eof                      updateColumnInfo(strlen(yytext)); return(EOFILE);
eoln                     updateColumnInfo(strlen(yytext)); return(EOLN);
chr                      updateColumnInfo(strlen(yytext)); return(CHR);
program                  updateColumnInfo(strlen(yytext)); return(PROGRAM);
integer                  updateColumnInfo(strlen(yytext)); return(INTEGER);
real                     updateColumnInfo(strlen(yytext)); return(REAL);
boolean                  updateColumnInfo(strlen(yytext)); return(BOOLEAN);
char                     updateColumnInfo(strlen(yytext)); return(CHAR);
value                    updateColumnInfo(strlen(yytext)); return(VALUE);
reference                updateColumnInfo(strlen(yytext)); return(REFERENCE);
begin                    updateColumnInfo(strlen(yytext)); return(BEGIN_TOK);
end                      updateColumnInfo(strlen(yytext)); return(END);
if                       updateColumnInfo(strlen(yytext)); return(IF);
then                     updateColumnInfo(strlen(yytext)); return(THEN);
else                     updateColumnInfo(strlen(yytext)); return(ELSE);
repeat                   updateColumnInfo(strlen(yytext)); return(REPEAT);
until                    updateColumnInfo(strlen(yytext)); return(UNTIL);
read                     updateColumnInfo(strlen(yytext)); return(READ);
write                    updateColumnInfo(strlen(yytext)); return(WRITE);
false                    updateColumnInfo(strlen(yytext)); return(FALSE);
true                     updateColumnInfo(strlen(yytext)); return(TRUE);
div						 updateColumnInfo(strlen(yytext)); return(DIV);
mod						 updateColumnInfo(strlen(yytext)); return(MOD);
and						 updateColumnInfo(strlen(yytext)); return(AND);
or 						 updateColumnInfo(strlen(yytext)); return(OR);
:=                       updateColumnInfo(strlen(yytext)); return(ATRIB);
\(                       updateColumnInfo(strlen(yytext)); return(LPAR);
\)                       updateColumnInfo(strlen(yytext)); return(RPAR);
NOT                      updateColumnInfo(strlen(yytext)); return(NOT);
\<						 updateColumnInfo(strlen(yytext)); return(LT);
>						 updateColumnInfo(strlen(yytext)); return(GT);
>=						 updateColumnInfo(strlen(yytext)); return(GE);
\<=						 updateColumnInfo(strlen(yytext)); return(LE);
=						 updateColumnInfo(strlen(yytext)); return(EQ);
!=						 updateColumnInfo(strlen(yytext)); return(NE);
{ADDOP}                  updateColumnInfo(strlen(yytext)); yylval.intval = yytext[0]; return(ADDOP);
{MULOP}                  updateColumnInfo(strlen(yytext)); yylval.intval = yytext[0]; return(MULOP);
{INTEGER_CONSTANT}       updateColumnInfo(strlen(yytext)); yylval.intval = atoi(yytext); return(INTEGER_CONSTANT);
{REAL_CONSTANT}          updateColumnInfo(strlen(yytext)); yylval.realval = (double) atof(yytext); return(REAL_CONSTANT);
{CHAR_CONSTANT}          updateColumnInfo(strlen(yytext)); yylval.intval = yytext[0]; return(CHAR_CONSTANT);
{ID}                     updateColumnInfo(strlen(yytext)); yylval.addr = installToken(yytext); return(ID);
%%
#ifndef yywrap
yywrap() { return 1; }
#endif

