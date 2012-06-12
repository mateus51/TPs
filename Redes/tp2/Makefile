COMPILER = gcc
OPTIONS = -c -g -Wall

all: tp2-client tp2-server

tp2-client: time.o tp_socket.o client.o window.o
	$(COMPILER) time.o tp_socket.o client.o window.o -o $@

tp2-server: time.o tp_socket.o server.o window.o
	$(COMPILER) time.o tp_socket.o server.o window.o -pthread -o $@

client.o: client.c client.h
	$(COMPILER) $(OPTIONS) client.c

server.o: server.c server.h
	$(COMPILER) $(OPTIONS) server.c

time.o: time.c time.h
	$(COMPILER) $(OPTIONS) time.c

window.o: window.c window.h
	$(COMPILER) $(OPTIONS) window.c

tp_socket.o: tp_socket.c tp_socket.h
	$(COMPILER) $(OPTIONS) tp_socket.c

clean: 
	@rm -f *.o tp2-client tp2-server impaciente
	
impaciente: impaciente.c 
	gcc impaciente.c -o $@