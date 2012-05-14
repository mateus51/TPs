COMPILER = gcc
OPTIONS = -c -g -Wall

all: tp1-client tp1-server

tp1-client: io.o client.o socket.o time.o
	$(COMPILER) io.o client.o socket.o time.o -o tp1-client

tp1-server: io.o server.o socket.o time.o
	$(COMPILER) io.o server.o socket.o time.o -o tp1-server

io.o: io.c
	$(COMPILER) $(OPTIONS) io.c

socket.o: socket.c
	$(COMPILER) $(OPTIONS) socket.c

time.o: time.c
	$(COMPILER) $(OPTIONS) time.c

client.o: client.c
	$(COMPILER) $(OPTIONS) client.c

server.o: server.c
	$(COMPILER) $(OPTIONS) server.c

clean:
	rm -f *.o tp1-client tp1-server

