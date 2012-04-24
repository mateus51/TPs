COMPILER = gcc
OPTIONS = -c -Wall -Wextra -Werror

all: mv

mv: io.o mv.o main.o
	$(COMPILER) io.o mv.o main.o -o mv

main.o: main.c
	$(COMPILER) $(OPTIONS) main.c

mv.o: mv.c
	$(COMPILER) $(OPTIONS) mv.c

io.o: io.c
	$(COMPILER) $(OPTIONS) io.c

clean:
	rm -f *.o mv

