COMPILER = gcc
OPTIONS = -c -g -Wall

all: tp1

tp1: glpk_test.o main.c
	$(COMPILER) glpk_test.o main.c -lglpk -o tp1

glpk_test.o: glpk_test.c
	$(COMPILER) $(OPTIONS) glpk_test.c


clean:
	rm -f *.o tp1

