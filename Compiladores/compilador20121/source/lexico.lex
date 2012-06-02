%{
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
void installToken(char *tok, char *lex) {
    total_tokens++;
    //tokens = (Token*) realloc(tokens, sizeof(Token) * total_tokens);
    tokens[total_tokens-1] = getToken(tok, lex);
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
%%
{NEWLINE}               ECHO; linha_atual++; coluna_atual = 0;
{SPACES}                ECHO; coluna_atual += strlen(yytext);
{COMMA}                 ECHO; installToken("COMMA", yytext); coluna_atual += strlen(yytext); return(token);
{COLON}                 ECHO; installToken("COLON", yytext); coluna_atual += strlen(yytext); return(token);
{SEMICOLON}             ECHO; installToken("SEMICOLON", yytext); coluna_atual += strlen(yytext); return(token);
{INTEGER_CONSTANT}      ECHO; installToken("INTEGER_CONSTANT", yytext); coluna_atual += strlen(yytext); return(token);
{REAL_CONSTANT}         ECHO; installToken("REAL_CONSTANT", yytext); coluna_atual += strlen(yytext); return(token);
{CHAR_CONSTANT}         ECHO; installToken("CHAR_CONSTANT", yytext); coluna_atual += strlen(yytext); return(token);
{ADDOP}                 ECHO; installToken("ADDOP", yytext); coluna_atual += strlen(yytext); return(token);
{MULOP}                 ECHO; installToken("MULOP", yytext); coluna_atual += strlen(yytext); return(token);
{RELOP}                 ECHO; installToken("RELOP", yytext); coluna_atual += strlen(yytext); return(token);
PROCEDURE               ECHO; installToken("PROC", yytext); coluna_atual += strlen(yytext); return(token);
sin                     ECHO; installToken("SIN", yytext); coluna_atual += strlen(yytext); return(token);
log                     ECHO; installToken("LOG", yytext); coluna_atual += strlen(yytext); return(token);
cos                     ECHO; installToken("COS", yytext); coluna_atual += strlen(yytext); return(token);
ord                     ECHO; installToken("ORD", yytext); coluna_atual += strlen(yytext); return(token);
abs                     ECHO; installToken("ABS", yytext); coluna_atual += strlen(yytext); return(token);
sqrt                    ECHO; installToken("SQRT", yytext); coluna_atual += strlen(yytext); return(token);
exp                     ECHO; installToken("EXP", yytext); coluna_atual += strlen(yytext); return(token);
eof                     ECHO; installToken("EOF", yytext); coluna_atual += strlen(yytext); return(token);
eoln                    ECHO; installToken("EOLN", yytext); coluna_atual += strlen(yytext); return(token);
program                 ECHO; installToken("PROGRAM", yytext); coluna_atual += strlen(yytext); return(token);
integer                 ECHO; installToken("INTEGER", yytext); coluna_atual += strlen(yytext); return(token);
real                    ECHO; installToken("REAL", yytext); coluna_atual += strlen(yytext); return(token);
boolean                 ECHO; installToken("BOOLEAN", yytext); coluna_atual += strlen(yytext); return(token);
char                    ECHO; installToken("CHAR", yytext); coluna_atual += strlen(yytext); return(token);
value                   ECHO; installToken("VALUE", yytext); coluna_atual += strlen(yytext); return(token);
reference               ECHO; installToken("REFERENCE", yytext); coluna_atual += strlen(yytext); return(token);
begin                   ECHO; installToken("BEGIN", yytext); coluna_atual += strlen(yytext); return(token);
end                     ECHO; installToken("END", yytext); coluna_atual += strlen(yytext); return(token);
if                      ECHO; installToken("IF", yytext); coluna_atual += strlen(yytext); return(token);
then                    ECHO; installToken("THEN", yytext); coluna_atual += strlen(yytext); return(token);
else                    ECHO; installToken("ELSE", yytext); coluna_atual += strlen(yytext); return(token);
repeat                  ECHO; installToken("REPEAT", yytext); coluna_atual += strlen(yytext); return(token);
until                   ECHO; installToken("UNTIL", yytext); coluna_atual += strlen(yytext); return(token);
read                    ECHO; installToken("READ", yytext); coluna_atual += strlen(yytext); return(token);
write                   ECHO; installToken("WRITE", yytext); coluna_atual += strlen(yytext); return(token);
false                   ECHO; installToken("FALSE", yytext); coluna_atual += strlen(yytext); return(token);
true                    ECHO; installToken("TRUE", yytext); coluna_atual += strlen(yytext); return(token);
:=                      ECHO; installToken("ATRIB", yytext); coluna_atual += strlen(yytext); return(token);
\(                      ECHO; installToken("LPAR", yytext); coluna_atual += strlen(yytext); return(token);
\)                      ECHO; installToken("RPAR", yytext); coluna_atual += strlen(yytext); return(token);
NOT                     ECHO; installToken("NOT", yytext); coluna_atual += strlen(yytext); return(token);
{ID}                    ECHO; installToken("ID", yytext); coluna_atual += strlen(yytext); return(token);
%%
int main() {
    yylex();
    //printTokens();
    return 0;
}

