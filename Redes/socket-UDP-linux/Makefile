default: udp_serv  udp_cli

udp_cli: udp_cli.o
	cc -o udp_cli udp_cli.o \
        -lnsl

udp_cli.o: udp_cli.c

udp_serv: udp_serv.o                                              
	cc -o udp_serv udp_serv.o \
	-lnsl

udp_serv.o: udp_serv.c

clean:
	\rm -f *.o udp_serv udp_cli
