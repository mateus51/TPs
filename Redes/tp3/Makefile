COMPILER = gcc
OPTIONS = -c -g -Wall

all: tp3-server tp3-sender


tp3-server: time.o server.o tp_socket.o message.o
	$(COMPILER) time.o server.o tp_socket.o message.o -o $@

tp3-sender: sender.o tp_socket.o time.o message.o
	$(COMPILER) sender.o tp_socket.o time.o message.o -o $@

server.o: server.c
	$(COMPILER) $(OPTIONS) server.c

sender.o: sender.c
	$(COMPILER) $(OPTIONS) sender.c

message.o: message.c message.h
	$(COMPILER) $(OPTIONS) message.c

time.o: time.c time.h
	$(COMPILER) $(OPTIONS) time.c

tp_socket.o: tp_socket.c tp_socket.h
	$(COMPILER) $(OPTIONS) tp_socket.c

#listener.o: listener.c listener.h
#	$(COMPILER) $(OPTIONS) listener.c

clean: 
	@rm -f *.o tp2-server tp3-sender
