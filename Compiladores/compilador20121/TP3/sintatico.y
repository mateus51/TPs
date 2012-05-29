/* declarations */


%{
	#include "sym_table.h"
	#include "type_checker.h"
	
	
	/* Tabela de símbolos. Declarada globalmente para estar disponível
	 * tanto para o Lex quanto para o Yacc.
	 * Foi declarado dessa forma para o endereço ser conhecido
	 * em tempo de compilação (stack). */
	SymbolTable table;
	SymbolTable *symbol_table = (SymbolTable*) &table;
	int yydebug=1;

	// No máximo 10 variáveis na mesma declaração
	int vars_to_get_type[10];
	int var_ind = 0;
	
	// variavel para indicar quando o parser está lendo
	// código ou declarações
	boolean reading_code = False;
	
	// variavel que guarda número de parâmetros
	// de cada definição função.
	int function_def_params = 0;

	// variavel que guarda número de parâmetros
	// de cada chamada função.	
	int function_call_params = 0;

	void resetVarsArray() {
		int i;
		for (i = 0; i < 10; i++)
			vars_to_get_type[i] = -1;
		var_ind = 0;
	}

	void updateVariablesType(char *type_str) {
		if (DBG)
			printf("\n\nUpdating array...\n  array[0] = %d\n", vars_to_get_type[0]);

		int i;
		for (i = 0; vars_to_get_type[i] != -1; i++)
			updateType(symbol_table, vars_to_get_type[i], type_str);

		resetVarsArray();
		//printTable(symbol_table);
	}
	
	void updateFunctionDef(int index, char *type) {
		updateType(symbol_table, index, type);
		symbol_table->items[index]->num_params = function_def_params;
		function_def_params = 0;
	}

	void saveVarInArray(int var_index) {
		if (var_ind >= 10)
			erro(symbol_table, "No máximo 10 variáveis podem ser declaradas ao mesmo tempo!");

		vars_to_get_type[var_ind] = var_index;
		var_ind++;
	}
	
	void updateFunctionParams(int index) {
		symbol_table->items[index]->num_params = function_def_params;
		function_def_params = 0;
	}
	
	char *getType(int index) {
		return symbol_table->items[index]->type;
	}	

%}



%union
{
	int integer;
	float real;
	char *string;
}

%token COMMA COLON SEMICOLON PROC SIN LOG COS ORD ABS SQRT EXP EOFILE EOLN PROGRAM INTEGER REAL BOOLEAN CHAR VALUE REFERENCE BEGIN_TOK END IF THEN ELSE REPEAT UNTIL READ WRITE FALSE TRUE ATRIB LPAR RPAR NOT EQ NE GT LT GE LE DIV MOD AND OR
%token <integer> ADDOP
%token <integer> MULOP
%token <integer> ID
%token <integer> INTEGER_CONSTANT
%token <real> REAL_CONSTANT
%token <integer> CHAR_CONSTANT

%type<string> type tipo_retornado expr factor factor_a function_ref_par built_in_function constant simple_expr term
%type<integer> variable simple_variable_or_proc

%start program
%%

/* rules */
program    :       PROGRAM ID SEMICOLON decl_list compound_stmt
						{ updateType(symbol_table, $2, "program"); }
           ;
decl_list   :       decl_list SEMICOLON decl
            |       decl
            |		vazio
            ;
decl    :       dcl_var
        |       dcl_proc
        ;
dcl_var     :       ident_list COLON type
						{ updateVariablesType($3); }
            ;
ident_list  :       ident_list COMMA ID
            			{ saveVarInArray($3); }
            |       ID
            			{ saveVarInArray($1); }
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
						{ updateFunctionDef($3, $1); }
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
corpo   :       COLON decl_list SEMICOLON compound_stmt after_proc_compound id_return
        |       vazio
        ;
after_proc_compound	:		vazio
								{ closeScope(symbol_table); }
					;
						;
id_return   :       ID
            |       vazio
            ;
espec_parametros    :       lpar_espec_params lista_parametros RPAR
                    ;
