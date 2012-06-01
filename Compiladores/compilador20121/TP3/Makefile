COMPILER = gcc
OPTIONS = -c -Wall

all: a.out

a.out: sym_table.o type_checker.o y.tab.c
	$(COMPILER) sym_table.o type_checker.o y.tab.c -ll

lex.yy.c: lexico.lex
	lex lexico.lex

y.tab.c: lex.yy.c sintatico.y
	yacc sintatico.y --verbose #--debug

sym_table.o: sym_table.c sym_table.h
	$(COMPILER) $(OPTIONS) sym_table.c

type_checker.o: type_checker.c type_checker.h
	$(COMPILER) $(OPTIONS) type_checker.c

clean:
	rm -f *.o a.out lex.yy.c y.tab.c

