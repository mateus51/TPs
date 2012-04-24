COMPILER = gcc
OPTIONS = -c -g -Wall -Wextra -Werror

all: tp6

tp6: io.o main.o lista.o cache.o
	$(COMPILER) io.o main.o lista.o cache.o -o tp6

main.o: main.c
	$(COMPILER) $(OPTIONS) main.c

io.o: io.c
	$(COMPILER) $(OPTIONS) io.c

lista.o: lista.c
	$(COMPILER) $(OPTIONS) lista.c

cache.o: cache.c
	$(COMPILER) $(OPTIONS) cache.c

clean:
	rm -f *.o tp6
