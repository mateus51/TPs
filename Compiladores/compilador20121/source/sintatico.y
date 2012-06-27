/* declarations */


%{

	#include <stdio.h>

	#include "sym_table.h"
	#include "type_checker.h"
	#include "semantic_analyzer.h"
	
	#define YYSTYPE Attributes
     
	int total_tokens = 0;	
	
	/* Tabela de símbolos. Declarada globalmente para estar disponível
	 * tanto para o Lex quanto para o Yacc. */
	SymbolTable table;
	SymbolTable *symbol_table = (SymbolTable*) &table;
	
	// Debug flag
	int yydebug=1;

	// No máximo 10 variáveis na mesma declaração
	int vars_to_get_type[10];
	int var_ind = 0;
	
	// variavel para indicar quando o parser está lendo
	// código ou declarações
	char reading_code = False;
	
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

	void updateVariablesType(Type type) {
		if (DBG)
			printf("\n\nUpdating array...\n  array[0] = %d\n", vars_to_get_type[0]);

		int i;
		for (i = 0; vars_to_get_type[i] != -1; i++)
			updateType(symbol_table, vars_to_get_type[i], type);

		resetVarsArray();
		//printTable(symbol_table);
	}
	
	void updateFunctionDef(int index, Type functype) {
		updateType(symbol_table, index, functype);
		symbol_table->items[index]->num_params = function_def_params;
		function_def_params = 0;
	}

	void saveVarInArray(int var_index) {
		if (var_ind >= 10)
			erro("No máximo 10 variáveis podem ser declaradas ao mesmo tempo!");

		vars_to_get_type[var_ind] = var_index;
		var_ind++;
	}
	
	void updateFunctionParams(int index) {
		symbol_table->items[index]->num_params = function_def_params;
		function_def_params = 0;
	}

%}



%token COMMA COLON SEMICOLON PROC SIN LOG COS ORD ABS SQRT EXP EOFILE EOLN CHR PROGRAM INTEGER REAL BOOLEAN CHAR VALUE REFERENCE BEGIN_TOK END IF THEN ELSE REPEAT UNTIL READ WRITE FALSE TRUE ATRIB LPAR RPAR NOT EQ NE GT LT GE LE DIV MOD AND OR ID INTEGER_CONSTANT REAL_CONSTANT CHAR_CONSTANT ADDOP MULOP


%start program


%error-verbose


%initial-action { @$.last_column = 0; };

%%

/* rules */
program    :       PROGRAM ID SEMICOLON decl_list compound_stmt
						{ updateType(symbol_table, $2.addr, program); }
           ;
decl_list   :       decl_list SEMICOLON decl
            |       decl
            |		vazio
            ;
decl    :       dcl_var
        |       dcl_proc
        ;
dcl_var     :       ident_list COLON type
						{ updateVariablesType($3.type); }
            ;
ident_list  :       ident_list COMMA ID
            			{ saveVarInArray($3.addr); }
            |       ID
            			{ saveVarInArray($1.addr); }
            ;
type	:		INTEGER
					{ $$.type = integer; }
		|		REAL
					{ $$.type = real; }
		|		BOOLEAN
					{ $$.type = boolean; }
		|		CHAR
					{ $$.type = character; }
		;
dcl_proc    :       tipo_retornado PROC ID espec_parametros corpo
						{ updateFunctionDef($3.addr, $1.type); }
            ;
vazio   :
        ;
tipo_retornado  :       INTEGER
							{ $$.type = integer; }
                |       REAL
                			{ $$.type = real; }
                |       BOOLEAN
                			{ $$.type = boolean; }
                |       CHAR
                			{ $$.type = character; }
                |       vazio
                			{ $$.type = nulltype; }
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
						{ updateType(symbol_table, $4.addr, $2.type); }
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
						{ checkAssign(symbol_table, $1.addr, $3.type, @3.first_line, @3.first_column, @3.last_line, @3.last_column); }
			;
if_stmt	:		IF cond THEN stmt
					{ checkIf($2.type, @2.first_line, @2.first_column, @2.last_line, @2.last_column); }
		|		IF cond THEN stmt ELSE stmt
					{ checkIf($2.type, @2.first_line, @2.first_column, @2.last_line, @2.last_column); }
		;
cond	:		expr
					{ $$.type = $1.type; }
		;
