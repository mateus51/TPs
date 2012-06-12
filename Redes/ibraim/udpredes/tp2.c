#include <signal.h>   /* para signal */
#include <sys/time.h>   /* para setitimer */
#include <stdio.h>      /* para fprintf, fgetln */
#include <stdlib.h>     /* para atoi, exit */
#include "tp2.h"

extern int alarm;

void timer_handler(int signum){
//    fprintf(stderr,"Anda logo!\n");
	alarm=1;
//	mysettimer(1000);  /* Melhor lugar para reiniciar o timer */
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void mysethandler(void) {
    signal(SIGALRM,timer_handler);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void mysettimer(int milisegundos){
    struct itimerval newvalue, oldvalue;

    newvalue.it_value.tv_sec  = milisegundos / 1000;
    newvalue.it_value.tv_usec = milisegundos % 1000 * 1000;
    newvalue.it_interval.tv_sec  = 0;
    newvalue.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &newvalue, &oldvalue);
}
///////////////////////////////////////////////////////////////////////////////////////////////////

