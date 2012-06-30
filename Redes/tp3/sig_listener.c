#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>

#include "time.h"
#include "message.h"

char keep_listening_for_signals;
pthread_mutex_t clients_mutex;
extern double start_time;

extern int clients[2000];


//
//void lock_clients_mutex() {
//	pthread_mutex_lock(&clients_mutex);
////	printf("\nMUTEX locked!\n");
//}
//
//void unlock_clients_mutex() {
////	printf("MUTEX unlocked!\n\n");
//	pthread_mutex_unlock(&clients_mutex);
//}
//
//void destroy_server_window_mutex() {
//	pthread_mutex_destroy(&clients_mutex);
//}

void dummy_handler(int signum) { ; }

void set_alarm() {
	alarm(60);
}

// listener for the SIGALRM signal. Made this way so the handler has access
// to the window pointer without it being global.
// When the alarm arrives, resends the older packet in the window.
void *signal_listener(void *arg) {
	sigset_t set;
	int rc, sig;
	signal(SIGALRM, dummy_handler);

	keep_listening_for_signals = 1;

	while (keep_listening_for_signals) {

		// configuring signal set.
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

		// waiting for SIGALRM
		rc = sigwait(&set, &sig);
		if (rc) {
			 printf("ERROR: return code from sigwait() is %d\n", rc);
			 exit(EXIT_FAILURE);
		}

		if (sig == SIGALRM && keep_listening_for_signals) {
			// keep_listening_for_signals is checked because it
			// may have changed while listener was blocked by sigwait()

			int i, exib = 0, env = 0;
			for (i = 1; i < 2000; i++) {
				if (clients[i] != -1) {
					if (i < 1000)
						exib++;
					else
						env++;
				}
			}

			// montando mensagem
			double elapsed_time = get_time() - start_time;
			char msg_text[141];
			sprintf(msg_text, "[tp3-server] Clientes (exibição/envio/total): %d/%d/%d   Uptime: %.2fs", exib, env, exib+env, elapsed_time);
//			printf("[SIG] %s\n", msg_text);
			msg_t msg;
			msg.type = MSG;
			msg.orig_uid = 0;
			msg.dest_uid = 0;
			msg.text_len = strlen(msg_text) + 1;
			strcpy(msg.text, msg_text);
			char buffer[BUFF_LEN];
			encode(buffer, msg);

			// envia msg p/ todos os clientes
			for (i = 0; i < 1000; i++) {
				if (clients[i] != -1) {
					write (clients[i], buffer, BUFF_LEN);
				}
			}

			// reinicia timer
			set_alarm();
		}
		else if (!keep_listening_for_signals){
//			printf("keep_listening_for_signals is FALSE!\n");
		}
		else {
//			printf("caugth signal isn't SIGALRM!\n");
		}
	}
	pthread_exit(NULL);
	return NULL; // only to remove warning.
}

pthread_t start_signal_listener() {
	int rc;
	pthread_t thread;
	pthread_attr_t attr;
	pthread_mutex_init(&clients_mutex, NULL);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	rc = pthread_create(&thread, &attr, signal_listener, NULL);
	if (rc) {
		 printf("ERROR: return code from pthread_create() is %d\n", rc);
		 exit(EXIT_FAILURE);
	}
	pthread_attr_destroy(&attr);

	// block alarm signal for other threads
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
	// FIXME: se der problema, usar pthread_sigmask()
	rc = sigprocmask(SIG_BLOCK, &set, NULL);
	if (rc) {
		 printf("ERROR: return code from sigprocmask() is %d\n", rc);
		 exit(EXIT_FAILURE);
	}

	set_alarm();

	return thread;
}

// waits for the thread to finish.
void stop_signal_listener (pthread_t thread) {
	keep_listening_for_signals = 0;
	int rc;
	rc = pthread_join(thread, NULL);
	if (rc) {
		printf("ERROR: return code from pthread_join() is %d\n", rc);
		exit(EXIT_FAILURE);
	}
}

