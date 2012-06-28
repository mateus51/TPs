run: programa
	
clean: 
	@echo "Limpando"
	rm ./servidor ./exibicao ./envio
	@echo "OK!"

programa: 
	@echo "Compilando envio..." 
	gcc -o envio envio.c mensagem.c
	@echo "OK!"
	@echo "Compilando server..."
	gcc -o servidor servidor.c mensagem.c
	@echo "OK!"
	@echo "Compilando exibicao..."
	gcc -o exibicao exibicao.c mensagem.c
	@echo "OK!"
