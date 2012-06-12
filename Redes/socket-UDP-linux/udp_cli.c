/* 
 * Exemplo de um cliente usando o protocolo UDP.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/*
 * Tamanho da mensagem que sera enviada 
 * para o servidor.
 */
#define MAXMESG 2

main (argc, argv)
int  argc;
char *argv[];
{
    int sockfd;  /* descritor do socket */
    struct sockaddr_in cli_addr,   /* endereco do cliente */ 
                       serv_addr;  /* endereco do servidor */
    char byte; /* caracter a ser recebido */
    char mesg[MAXMESG]; /* mensagem que sera enviada para o servidor */
    char *serv_udp_port;   /* porto do servidor */
    char *serv_host_addr;  /* endereco ip do servidro */


    /* 
     * Verifica se o programa foi chamado com os
     * parametros necessarios.
     */
    if (argc < 3) {
        printf("Uso: %s <endereco_ip_do_servidor> <porto_do_servidor>\n", 
                                                                  argv[0]);
        exit(1);
    }
 
    /*
     * Pega o endereco e o porto do servidor que
     * foram passados pela linha de comando.
     */
    serv_host_addr = argv[1];
    serv_udp_port  = argv[2];

    /*
     * Mensagem que sera enviada para o servidor (OI) 
     */
    mesg[0] = 'O';
    mesg[1] = 'I';
 
    /*
     * Preenche a estrutura de dados que representa
     * o endereco do servidor. Ver o codigo do cliente
     * TCP para maiores detalhes.
     */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(serv_host_addr);
    serv_addr.sin_port = htons(atoi(serv_udp_port));


    /*
     * Cria o socket que sera utilizado para conversar com
     * o servidor. O tipo do socket e SOCK_DGRAM, o que 
     * caracteriza que o protocolo UDP sera usado ao inves
     * de TCP (SOCK_STREAM).
     */
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("Cliente: erro ao criar o socket.\n");
        exit(1);
    }

    /*
     * Preenche a estrutura de dados que representa o
     * endereco do cliente. Nesse caso o cliente tem 
     * o endereco da maquina em que esta executando e 
     * um porto sera escolhido automaticamente no 
     * intervalo de 1024 a 5000.
     */
    cli_addr.sin_family = AF_INET;
    cli_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    cli_addr.sin_port = htons(0);

    /*
     * Associa o socket ao endereco do cliente.
     */
    if (bind(sockfd, (struct sockaddr *) &cli_addr, sizeof(cli_addr)) < 0) {
        printf("Cliente: erro no bind.\n");
        exit(1);
    }

    /* 
     * Envia para o servidor a mensagem inicial (OI).
     */
    sendto(sockfd, mesg, MAXMESG, 0, (struct sockaddr *) &serv_addr, 
                                                        sizeof(serv_addr));

    /*
     * Fica recebendo byte a byte do servidor ate ele enviar 
     * um 0 (nulo), e escreve na tela os caracteres recebidos.
     */
    recvfrom(sockfd, &byte, 1, 0, (struct sockaddr *) 0, (int *) 0);
    while(byte != 0) {

        printf("%c", byte);
        recvfrom(sockfd, &byte, 1, 0, (struct sockaddr *) 0, (int *) 0);
    }

    /*
     * Quando terminar de receber os caracteres, fecha o socket e
     * finaliza o programa.
     */
    close(sockfd);
    exit(0);
}
