#include "../janela.h"

#define MAX_NOME 20

int main(int argc, char * argv[]) {

    /* Declaração das variáveis */
    char nomehost[MAX_NOME];
    int porto;
    int tambuffer,tamjanela;
    char nomearquivo[MAX_NOME];
    char *buffer;
    FILE *arquivo;
    FILE *saida;
    double tempo1,tempo2,tempototal;
    struct timeval tempo;

    
    /* Recebe os argumentos */
    if (argc==6) {
        strcpy(nomehost,argv[1]);
        porto = atoi(argv[2]);
        strcpy(nomearquivo,argv[3]);
        tambuffer = atoi(argv[4]);
        tamjanela = atoi(argv[5]);
    }
    else {
      printf("Erro nos parâmetros!\nUso: ./cliente <nome do host> <porto> <arquivo> <buffer> <janela>\n");
      return 0;
    }

    /* Abertura ativa */
    windowInitAtivo(nomehost,porto);
    printf("Conectou com o servidor %s na porta %d.\n\n",nomehost,porto);

    buffer = (char*)malloc(sizeof(char)*tambuffer);
    strcpy(buffer,nomearquivo);
 
     /* Abre o arquivo para escrita*/
    arquivo = fopen(nomearquivo,"w");
    saida = fopen("saida.txt","a+");
   
    /* Recebe o arquivo */
    unsigned int numbytes = 0;
    int recebidos = 0;

    /* Inicia a medida de desempenho */
    gettimeofday(&tempo,NULL);
    tempo1 = tempo.tv_sec+(tempo.tv_usec/1000000.0);

    if ( windowSendName(buffer,tambuffer) < 0){
//        printf("Erro: Não conseguiu enviar o nome do arquivo.\n");
//        return 0;
    }
    printf("Enviou o nome do arquivo.\n\n");

    printf("Recebendo arquivo...\n\n");
    recebidos = windowReceive(buffer,tambuffer);
    numbytes += fwrite(buffer,1, recebidos,arquivo);    

    while ( (recebidos = windowReceive(buffer,tambuffer)) > 0 ){
        numbytes += fwrite(buffer,1, recebidos,arquivo);
    }

    /* Fecha conexão e arquivo  */
    fclose(arquivo);

    /* Finaliza medida de desempenho */
    gettimeofday(&tempo,NULL);
    tempo2 = tempo.tv_sec+(tempo.tv_usec/1000000.0);
    tempototal = tempo2 - tempo1;

    printf("Foram recebidos %u byte(s)!\n\n",numbytes);
    printf("Tempo de execução: %.3fs\n",tempototal);
    printf("Throughput: %.3f kbps\n",numbytes/tempototal);

    windowClose();
    
    return 1;
}


