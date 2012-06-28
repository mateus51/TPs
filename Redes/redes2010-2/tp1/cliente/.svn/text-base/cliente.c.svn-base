#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#define MAX_NOME 20

int main(int argc, char * argv[]) {

    /* Declaração das variáveis */
    char nomehost[MAX_NOME];
    struct hostent *host;
    struct sockaddr_in sin;
    int porto;
    int tambuffer;
    char *buffer;
    char nomearquivo[MAX_NOME];
    FILE *arquivo,*saida;;
    int idsocket;
    unsigned int numbytes;
    double tempo1,tempo2,tempototal;
    struct timeval tempo;

    
    /* Recebe os argumentos */
    if (argc==5) {
        strcpy(nomehost,argv[1]);
        porto = atoi(argv[2]);
        strcpy(nomearquivo,argv[3]);
        tambuffer = atoi(argv[4]);
    }
    else {
      printf("Erro nos parâmetros!\nUso: ./cliente <nome do host> <porto> <arquivo> <buffer>\n");
      return 0;
    }

    /* Pega o IP do host de acordo com o nome */
    host = gethostbyname(nomehost);
    if (!host) {
        printf("Erro: host não encontrado: %s\n", nomehost);
        return 0;
    }

    /* Inicializa os argumentos */ 
    bzero((char *)&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    bcopy(host->h_addr, (char *)&sin.sin_addr, host->h_length);
    sin.sin_port = htons(porto);

    /* Inicia a medida de desempenho */
    gettimeofday(&tempo,NULL);
    tempo1 = tempo.tv_sec+(tempo.tv_usec/1000000.0);

    /* Abertura ativa */
    if ((idsocket = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Erro: Não conseguiu abrir o socket.\n");
        return 0;
    }

    /* Conecta com o servidor */
    if (connect(idsocket, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
        printf("Erro: Não conseguiu conectar ao servidor.\n");
        close(idsocket);
        return 0;
    }

    /* Envia o nome do arquivo */
    if ( send(idsocket, nomearquivo, strlen(nomearquivo)+1, 0) < 0){
        printf("Erro: Não conseguiu enviar o nome do arquivo.\n");
        return 0;
    }

    /* Abre o arquivo para escrita*/
    arquivo = fopen(nomearquivo,"w");
    saida = fopen("saida.txt","a+");

    /* Recebe o arquivo */
    numbytes = 0;
    int recebidos = 0;
    buffer = (char*)malloc(sizeof(char)*tambuffer);
    while ( (recebidos = recv(idsocket, buffer, tambuffer, 0)) > 0){
        numbytes += fwrite(buffer,1, recebidos,arquivo);
    }

    /* Fecha conexão e arquivo  */
    fclose(arquivo);
    close(idsocket);

    /* Finaliza medida de desempenho */
    gettimeofday(&tempo,NULL);
    tempo2 = tempo.tv_sec+(tempo.tv_usec/1000000.0);
    tempototal = tempo2 - tempo1;

    /* Imprime as estatisticas */
    printf("Buffer = %u byte(s), %.3f kbps (%u bytes em %.3fs)\n",tambuffer,numbytes/tempototal,numbytes,tempototal);
    fprintf(saida,"%u %u %u %.3f %.3f\n",numbytes, numbytes/tambuffer, tambuffer, (numbytes/tempototal),tempototal);
    fclose(saida);
    return 1;
}


