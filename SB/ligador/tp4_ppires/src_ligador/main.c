#include "io.h"
#include "ligador.h"
#include "simbolos.h"

int main(int argc, char *argv[]) {

	GetArgs(argc, argv);

	TabelaDeSimbolos *tabela = NewTabelaDeSimbolos();

	BuildMasterSymbolTable(tabela);

	LinkObjects(tabela);

	//ImprimeTabela(tabela);

	FreeTabela(tabela);

	extern char **object_files;
	free(object_files);

	return EXIT_SUCCESS;
}
