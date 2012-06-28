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
#include "mensagem.h"

int fdmax;
int serversocket;
fd_set master; 
int numExibicao=0;
struct timeval time1;
short int clients[20];

/* Exibe erros */
void error(char *msg)
{
    printf("\n%s\n", msg);
    exit(0);
}

/* Pega o endereco */
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

/* Funcoes de timer */
void mysettimer(int milisegundos) {
    struct itimerval newvalue, oldvalue;

    newvalue.it_value.tv_sec  = milisegundos / 1000;
    newvalue.it_value.tv_usec = milisegundos % 1000 * 1000;
    newvalue.it_interval.tv_sec  = 0;
    newvalue.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &newvalue, &oldvalue);
}

void timer_handler(int signum) {

    /* Finaliza o timer */
    struct timeval time2;
    int sec, msec; 
    gettimeofday(&time2,NULL);
    sec = (int)  (time2.tv_sec - time1.tv_sec);
    msec = (int ) (time2.tv_usec - time1.tv_usec);

    char buffer[141] ;  
    msg_t msg;
    int j;
    for(j = 0; j <= fdmax; j++) {
        if (FD_ISSET(j, &master) && clients[j] > 0 && clients[j] < 1000) {
            if (j != serversocket) {
                sprintf(buffer,"\n\tID: %d.\n\tNumero de clientes: %d.\n\tUptime: \%3u.\%06u s.\n",clients[j],numExibicao,(unsigned int) sec, (unsigned int) msec); 
                setMsg(&msg,MSG,0,0,strlen(buffer),buffer);
                if (send(j, &msg, sizeof(msg), 0) == -1) {
                    error("send");
                }
            }
        }
    }	
    mysettimer(60000);
}

void mysethandler(void) {
    signal(SIGALRM,timer_handler);
}

