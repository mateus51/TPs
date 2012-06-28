#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <sys/errno.h>
#include "protocolo.h"

#define ESPERA 60000

short int viewerNum=0;
short int connct_uids[20];
int fdmax;        // variavel para guardar o número máximo de sockets na lista 
int listener;     // descritor para o socket que esta escutando 
fd_set master;    // Lista "mestre" para os sockets utilizados 
struct timeval time1;

//funcao de auxilio para informar erros e abortar
void error(char *msg)
{
    printf("\n%s\n", msg);
    exit(0);
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

//funcao de auxilio para informar como usar o programa
void usage()
{
    printf("Usage: \n ./server port \n"); 
    printf("\t port: \t\t  Porto do servidor\n"); 
} 

void mysettimer(int milisegundos) {
    struct itimerval newvalue, oldvalue;

    newvalue.it_value.tv_sec  = milisegundos / 1000;
    newvalue.it_value.tv_usec = milisegundos % 1000 * 1000;
    newvalue.it_interval.tv_sec  = 0;
    newvalue.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &newvalue, &oldvalue);
}

void timer_handler(int signum) {

    char buf[141] ;  
    int j;
    struct timeval time2;
    Mensagem msg;
    int sec, msec; 

    //termina a contagem do tempo
    gettimeofday(&time2,NULL);

    //calcula as medidas com base no tempo gasto
    sec = (int)  (time2.tv_sec - time1.tv_sec);
    msec = (int ) (time2.tv_usec - time1.tv_usec);

    for(j = 0; j <= fdmax; j++) {

        //verifica se "configurado"/"setado"
        if (FD_ISSET(j, &master) && connct_uids[j] > 0 && connct_uids[j] < 1000) {

            // ignora o listener 
            if (j != listener) {

                sprintf(buf,"Seu id é %d. Existe(m) %d viewer(s). Sem acidentes desde \%3u.\%06u s.\n",connct_uids[j],viewerNum,(unsigned int) sec, (unsigned int) msec); 
                empacota(&msg,2,0,0,strlen(buf),buf);
                if (send(j, &msg, sizeof(msg), 0) == -1) {
                    error("send");
                }
            }
        }
    }	
    mysettimer(ESPERA);  /* Melhor lugar para reiniciar o timer */
}

void mysethandler(void) {
    signal(SIGALRM,timer_handler);
}

