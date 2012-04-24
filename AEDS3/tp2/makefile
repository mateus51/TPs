COMPILER = gcc
OPTIONS = -c -g -Wall -Wextra -Werror

all: tp2

tp2: benchmark.o eleicao.o io.o kemeny_young.o enumerations.o main.o
	$(COMPILER) -lpthread -lm benchmark.o eleicao.o io.o kemeny_young.o enumerations.o main.o -o tp2

main.o: main.c
	$(COMPILER) $(OPTIONS) main.c

kemeny_young.o: kemeny_young.c
	$(COMPILER) $(OPTIONS) kemeny_young.c

io.o: io.c
	$(COMPILER) $(OPTIONS) io.c

eleicao.o: eleicao.c
	$(COMPILER) $(OPTIONS) eleicao.c

enumerations.o: enumerations.c
	$(COMPILER) $(OPTIONS) enumerations.c

benchmark.o: benchmark.c
	$(COMPILER) $(OPTIONS) benchmark.c	

clean:
	rm -f *.o tp0
