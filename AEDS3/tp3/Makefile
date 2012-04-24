COMPILER = gcc
OPTIONS = -c -g -Wall -Wextra -Werror

run: tp3_fb tp3_pd
	./tp3_fb entrada
	./tp3_pd entrada

all: tp3_fb tp3_pd

tp3_pd: io.o pd.o show.o benchmark.o
	$(COMPILER) io.o pd.o show.o benchmark.o -o tp3_pd

tp3_fb: io.o fb.o show.o benchmark.o
	$(COMPILER) io.o fb.o show.o benchmark.o -o tp3_fb -lm
	
fb.o: fb.c
	$(COMPILER) $(OPTIONS) fb.c
	
pd.o: pd.c
	$(COMPILER) $(OPTIONS) pd.c		
	
show.o: show.c
	$(COMPILER) $(OPTIONS) show.c	

io.o: io.c
	$(COMPILER) $(OPTIONS) io.c
	
benchmark.o: benchmark.c
	$(COMPILER) $(OPTIONS) benchmark.c	

clean:
	rm -f *.o tp3_*