int main(int argc, char *argv[]) { 
    if ( argc != 2 ){
        usage();
        error("Numero de argumentos invalido\n");
    }

    //Marcação do evento de status
    mysethandler();
    mysettimer(ESPERA);


    // Declarações iniciais
    char *porto = argv[1]; //porto a ser utilizado pelo servidor
    fd_set read_fds;  // Lista temporarioa para os sockets do select() 

    int newfd;        // descritor para o socket que esta lidando na vez 
    struct sockaddr_storage remoteaddr; // para guardar o endereco do client 
    socklen_t addrlen;
    Mensagem msg;

    // buffer para as mensagens transmitidas
    char buf[141];    
    int nbytes;

    char remoteIP[INET6_ADDRSTRLEN];

    // para o setsockopt()
    int yes=1;        
    int i, j, rv;

    struct addrinfo hints, *ai, *p;

    //structs de tempo para timeout
    struct timeval tv;
    tv.tv_sec= 2;
    tv.tv_usec=500000;

    //Limpara a lista master e a temporaria
    FD_ZERO(&master);    
    FD_ZERO(&read_fds);

    // "binda" e inicializa o socket do servidor
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if ((rv = getaddrinfo(NULL, porto, &hints, &ai)) != 0) {
        fprintf(stderr, "Servidor: %s\n", gai_strerror(rv));
        error("getaddrinfo");
    }

    for(p = ai; p != NULL; p = p->ai_next) {

        listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (listener < 0) { 
            continue;
        }

        //  Remove o problema de "address already in use" 
        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

        if (bind(listener, p->ai_addr, p->ai_addrlen) < 0) {
            close(listener);
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "Servidor: Falha na incialização\n");
        error("Falha na inicialização");
    }else{
        printf("Servidor incializado na porta %s\n",porto);
    } 

    freeaddrinfo(ai); 

    if (listen(listener, 10) == -1) {
        error("listen");
    }

    //Adiciona o listener na lista "mestre" 
    FD_SET(listener, &master);
    connct_uids[listener] = 0;

    // Atualiza o número max de sockets 
    fdmax = listener; 


    //inicia a contagem do tempo
    gettimeofday(&time1,NULL);

    /******************************
     *  Comportamento do servidor  *  
     ******************************/

    printf("What do you hear, Starbuck?\n");
    printf("Nothing but the rain.\n");

    int tipo_msg=0;
    // Principal 
    while(1) {
        errno = 0; /* Só por garantia */
        read_fds = master; // copia  a lista 

        if (select(fdmax+1, &read_fds, NULL, NULL, &tv) == -1) {
            if (errno==EINTR) {
                errno = 0;
                continue;
            }
            error("select");
        }

        // Procura na lista "mestre" por sockets ativos 
        for(i = 0; i <= fdmax; i++) {

            if (FD_ISSET(i, &read_fds)) { // quando acha um 
                //verifica se o que achou veio do listener
                if (i == listener) {

                    // Resolve a nova conexão 
                    addrlen = sizeof remoteaddr;
                    newfd = accept(listener,
                            (struct sockaddr *)&remoteaddr,
                            &addrlen);

                    if (newfd == -1) {
                        error("accept");
                    } else {
                        //adiciona na lista "mestre"
                        FD_SET(newfd, &master); 
                        connct_uids[newfd]=0;

                        //atualiza o número Max
                        if (newfd > fdmax) {   
                            fdmax = newfd;
                        }
                        printf("[Novo cliente] Conexão de %s no "
                                "socket %d\n",
                                inet_ntop(remoteaddr.ss_family,
                                    get_in_addr((struct sockaddr*)&remoteaddr),
                                    remoteIP, INET6_ADDRSTRLEN),
                                newfd);
                    }
                } else {
                    // Veio das conexoes ativas 

                    if ((nbytes = recv(i, &msg, sizeof msg, 0)) <= 0) {

                        // Provavelmente erro ou pq client fechou conexao 
                        if (nbytes == 0){
                            //conexao fecahda 
                            printf("Server: socket %d Desligando\n", i);

                            //verifica se foi um viewer que desligou
                            if(connct_uids[i] > 0 && connct_uids[i] < 1000){
                                viewerNum--;
                            }
                        } else {
                            printf("Server: Erro no  recv do socket %d \n", i);

                        }
                        //fecha a conexao e remove da lista "mestre" 
                        close(i); 
                        FD_CLR(i, &master); 
                        connct_uids[i] = -1;
                    } else {
                        //Veio dados
                        tipo_msg = getType(&msg);
                        printf("[Nova Mensagem] tipo %d de %d para %d\n",tipo_msg, getOrigem(&msg),getDestino(&msg));


                        //reenvia a mensagem pro client e registra o uid no array de sockets
                        if(tipo_msg == 0){
                            int uid_existe=0;
                            //verifica se já existe o uid autenticado
                            if (getOrigem(&msg) > 1000){
                                for(j = 0; j <= fdmax; j++) {
                                    if(connct_uids[j] == getOrigem(&msg)){
                                        uid_existe=1;
                                        break;
                                    }
                                }
                            }
                            else {
                                for(j = 0; j <= fdmax; j++) {
                                    if((connct_uids[j] == getOrigem(&msg)) || 
                                            (connct_uids[j] == 1000 + getOrigem(&msg))){
                                        uid_existe=1;
                                        break;
                                    }
                                }
                            }

                            if (uid_existe) {
                                //manda mensagem de erro
                                printf("[Novo Erro] UID %d já existe\n",getOrigem(&msg));
                                empacota(&msg,1,0,getOrigem(&msg),20,"ERRO: UID já existe\n");

                                if (send(i, &msg , sizeof(msg), 0) == -1) {
                                    error("send");
                                }
                                close(i); 
                                FD_CLR(i, &master); 
                                continue;
                            }

                            connct_uids[i] = getOrigem(&msg);
                            printf("[Novo registro] Socket %d com UID %d\n",i,connct_uids[i]);

                            //verifica se é um viewer
                            if ( connct_uids[i] < 1000 && connct_uids[i] > 0){
                                viewerNum++;
                            }

                            //manda pacote de confirmação
                            empacota(&msg,0,0,getOrigem(&msg),2,"OI");

                            if (send(i, &msg , sizeof(msg), 0) == -1) {
                                error("send");
                            }
                            continue;
                        }

                        //Pra enviar somente pra um cliente
                        if (getDestino(&msg) != 0){
                            for(j = 0; j <= fdmax; j++) {
                                if(connct_uids[j] == getDestino(&msg)) break;
                            }

                            if (FD_ISSET(j, &master)){
                                if (send(j, &msg, nbytes, 0) == -1) {
                                    error("send");
                                }
                            }
                            continue;
                        }
                        // repassa para todos 
                        for(j = 0; j <= fdmax; j++) {

                            //verifica se "configurado"/"setado"
                            if (FD_ISSET(j, &master)) {

                                // ignora o listener e o próprio servidor 
                                if (j != listener && j != i) {

                                    if (send(j, &msg, nbytes, 0) == -1) {
                                        error("send");
                                    }
                                }
                            }
                        }
                    }
                } 
            } 
        } 
    } 

    return 0;
}
