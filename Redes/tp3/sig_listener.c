#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>

#include "time.h"
#include "message.h"

// protótipo das funções do servidor utilizadas
// pela thread que envia o status do servidor
void broadcast_message(const char *str);
char *make_status_string();


void dummy_handler(int signum) { ; }

void set_alarm() {
	alarm(60);
}

int wait_for_alarm() {
	// configuring signal set.
	sigset_t set;
	int rc, sig;
	rc = sigemptyset(&set);
	if (rc) {
		perror("sigemptyset()");
		exit(EXIT_FAILURE);
	}
	rc = sigaddset(&set, SIGALRM);
	if (rc) {
		perror("sigaddset()");
		 exit(EXIT_FAILURE);
	}
	rc = sigwait(&set, &sig);
	if (rc) {
		 perror("sigwait()");
		 exit(EXIT_FAILURE);
	}
	return sig;
}

// listener for the SIGALRM signal. Made this way so the handler has access
// to the window pointer without it being global.
// When the alarm arrives, resends the older packet in the window.
void *signal_listener(void *arg) {
	signal(SIGALRM, dummy_handler);
	char str[141];
	int sig;

	while (1) {
		// espera pelo alarme
		sig = wait_for_alarm();

		if (sig == SIGALRM) {
			// Gera string a ser enviada
			make_status_string(str);

			// envia msg p/ todos os clientes de exibição conectados
			broadcast_message(str);

			// reinicia timer
			set_alarm();
		}
		else {
//			printf("caugth signal isn't SIGALRM!\n");
		}
	}
	pthread_exit(NULL);
	return NULL; // only to remove warning.
}

void start_signal_listener() {
	int rc;
	pthread_t thread;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	rc = pthread_create(&thread, &attr, signal_listener, NULL);
	if (rc) {
		 printf("ERROR: return code from pthread_create() is %d\n", rc);
		 exit(EXIT_FAILURE);
	}
	pthread_attr_destroy(&attr);

	// block alarm signal for main thread
	sigset_t set;
	rc = sigemptyset(&set);
	if (rc) {
		 printf("ERROR: return code from sigemptyset() is %d\n", rc);
		 exit(EXIT_FAILURE);
	}
	rc = sigaddset(&set, SIGALRM);
	if (rc) {
		 printf("ERROR: return code from sigaddset() is %d\n", rc);
		 exit(EXIT_FAILURE);
	}
	// XXX: se der problema, usar pthread_sigmask()
	rc = sigprocmask(SIG_BLOCK, &set, NULL);
	if (rc) {
		 printf("ERROR: return code from sigprocmask() is %d\n", rc);
		 exit(EXIT_FAILURE);
	}

	set_alarm();
}
