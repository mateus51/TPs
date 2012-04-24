COMPILER = gcc
OPTIONS = -c -Wall -Wextra -Werror -g

run: tp0
	./tp0 entrada

all: tp0

tp0: TADeleicao.o io.o kemeny_young.o main.o
	$(COMPILER) TADeleicao.o io.o kemeny_young.o main.o -o tp0

main.o: kemeny_young.o main.c
	$(COMPILER) $(OPTIONS) main.c

kemeny_young.o: io.o kemeny_young.c 
	$(COMPILER) $(OPTIONS) kemeny_young.c

io.o: TADeleicao.o io.c
	$(COMPILER) $(OPTIONS) io.c

TADeleicao.o: TADeleicao.c
	$(COMPILER) $(OPTIONS) TADeleicao.c	

clean:
	rm -f *.o tp0
