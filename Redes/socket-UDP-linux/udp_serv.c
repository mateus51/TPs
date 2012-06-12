/* 
 * Exemplo de um servidor usando o protocolo UDP.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/*
 * Tamanho maximo da mensagem
 * que ira receber dos clientes.
 */
#define MAXMESG 2

main (argc, argv) 
int  argc;
char * argv[];
{
    int sockfd;  /* descritor do socket */
    int clilen;  /* tamanho da estrutura de dados de endereco do cliente */

    struct sockaddr_in serv_addr, /* endereco do servidor */
                       cli_addr;  /* endereco do cliente */

    char byte,      /* byte que sera enviado para o cliente */
         LF = '\n', /* Line Feed */
         null = 0;  /* NULL */

    char mesg[MAXMESG]; /* Mensagem que ira receber dos clientes */
    int n,    /* tamanho da mensagem recebida dos clientes */ 
        i;    /* contador */

    char *serv_udp_port; /* porto do servidor */

    /*
     * Verifica se os paramentros da linha de comando
     * sao validos.
     */
    if (argc < 2) {
        printf("Uso: %s <porto_do_servidor>\n", argv[0]);
        exit(1);
    }

    /*
     * Pega o porto passado como parametro atraves da
     * linha de comando.
     */
    serv_udp_port = argv[1];


    /*
     * Cria o socket que sera utilizado para conversar 
     * com os clientes. O tipo do socket e SOCK_DGRAM, o que 
     * caracteriza que o protocolo UDP sera usado ao inves
     * de TCP (SOCK_STREAM).
     */
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("Servidor: erro ao criar socket.\n");
        exit(1);
    }

    /*
     * Preenche a estrutura de dados que representa
     * o endereco do servidor. Ver o codigo do cliente
     * TCP para maiores detalhes.
     */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port        = htons(atoi(serv_udp_port));
    

    /*
     * Associa o socket ao endereco do servidor.
     */
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        printf("Servidor: erro no bind");
        exit(1);
    }
    printf("Servidor inicializado.\n");
 
    /*
     * Entre em um llop infinito respondendo aos clientes 
     * que enviam uma mensagem para o servidor. O servidor
     * imprime na tela a mensagem recebida e envia para o
     * cliente os caracteres de A a Z e termina enviando
     * um 0 (NULL).
     */
    clilen = sizeof(cli_addr);
    for(;;) {

        printf("Esperando por mensagens de clientes...\n\n");

        /*
         * Recebe uma mensagem de um cliente qualquer.
         */
        n = recvfrom(sockfd, mesg, MAXMESG, 0, (struct sockaddr *) &cli_addr, 
                                                                   &clilen);

        
        /*
         * Imprime a mensagem recebida 
         */
        printf("Servidor: Recebi uma mensagem.\n");
        printf("Mensagem -> ");
        for (i=0; i<n; i++) {
            printf("%c", mesg[i]);
        }
        printf("\n");


        /* 
         * Envia para o cliente os caracteres de A a Z, cada
         * um seguido de um \n.
         */
        printf("Servidor: Enviando os caracteres...\n");
        for (byte='A'; byte<='Z'; byte++) {

            /*
             * Envia o caracter.
             */
            sendto(sockfd, &byte, 1, 0, (struct sockaddr *) &cli_addr, 
                                                                clilen);

            /*
             * Envia o \n
             */
            sendto(sockfd, &LF, 1, 0, (struct sockaddr *) &cli_addr, 
                                                              clilen);
        }

        /* 
         * Envia o um 0 (NULL).
         */ 
        sendto(sockfd, &null, 1, 0, (struct sockaddr *) &cli_addr,
                                                            clilen);
        printf("Servidor: Caracteres enviados.\n");
    }
    
}
