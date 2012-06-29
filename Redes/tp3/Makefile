COMPILER = gcc
OPTIONS = -c -g -Wall

all: tp3-server tp3-sender tp3-receiver

tp3-server: server.o time.o tp_socket.o message.o
	$(COMPILER) time.o server.o tp_socket.o message.o -o $@

tp3-sender: sender.o tp_socket.o time.o message.o client.o
	$(COMPILER) sender.o tp_socket.o time.o message.o client.o -o $@

tp3-receiver: receiver.o tp_socket.o time.o message.o client.o 
	$(COMPILER) receiver.o tp_socket.o time.o message.o client.o -o $@

server.o: server.c
	$(COMPILER) $(OPTIONS) server.c

sender.o: sender.c
	$(COMPILER) $(OPTIONS) sender.c

receiver.o: receiver.c
	$(COMPILER) $(OPTIONS) receiver.c

message.o: message.c message.h
	$(COMPILER) $(OPTIONS) message.c

client.o: client.c client.h
	$(COMPILER) $(OPTIONS) client.c

time.o: time.c time.h
	$(COMPILER) $(OPTIONS) time.c

tp_socket.o: tp_socket.c tp_socket.h
	$(COMPILER) $(OPTIONS) tp_socket.c

#listener.o: listener.c listener.h
#	$(COMPILER) $(OPTIONS) listener.c

clean: 
	@rm -f *.o tp2-server tp3-sender tp3-receiver
