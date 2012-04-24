COMPILER = gcc
OPTIONS = -c -g -Wall -Wextra -Werror

all: montador

montador: io.o montador.o main.o
	$(COMPILER) io.o montador.o main.o -o montador

main.o: main.c
	$(COMPILER) $(OPTIONS) main.c

montador.o: montador.c
	$(COMPILER) $(OPTIONS) montador.c

io.o: io.c
	$(COMPILER) $(OPTIONS) io.c

clean:
	rm -f *.o montador