int main(int argc, char *argv[]) { 

    if ( argc != 2 ) {
      error("Erro nos parâmetros!\nUso: ./servidor <porto>\n");
    }

    /* Recebe os parametros */
    char *port = argv[1];


    /* Inicializa o socket do servidor */
    struct addrinfo hints, *servinfo, *p;
    int rv;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if ((rv = getaddrinfo(NULL, port, &hints, &servinfo)) != 0) {
        fprintf(stderr, "Servidor: %s\n", gai_strerror(rv));
        error("getaddrinfo");
    }
    
    /* Faz o bind */
    int i,j;
    for(p = servinfo; p != NULL; p = p->ai_next) {
        serversocket = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (serversocket < 0) { 
            continue;
        }
        /* Corrige bug do address already in use */
        i=1;
        setsockopt(serversocket, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(int));

        if (bind(serversocket, p->ai_addr, p->ai_addrlen) < 0) {
            close(serversocket);
            continue;
        }

        break;
    }

    /* Verifica corretude */
    if (p == NULL) {
        fprintf(stderr, "Servidor: Falha na incialização\n");
    }else{
        printf("Inicializando servidor na porta %s:\n",port);
    } 

    freeaddrinfo(servinfo); 

    if (listen(serversocket, 10) == -1) {
        error("listen");
    }

    /* Inicializa as listas */
    fd_set fd_temp;
    FD_ZERO(&master);    
    FD_ZERO(&fd_temp);

    /* Adiciona o socket na lista */
    FD_SET(serversocket, &master);
    clients[serversocket] = 0;
    fdmax = serversocket; 


    /* Inicia o timer */
    gettimeofday(&time1,NULL);
    mysethandler();
    mysettimer(60000);

    int tipo=OI;
    int newfd;
    struct sockaddr_storage clientaddr;
    socklen_t addrlen;
    msg_t msg;
    char buffer[141];    
    int numbytes;
    char remoteIP[INET6_ADDRSTRLEN];

    /* Timeout */
    struct timeval tv;
    tv.tv_sec = 2;
    tv.tv_usec = 500000;

    printf("####################################################################\n");
    printf("#                     SERVIDOR INICIADO                            #\n");
    printf("####################################################################\n\n");
    while(1) {
        fd_temp = master;
        errno = 0;
        if (select(fdmax+1, &fd_temp, NULL, NULL, &tv) == -1) {
        /* Trata os casos de timeout */
            if (errno==EINTR) {
                errno = 0;
                continue;
            }
            error("select");
        }

        /* Para cada socket ativo */
        for(i = 0; i <= fdmax; i++) {

            if (FD_ISSET(i, &fd_temp)) {
                if (i == serversocket) {
                    /* Novas conexoes */
                    addrlen = sizeof(clientaddr);
                    newfd = accept(serversocket, (struct sockaddr *)&clientaddr, &addrlen);

                    if (newfd == -1) {
                        error("accept");
                    } else {
                        /* Adiciona cliente */
                        FD_SET(newfd, &master); 
                        clients[newfd]=0;
                        if (newfd > fdmax) {   
                            fdmax = newfd;
                        }
                        printf("## Nova conexão de %s no socket %d ##\n", inet_ntop(clientaddr.ss_family,get_in_addr((struct sockaddr*)&clientaddr),remoteIP, INET6_ADDRSTRLEN), newfd);
                    }
                } else {
                    /* Recebe dados dos cliente */
                    if ((numbytes = recv(i, &msg, sizeof(msg), 0)) <= 0) {

                        /* Erro com o cliente */
                        if (numbytes == 0){
                            /* Conexao fechou */
                            printf("## Fechou o socket %d ##\n", i);

                            /* Verifica se foi um cliente de exibicao */
                            if(clients[i] > 0 && clients[i] < 1000){
                                numExibicao--;
                            }
                        } else {
                            printf("Erro no socket %d\n", i);

                        }
                        /* Fecha a conexao */
                        close(i); 
                        FD_CLR(i, &master); 
                        clients[i] = -1;
                    } else {
                        /* Chegaram dados */
                        tipo = getType(&msg);
                        printf("## Recebeu uma mensagem do tipo %d de %d para %d ##\n",tipo, getOrig(&msg),getDest(&msg));

                        /* Envia a mensagem pro cliente */
                        if(tipo == OI){
                            int uid_existe=0;
                            
                            /* Verifica se ja existe um cliente com o ID */
                            if (getOrig(&msg) > 1000){
                                for(j = 0; j <= fdmax; j++) {
                                    if(clients[j] == getOrig(&msg)){
                                        uid_existe=1;
                                        break;
                                    }
                                }
                            }
                            else {
                                for(j = 0; j <= fdmax; j++) {
                                    if((clients[j] == getOrig(&msg)) || 
                                            (clients[j] == 1000 + getOrig(&msg))){
                                        uid_existe=1;
                                        break;
                                    }
                                }
                            }
  
                            /* Se o ID ja esta sendo usado */
                            if (uid_existe) {
                                printf("## ID %d já está em uso ##\n",getOrig(&msg));
                                setMsg(&msg,TCHAU,0,getOrig(&msg),20,"Error: ID em uso\n");
                                if (send(i, &msg , sizeof(msg), 0) == -1) {
                                    error("send");
                                }
                                close(i); 
                                FD_CLR(i, &master); 
                                continue;
                            }


                            /* Adiciona novo cliente */
                            clients[i] = getOrig(&msg);
                            printf("## Recebeu novo cliente com socket %d e ID %d ##\n",i,clients[i]);
                            if ( clients[i] < 1000 && clients[i] > 0){
                                numExibicao++;
                            }

                            /* Manda confirmacao */
                            setMsg(&msg,OI,0,getOrig(&msg),13,"Hello, Dave.\n");
                            if (send(i, &msg , sizeof(msg), 0) == -1) {
                                error("send");
                            }

                            continue;
                        }

                        /* Mensagem para um cliente */
                        if (getDest(&msg) != 0){
                            for(j = 0; j <= fdmax; j++) {
                                if(clients[j] == getDest(&msg)) 
                                  break;
                            }

                            if (FD_ISSET(j, &master)){
                                if (send(j, &msg, numbytes, 0) == -1) {
                                    error("send");
                                }
                            }
                            continue;
                        }
                        
                        /* Mensagem para todos */
                        for(j = 0; j <= fdmax; j++) {
                            if (FD_ISSET(j, &master)) {
                                if (j != serversocket && j != i) {
                                    if (send(j, &msg, numbytes, 0) == -1) {
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
