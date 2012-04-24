COMPILER = gcc
OPTIONS = -c -g -Wall -Wextra -Werror

all: tp5

stats: io.o temporal.o lista.o video.o espacial.o statistics.o main.o_with_stats
	$(COMPILER) io.o main.o temporal.o lista.o video.o espacial.o statistics.o -lgsl -lgslcblas -lm -o tp5

tp5: io.o temporal.o lista.o video.o espacial.o main.o
	$(COMPILER) io.o main.o temporal.o lista.o video.o espacial.o -o tp5

main.o_with_stats: main.c
	$(COMPILER) $(OPTIONS) -D __GENERATE_STATS__ main.c

main.o: main.c
	$(COMPILER) $(OPTIONS) main.c
	
lista.o: lista.c
	$(COMPILER) $(OPTIONS) lista.c
	
temporal.o: temporal.c
	$(COMPILER) $(OPTIONS) temporal.c

espacial.o: espacial.c
	$(COMPILER) $(OPTIONS) espacial.c

io.o: io.c
	$(COMPILER) $(OPTIONS) io.c
	
video.o: video.c
	$(COMPILER) $(OPTIONS) video.c

statistics.o: statistics.c
	$(COMPILER) $(OPTIONS) statistics.c

clean:
	rm -f *.o *.png tp5 localidadetemporal.txt localidadeespacial.txt popularidade.txt estatisticas.txt
