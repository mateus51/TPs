%{
#include <string.h>

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
{NEWLINE}
{SPACES}
{COMMA}                  return(COMMA);
{COLON}                  return(COLON);
{SEMICOLON}              return(SEMICOLON);
PROCEDURE                return(PROC);
sin                      return(SIN);
log                      return(LOG);
cos                      return(COS);
ord                      return(ORD);
abs                      return(ABS);
sqrt                     return(SQRT);
exp                      return(EXP);
eof                      return(EOFILE);
eoln                     return(EOLN);
program                  return(PROGRAM);
integer                  return(INTEGER);
real                     return(REAL);
boolean                  return(BOOLEAN);
char                     return(CHAR);
value                    return(VALUE);
reference                return(REFERENCE);
begin                    return(BEGIN_TOK);
end                      return(END);
if                       return(IF);
then                     return(THEN);
else                     return(ELSE);
repeat                   return(REPEAT);
until                    return(UNTIL);
read                     return(READ);
write                    return(WRITE);
false                    return(FALSE);
true                     return(TRUE);
:=                       return(ATRIB);
\(                       return(LPAR);
\)                       return(RPAR);
NOT                      return(NOT);
\<						 return(LT);
>						 return(GT);
>=						 return(GE);
\<=						 return(LE);
=						 return(EQ);
!=						 return(NE);
{ADDOP}                  yylval.integer = yytext[0]; return(ADDOP);
{MULOP}                  yylval.integer = yytext[0]; return(MULOP);
{INTEGER_CONSTANT}       yylval.integer = atoi(yytext); return(INTEGER_CONSTANT);
{REAL_CONSTANT}          yylval.real = (int) atof(yytext); return(REAL_CONSTANT);
{CHAR_CONSTANT}          yylval.integer = yytext[0]; return(CHAR_CONSTANT);
{ID}                     yylval.string = strdup(yytext); return(ID);
%%
#ifndef yywrap
yywrap() { return 1; }
#endif


