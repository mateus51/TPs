#include "montador.h"
#include "io.h"

int main(int argc, char *argv[]) {

	FILE *file = GetArgs(argc, argv);

	TabelaDeSimbolos *tabela = ConstroiTabelaDeSimbolos(file);

	rewind(file);

	TraduzPrograma(file, tabela);

	extern char verbose;
	if (verbose) ImprimeTabela(tabela);

	FreeTabela(tabela);

	fclose(file);

	return 0;
}
