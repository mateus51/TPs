#include "../janela.h"

#define MAX_PENDING  5
#define MAX_NOME 20

int main(int argc, char * argv[]) {
    char *buffer;
    int porto,tambuffer,tamjanela;
    FILE *arquivo;
    int recebidos,lidos;
    
    /* Recebe os argumentos */
    if (argc==4) {
        porto = atoi(argv[1]);
        tambuffer = atoi(argv[2]);
        tamjanela = atoi(argv[3]);
    }
    else {
      printf("Erro nos parâmetros!\nUso: ./servidor <porto> <buffer> <janela>\n");
      return 0;
    }
   
    /* Abertura passiva */
    windowInitPassivo(porto,tambuffer,tamjanela);


    /* Roda o servidor */
    while(1){

        /* Recebe o nome do arquivo */
        buffer = (char*)malloc(sizeof(char)*tambuffer);
        recebidos = 0;
        printf("\n********\n\n");
        printf("Esperando a conexão de um cliente...\n\n");
        if ((recebidos = windowReceiveName(buffer, tambuffer)) < 0){
//            printf("Erro: Não conseguiu receber o nome do arquivo.\n");
//            return 0;
        }

        
        /* Abre o arquivo para leitura */
        arquivo = fopen(buffer,"r");  

        /* Envia o arquivo para o cliente */
        lidos = 0;
        printf("Enviando o arquivo: %s\n\n",buffer);
        while ( (lidos = fread(buffer,1,tambuffer, arquivo)) > 0 ){ 
            if ( windowSend(buffer, lidos) < 0){
//                printf("Erro: Não conseguiu enviar o arquivo.\n");
//                return 0;
            }
        }
        windowSendFinal(tambuffer);
        printf("Arquivo enviado!\n");
    }
     
    windowClose();
    return 1;
}

