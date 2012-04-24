COMPILER = gcc
OPTIONS = -c -g -Wall -Wextra -Werror

all: ligador

ligador: io.o main.o ligador.o simbolos.o
	$(COMPILER) io.o main.o ligador.o simbolos.o -o ligador

ligador.o: ligador.c
	$(COMPILER) $(OPTIONS) ligador.c

simbolos.o: simbolos.c
	$(COMPILER) $(OPTIONS) simbolos.c

main.o: main.c
	$(COMPILER) $(OPTIONS) main.c

io.o: io.c
	$(COMPILER) $(OPTIONS) io.c

clean:
	rm -f *.o ligador

