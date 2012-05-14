all: run

run: TP3 COMPILA_TP2
	./COMPILA_TP2
	./TP3 entrada saida1

TP3: main.o tabela.o quadruplas.o tradutor.o
	g++ -g main.o tabela.o quadruplas.o tradutor.o -lm -o TP3
	
COMPILA_TP2: CompilaJava.o
	g++ -g CompilaJava.o -o COMPILA_TP2

main.o: main.cpp
	g++ -g -c -Wall -Werror main.cpp -o main.o

tabela.o: tabela.cpp tabela.hpp
	g++ -g -c -Wall -Werror tabela.cpp -o tabela.o

quadruplas.o: quadruplas.cpp quadruplas.hpp
	g++ -g -c -Wall -Werror quadruplas.cpp -o quadruplas.o

tradutor.o: tradutor.cpp tradutor.hpp
	g++ -g -c -Wall -Werror tradutor.cpp -o tradutor.o

CompilaJava.o: CompilaJava.cpp
	g++ -g -c -Wall -Werror CompilaJava.cpp -o CompilaJava.o

clean:
	-rm -rf main.o tabela.o quadruplas.o tradutor.o CompilaJava.o