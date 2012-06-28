run: programa
	
clean: server writer viewer 
	@echo "Tentando apagar o programa.exe"
	rm ./server ./viewer ./writer

programa: server.c writer.c viewer.c protocolo.c protocolo.h
	@echo "Compilando writer..." 
	gcc -o writer writer.c protocolo.c
	@echo "done"
	@echo "Compilando server..."
	gcc -o server server.c protocolo.c
	@echo "done"
	@echo "Compilando viewer..."
	gcc -o viewer viewer.c protocolo.c
	@echo "done"