repeat_stmt	:		REPEAT stmt_list UNTIL expr
						{ checkRepeat($4.type, @4.first_line, @4.first_column, @4.last_line, @4.last_column); }
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
					{ $$.type = $1.type; }
		|		simple_expr EQ simple_expr
					{ $$.type = checkRELOP($1.type, $3.type); }
		|		simple_expr NE simple_expr
					{ $$.type = checkRELOP($1.type, $3.type); }
		|		simple_expr GT simple_expr
					{ $$.type = checkRELOP($1.type, $3.type); }
		|		simple_expr LT simple_expr
					{ $$.type = checkRELOP($1.type, $3.type); }
		|		simple_expr GE simple_expr
					{ $$.type = checkRELOP($1.type, $3.type); }
		|		simple_expr LE simple_expr
					{ $$.type = checkRELOP($1.type, $3.type); }
		;
simple_expr	:		term
						{ $$.type = $1.type; }
			|		simple_expr ADDOP term
						{ checkExpType(symbol_table, $1.type, $3.type, @$.first_line, @$.first_column, @$.last_line, @$.last_column); $$ = $1; }
			|		simple_expr OR term
						{ checkExpType(symbol_table, $1.type, boolean, @$.first_line, @$.first_column, @$.last_line, @$.last_column); $$ = $1; }
			;
term	:		factor_a
					{ $$.type = $1.type; }
		|		term MULOP factor_a
					{ checkExpType(symbol_table, $1.type, $3.type, @$.first_line, @$.first_column, @$.last_line, @$.last_column); $$.type = $1.type; }
		|		term AND factor_a
					{ checkAnd($1.type, $3.type, @$.first_line, @$.first_column, @$.last_line, @$.last_column); $$.type = $1.type; }
		|		term MOD factor_a
					{ checkMod($1.type, $3.type, @$.first_line, @$.first_column, @$.last_line, @$.last_column); $$.type = $1.type; }
		|		term DIV factor_a
					{ checkDiv($1.type, $3.type, @$.first_line, @$.first_column, @$.last_line, @$.last_column); $$.type = $1.type; }
		;
factor_a	:		'-' factor
						{ $$.type = $2.type; }
			|		factor
						{ $$.type = $1.type; }
			;
factor	:		ID
					{ $$.type = lookupType(symbol_table, $1.addr); }
		|		constant
					{ $$.type = $1.type; }
		|		LPAR expr RPAR
					{ $$.type = $2.type; }
		|		NOT factor
					{ $$.type = checkNOT($2.type, @2.first_line, @2.first_column, @2.last_line, @2.last_column); }
		|		function_ref_par
					{ $$.type = $1.type; }
		;
function_ref_par	:		built_in_function LPAR expr RPAR
								{ $$.type = checkBuiltInFunctionCall($1.function, $3.type, @3.first_line, @3.first_column, @3.last_line, @3.last_column); $$.width = getTypeWidth($$.type); }
					|		variable LPAR expr_list RPAR
								{ $$.type = checkFunctionCall(symbol_table, $1.addr, @3.first_line, @3.first_column, @3.last_line, @3.last_column); ; $$.width = getTypeWidth($$.type); }
					;
built_in_function	:		SIN
								{ $$.function = fsin; }
					|		COS
								{ $$.function = fcos; }
					|		LOG
								{ $$.function = flog; }
					|		ORD
								{ $$.function = ford; }
					|		ABS
								{ $$.function = fabs; }
					|		SQRT
								{ $$.function = fsqrt; }
					|		EXP
								{ $$.function = fexp; }
					|		EOFILE
								{ $$.function = feofile; }
					|		EOLN
								{ $$.function = feoln; }
					|		CHR
								{ $$.function = fchr; }
					;
variable	:		simple_variable_or_proc
						{ $$.addr = $1.addr; $$.width = $1.width; }
			;
simple_variable_or_proc	:		ID
									{ $$.addr = $1.addr; $$.width = $1.width; }
						;
constant	:		INTEGER_CONSTANT
						{ $$.type = integer; $$.width = 4; }
			|		REAL_CONSTANT
						{ $$.type = real; $$.width = 8; }
			|		CHAR_CONSTANT
						{ $$.type = character; $$.width = 1; }
			|		boolean_constant
						{ $$.type = boolean; $$.width = 1; }
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
	//extern int linha_atual;
	//fprintf(stderr, "Error   (line %d): %s\n", linha_atual, s);
	extern YYLTYPE yylloc;
	fprintf(stderr, "Error (l%d,c%d-l%d,c%d): %s\n", yylloc.first_line, yylloc.first_column, yylloc.last_line, yylloc.last_column, s);
}