lpar_espec_params	:		LPAR
								{ openScope(symbol_table); }
					;
lista_parametros	:		parametro
								{ function_def_params++; }
                    |		lista_parametros COMMA parametro
                    			{ function_def_params++; }
                    ;
parametro	:		modo type COLON ID
						{ updateType(symbol_table, $4, $2); }
			;
modo	:		VALUE
		|		REFERENCE
		;
compound_stmt	:		start_compound stmt_list end_compound
							{ /* closeScope(symbol_table); */ }
				;
start_compound	:		BEGIN_TOK
							{ reading_code = True; }
				;
end_compound	:		END
							{ reading_code = False; }
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
						{ checkAtribType(symbol_table, $1, $3); }
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
						{ function_call_params++; }
			|		expr_list COMMA expr
						{ function_call_params++; }
			;
expr	:		simple_expr
					{ $$ = $1; }
		|		simple_expr EQ simple_expr
					{ $$ = "boolean"; }
		|		simple_expr NE simple_expr
					{ $$ = "boolean"; }
		|		simple_expr GT simple_expr
					{ $$ = "boolean"; }
		|		simple_expr LT simple_expr
					{ $$ = "boolean"; }
		|		simple_expr GE simple_expr
					{ $$ = "boolean"; }
		|		simple_expr LE simple_expr
					{ $$ = "boolean"; }
		;
simple_expr	:		term
						{ $$ = $1; }
			|		simple_expr ADDOP term
						{ checkExpType(symbol_table, $1, $3); $$ = $1; }
			|		simple_expr OR term
						{ checkExpType(symbol_table, $1, "boolean"); $$ = $1; }
			;
term	:		factor_a
					{ $$ = $1; }
		|		term MULOP factor_a
					{ checkExpType(symbol_table, $1, $3); $$ = $1; }
		|		term AND factor_a
					{ checkExpType(symbol_table, $1, "boolean"); $$ = $1; }
		|		term MOD factor_a
					{ checkExpType(symbol_table, $1, "integer"); $$ = $1; }
		|		term DIV factor_a
					{ checkExpType(symbol_table, $1, "integer"); $$ = $1; }
		;
factor_a	:		'-' factor
						{ $$ = $2; }
			|		factor
						{ $$ = $1; }
			;
factor	:		ID
					{ $$ = getType($1); }
		|		constant
					{ $$ = $1; }
		|		LPAR expr RPAR
					{ $$ = $2; }
		|		NOT factor
					{ $$ = $2; }
		|		function_ref_par
					{ $$ = $1; }
		;
function_ref_par	:		built_in_function LPAR expr RPAR
								{ $$ = $1; }
					|		variable LPAR expr_list RPAR
								{ checkFunctionCall(symbol_table, $1); $$ = getType($1); }
					;
built_in_function	:		SIN
								{ $$ = "real"; }
					|		COS
								{ $$ = "real"; }
					|		LOG
								{ $$ = "real"; }
					|		ORD
								{ $$ = "integer"; }
					|		ABS
								{ $$ = "real"; }
					|		SQRT
								{ $$ = "real"; }
					|		EXP
								{ $$ = "real"; }
					|		EOFILE
								{ $$ = "integer"; }
					|		EOLN
								{ $$ = "integer"; }
					;
variable	:		simple_variable_or_proc
						{ $$ = $1; }
			;
simple_variable_or_proc	:		ID
									{ $$ = $1; }
						;
constant	:		INTEGER_CONSTANT
						{ $$ = "integer"; }
			|		REAL_CONSTANT
						{ $$ = "real"; }
			|		CHAR_CONSTANT
						{ $$ = "char"; }
			|		boolean_constant
						{ $$ = "boolean"; }
			;
boolean_constant	:		TRUE
					|		FALSE
					;
%%
/* programs */
#include "lex.yy.c"
main() {
   initTable(symbol_table);
   resetVarsArray();
   yyparse();
   printTable(symbol_table);
   return 0;
}

yyerror(s) char *s; {
	fprintf( stderr, "%s\n", s );
}

