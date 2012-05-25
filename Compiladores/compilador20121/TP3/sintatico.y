/* declarations */


%{
	#include "sym_table.c"
	#include <stdio.h>
	int yydebug=1;
	/* Tabela de símbolos. Declarada globalmente para estar disponível
	 * tanto para o Lex quanto para o Yacc.
	 * Foi declarado dessa forma para o endereço ser conhecido
	 * em tempo de compilação. */
	SymbolTable table;
	SymbolTable *symbol_table = (SymbolTable*) &table;
	//symbol_table->initialized = False;
%}





%debug

%union 
{
	int integer;
	float real;
	char *string;
}

%token COMMA 
%token COLON
%token SEMICOLON
%token PROC
%token SIN
%token LOG
%token COS
%token ORD
%token ABS
%token SQRT
%token EXP
%token EOFILE
%token EOLN
%token PROGRAM
%token INTEGER
%token REAL
%token BOOLEAN
%token CHAR
%token VALUE
%token REFERENCE
%token BEGIN_TOK
%token END
%token IF
%token THEN
%token ELSE
%token REPEAT
%token UNTIL
%token READ
%token WRITE
%token FALSE
%token TRUE
%token ATRIB
%token LPAR
%token RPAR
%token NOT
%token EQ
%token NE
%token GT
%token LT
%token GE
%token LE
%token <integer> ADDOP
%token <integer> MULOP
%token <string> ID
%token <integer> INTEGER_CONSTANT
%token <real> REAL_CONSTANT
%token <integer> CHAR_CONSTANT

%type<string> type tipo_retornado

%start program
%%

/* rules */
program    :       PROGRAM ID SEMICOLON decl_list compound_stmt
						{ printf("reduced program!\n"); }
           ;
decl_list   :       decl_list SEMICOLON decl
            |       decl
            |		vazio
            ;
decl    :       dcl_var
        |       dcl_proc
        ;
dcl_var     :       ident_list COLON type
            ;
ident_list  :       ident_list COMMA ID
            |       ID
            			{ int id = getSymbol(symbol_table, $1); symbol_table->items[id]->type = strdup($1); }
            ;
type	:		INTEGER
					{ $$ = "integer"; }
		|		REAL
					{ $$ = "real"; }
		|		BOOLEAN
					{ $$ = "boolean"; }
		|		CHAR
					{ $$ = "char"; }
		;
dcl_proc    :       tipo_retornado PROC ID espec_parametros corpo
						{ openScope(symbol_table); }
            ;
vazio   :
        ;
tipo_retornado  :       INTEGER
							{ $$ = "integer"; }
                |       REAL
                			{ $$ = "real"; }
                |       BOOLEAN
                			{ $$ = "boolean"; }
                |       CHAR
                			{ $$ = "char"; }
                |       vazio
                			{ $$ = "vazio"; }
                ;
corpo   :       COLON decl_list SEMICOLON compound_stmt id_return
        |       vazio
        ;
id_return   :       ID
            |       vazio
            ;
espec_parametros    :       LPAR lista_parametros RPAR
                    ;
lista_parametros	:		parametro
                    |		lista_parametros COMMA parametro
                    ;
parametro	:		modo type COLON ID
			;
modo	:		VALUE
		|		REFERENCE
		;
compound_stmt	:		BEGIN_TOK stmt_list END
				;
stmt_list	:		stmt_list SEMICOLON stmt
			|		stmt
			;
stmt	:		assign_stmt
		|		if_stmt
		|		repeat_stmt
		|		read_stmt
		|		write_stmt
		|		compound_stmt
		|		function_ref_par
		;
assign_stmt	:		ID ATRIB expr
			;
if_stmt	:		IF cond THEN stmt
		|		IF cond THEN stmt ELSE stmt
		;
cond	:		expr
		;
repeat_stmt	:		REPEAT stmt_list UNTIL expr
			;
read_stmt	:		READ LPAR ident_list RPAR
			;
write_stmt	:		WRITE LPAR expr_list RPAR
			;
expr_list	:		expr
			|		expr_list COMMA expr
			;
expr	:		simple_expr
		|		simple_expr EQ simple_expr
		|		simple_expr NE simple_expr
		|		simple_expr GT simple_expr
		|		simple_expr LT simple_expr
		|		simple_expr GE simple_expr
		|		simple_expr LE simple_expr
				
		;
simple_expr	:		term
			|		simple_expr ADDOP term
			;
term	:		factor_a
		|		term MULOP factor_a
		;
factor_a	:		'-' factor
			|		factor
			;
factor	:		ID
		|		constant
		|		LPAR expr RPAR
		|		NOT factor
		|		function_ref_par
		;
function_ref_par	:		built_in_function LPAR expr RPAR
					|		variable LPAR expr_list RPAR
					;
built_in_function	:		SIN
					|		LOG
					|		COS
					|		ORD
					|		ABS
					|		SQRT
					|		EXP
					|		EOFILE
					|		EOLN
					;
variable	:		simple_variable_or_proc
			;
simple_variable_or_proc	:		ID
						;
constant	:		INTEGER_CONSTANT
			|		REAL_CONSTANT
			|		CHAR_CONSTANT
			|		boolean_constant
			;
boolean_constant	:		TRUE
					|		FALSE
					;
%%
/* programs */
#include "lex.yy.c"
main() {
   initTable(symbol_table);
   yyparse();
   printTable(symbol_table);
   return 0;
}

yyerror(s) char *s; {
	fprintf( stderr, "%s\n", s );
}

