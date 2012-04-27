%{
#include <string.h>



//#include "y.tab.h"
extern YYSTYPE yylval;

typedef struct Token {
    char *token;
    char *lexema;
    int linha;
    int coluna;
} Token;
int linha_atual = 0;
int coluna_atual = 0;
Token *tokens[100];// = (Token*) malloc(sizeof(Token) * 100);
int total_tokens = 0;
Token* getToken(char *tok, char *lex) {
    Token *token = (Token*) malloc(sizeof(Token));
    token->linha = linha_atual;
    token->coluna = coluna_atual;
    token->token = (char*) malloc(sizeof(char) * (strlen(tok)+1));
    strcpy(token->token, tok);
    token->lexema = (char*) malloc(sizeof(char) * (strlen(lex)+1));
    strcpy(token->lexema, lex);
    return token;
}
Token* installToken(char *tok, char *lex) {
    total_tokens++;
    //tokens = (Token*) realloc(tokens, sizeof(Token) * total_tokens);
    //tokens[total_tokens-1] = getToken(tok, lex);
    return getToken(tok, lex);
}
void printTokens() {
    int i = 0;
    //printf("total_tokens = %d\n", total_tokens);
    printf("%16s %16s %16s %16s\n\n", "TOKEN", "LEXEMA", "LINHA", "COLUNA");
    for (i = 0; i < total_tokens; i++) {
        printf("%16s %16s %16d %16d\n", tokens[i]->token, tokens[i]->lexema, tokens[i]->linha, tokens[i]->coluna);
    }
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
{NEWLINE}               ECHO; linha_atual++; coluna_atual = 0;
{SPACES}                ECHO; coluna_atual += strlen(yytext);
{COMMA}                 ECHO; coluna_atual += strlen(yytext); return(COMMA);
{COLON}                 ECHO; coluna_atual += strlen(yytext); return(COLON);
{SEMICOLON}             ECHO; coluna_atual += strlen(yytext); return(SEMICOLON);
PROCEDURE               ECHO; coluna_atual += strlen(yytext); return(PROC);
sin                     ECHO; coluna_atual += strlen(yytext); return(SIN);
log                     ECHO; coluna_atual += strlen(yytext); return(LOG);
cos                     ECHO; coluna_atual += strlen(yytext); return(COS);
ord                     ECHO; coluna_atual += strlen(yytext); return(ORD);
abs                     ECHO; coluna_atual += strlen(yytext); return(ABS);
sqrt                    ECHO; coluna_atual += strlen(yytext); return(SQRT);
exp                     ECHO; coluna_atual += strlen(yytext); return(EXP);
eof                     ECHO; coluna_atual += strlen(yytext); return(EOFILE);
eoln                    ECHO; coluna_atual += strlen(yytext); return(EOLN);
program                 ECHO; coluna_atual += strlen(yytext); return(PROGRAM);
integer                 ECHO; coluna_atual += strlen(yytext); return(INTEGER);
real                    ECHO; coluna_atual += strlen(yytext); return(REAL);
boolean                 ECHO; coluna_atual += strlen(yytext); return(BOOLEAN);
char                    ECHO; coluna_atual += strlen(yytext); return(CHAR);
value                   ECHO; coluna_atual += strlen(yytext); return(VALUE);
reference               ECHO; coluna_atual += strlen(yytext); return(REFERENCE);
begin                   ECHO; coluna_atual += strlen(yytext); return(BEGIN_TOK);
end                     ECHO; coluna_atual += strlen(yytext); return(END);
if                      ECHO; coluna_atual += strlen(yytext); return(IF);
then                    ECHO; coluna_atual += strlen(yytext); return(THEN);
else                    ECHO; coluna_atual += strlen(yytext); return(ELSE);
repeat                  ECHO; coluna_atual += strlen(yytext); return(REPEAT);
until                   ECHO; coluna_atual += strlen(yytext); return(UNTIL);
read                    ECHO; coluna_atual += strlen(yytext); return(READ);
write                   ECHO; coluna_atual += strlen(yytext); return(WRITE);
false                   ECHO; coluna_atual += strlen(yytext); return(FALSE);
true                    ECHO; coluna_atual += strlen(yytext); return(TRUE);
:=                      ECHO; coluna_atual += strlen(yytext); return(ATRIB);
\(                      ECHO; coluna_atual += strlen(yytext); return(LPAR);
\)                      ECHO; coluna_atual += strlen(yytext); return(RPAR);
NOT                     ECHO; coluna_atual += strlen(yytext); return(NOT);
\<						ECHO; coluna_atual += strlen(yytext); return(LT);
>						ECHO; coluna_atual += strlen(yytext); return(GT);
>=						ECHO; coluna_atual += strlen(yytext); return(GE);
\<=						ECHO; coluna_atual += strlen(yytext); return(LE);
=						ECHO; coluna_atual += strlen(yytext); return(EQ);
!=						ECHO; coluna_atual += strlen(yytext); return(NE);
{ADDOP}                 ECHO; coluna_atual += strlen(yytext); yylval.integer = yytext[0]; return(ADDOP);
{MULOP}                 ECHO; coluna_atual += strlen(yytext); yylval.integer = yytext[0]; return(MULOP);
{INTEGER_CONSTANT}      ECHO; coluna_atual += strlen(yytext); yylval.integer = atoi(yytext); return(INTEGER_CONSTANT);
{REAL_CONSTANT}         ECHO; coluna_atual += strlen(yytext); yylval.real = (int) atof(yytext); return(REAL_CONSTANT);
{CHAR_CONSTANT}         ECHO; coluna_atual += strlen(yytext); yylval.integer = yytext[0]; return(CHAR_CONSTANT);
{ID}                    ECHO; coluna_atual += strlen(yytext); yylval.string = strdup(yytext); return(ID);
%%
#ifndef yywrap
yywrap() { return 1; }
#endif


