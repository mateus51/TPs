/* tp_socket.c - funções auxiliares para uso de sockets UDP
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <strings.h>

#include "tp_socket.h"

int tp_socket(unsigned short port)
{
    int    so;
    struct sockaddr_in local_addr;
    int    addr_len =sizeof(local_addr);

//    fprintf(stderr,"tp_socket called\n");
    if ((so=socket(PF_INET,SOCK_STREAM,0))<0) {
        return -1;
    }
    if (tp_build_addr(&local_addr,INADDR_ANY,port)<0) {
        return -2;
    }

    /* Corrige bug do address already in use */
    int x = 1;
    setsockopt(so, SOL_SOCKET, SO_REUSEADDR, &x, sizeof(int));

    /* Envia buffer antes de fechar socket. Timeout de 5 segundos.
     * Para evitar erro "Connection reset by peer". */
    struct linger linger_opt;
    linger_opt.l_onoff = 1;
    linger_opt.l_linger = 5; // timeout: 5 seconds
    setsockopt(so, SOL_SOCKET, SO_LINGER, &linger_opt, sizeof(linger_opt));

    if (bind(so, (struct sockaddr*)&local_addr, addr_len)<0) {
        return -3;
    }
    return so;
}

int tp_build_addr(so_addr* addr, char* hostname, int port)
{
    struct hostent* he;

//    fprintf(stderr,"tp_build_addr called\n");
    addr->sin_family = PF_INET;
    addr->sin_port   = htons(port);
    if (hostname==NULL) {
        addr->sin_addr.s_addr = INADDR_ANY;
    } else {
        if ((he=gethostbyname(hostname))==NULL) {
            return -1;
        }
        bcopy(he->h_addr,&(addr->sin_addr.s_addr),sizeof(in_addr_t));
    }
    return 0;
}

