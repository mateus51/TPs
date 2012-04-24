COMPILER = gcc
OPTIONS = -c -Wall -Wextra -Werror -g

all: tp1-1

tp1-2: io.o tp1-2.o
	$(COMPILER) io.o tp1-2.o -o tp1-2

tp1-1: io.o automata_constructor.o main.o
	$(COMPILER) io.o automata_constructor.o main.o -o tp1-1

tp1-2.o: tp1-2.c
	$(COMPILER) $(OPTIONS) tp1-2.c

main.o: main.c
	$(COMPILER) $(OPTIONS) main.c

automata_constructor.o: automata_constructor.c
	$(COMPILER) $(OPTIONS) automata_constructor.c

io.o: io.c
	$(COMPILER) $(OPTIONS) io.c

clean:
	rm -f *.o tp1-*