COMPILER = gcc
OPTIONS = -c -g -Wall -Wextra -Werror

run: all
	./tp4 tp4Tests_input.txt

all: tp4

tp4: io.o main.o grafo.o fractal.o benchmark.o
	$(COMPILER) io.o main.o grafo.o fractal.o benchmark.o -lm -o tp4

main.o: main.c
	$(COMPILER) $(OPTIONS) main.c

fractal.o: fractal.c
	$(COMPILER) $(OPTIONS) fractal.c
	
grafo.o: grafo.c
	$(COMPILER) $(OPTIONS) grafo.c	

io.o: io.c
	$(COMPILER) $(OPTIONS) io.c
	
benchmark.o: benchmark.c
	$(COMPILER) $(OPTIONS) benchmark.c

clean:
	rm -f *.o tp4
