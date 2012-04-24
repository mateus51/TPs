COMPILER = gcc
OPTIONS = -c -g -Wall -Wextra -Werror

all: expansor

expansor: io.o main.o expansor.o macro.o
	$(COMPILER) io.o main.o expansor.o macro.o -o expansor

expansor.o: expansor.c
	$(COMPILER) $(OPTIONS) expansor.c
	
macro.o: macro.c
	$(COMPILER) $(OPTIONS) macro.c	

main.o: main.c
	$(COMPILER) $(OPTIONS) main.c

io.o: io.c
	$(COMPILER) $(OPTIONS) io.c

clean:
	rm -f *.o expansor

