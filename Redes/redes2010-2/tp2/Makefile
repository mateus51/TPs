default: janela tpsocket
	@echo "\n****Compilando o servidor****\n"
	(cd servidor; $(MAKE) )
	@echo "\n****Compilando o cliente****\n"
	(cd cliente; $(MAKE) )
clean:
	@echo "\n****Limpando os diretórios****\n"
	(cd servidor; $(MAKE) clean)
	(cd cliente; $(MAKE) clean)
tpsocket:
	gcc -c tp_socket.c -o tp_socket.o
janela:
	gcc -c janela.c -o janela.o
