#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_PENDING  5
#define MAX_NOME 20

int main(int argc, char * argv[]) {
    struct sockaddr_in sin;
    int tamsin;
    char *buffer;
    int porto,tambuffer;
    int idsocket, idsocket2;
    char nomearquivo[MAX_NOME];
    FILE *arquivo;
    
    /* Recebe os argumentos */
    if (argc==3) {
        porto = atoi(argv[1]);
        tambuffer = atoi(argv[2]);
    }
    else {
      printf("Erro nos parâmetros!\nUso: ./servidor <porto> <buffer>\n");
      return 0;
    }

    /* Inicializa os argumentos */
    bzero((char *)&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(porto);
    tamsin = sizeof(sin);

    /* Abertura passiva */
    if ((idsocket = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Erro: Não conseguiu abrir o socket.\n");
        return 0;
    }
    if ((bind(idsocket, (struct sockaddr *)&sin, sizeof(sin))) < 0) {
        printf("Erro: Não conseguiu vincular o socket.\n");
        return 0;
    }
    listen(idsocket, MAX_PENDING);

    /* Roda o servidor */
    while(1){
        /* Espera uma conexao */
        if ((idsocket2 = accept(idsocket, (struct sockaddr *)&sin, (socklen_t *) &tamsin)) < 0){
            printf("Erro: Não conseguiu aceitar a conexão.\n");
            return 0;      
        }
       
        /* Recebe o nome do arquivo */
        buffer = (char*)malloc(sizeof(char)*tambuffer);
        int i=0;
        buffer[0] = ' ';  
        while ( buffer[0] != '\0' ){
            if (recv(idsocket2, buffer, 1, 0) < 0){
                printf("Erro: Não conseguiu receber o nome do arquivo.\n");
                return 0;
            }
            nomearquivo[i] = buffer[0];
            i++;
        }
        nomearquivo[i] = '\0';
        
        /* Abre o arquivo para leitura */
        arquivo = fopen(nomearquivo,"r");  

        /* Envia o arquivo para o cliente */
        int lidos = 0;
        while ( (lidos = fread(buffer,1,tambuffer, arquivo)) > 0 ){ 
            if ( send(idsocket2, buffer, lidos,0) < 0){
                printf("Erro: Não conseguiu enviar o arquivo.\n");
                return 0;
            }
        }
        
        /* Fecha a conexao com o cliente */
        close(idsocket2);
    }
    close(idsocket);
    return 1;
}

