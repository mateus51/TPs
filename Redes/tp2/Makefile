COMPILER = gcc
OPTIONS = -c -g -Wall

all: tp2-client tp2-server

tp2-client: time.o tp_socket.o client.o window.o listener.o
	$(COMPILER) time.o tp_socket.o client.o window.o listener.o -pthread -o $@

tp2-server: time.o tp_socket.o server.o window.o listener.o
	$(COMPILER) time.o tp_socket.o server.o window.o listener.o -pthread -o $@

client.o: client.c
	$(COMPILER) $(OPTIONS) client.c

server.o: server.c
	$(COMPILER) $(OPTIONS) server.c

time.o: time.c time.h
	$(COMPILER) $(OPTIONS) time.c

window.o: window.c window.h
	$(COMPILER) $(OPTIONS) window.c

tp_socket.o: tp_socket.c tp_socket.h
	$(COMPILER) $(OPTIONS) tp_socket.c

listener.o: listener.c listener.h
	$(COMPILER) $(OPTIONS) listener.c

clean: 
	@rm -f *.o tp2-client tp2-server impaciente
	
impaciente: impaciente.c 
	gcc impaciente.c -o $@