#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

#include "window.h"

boolean keep_listening_for_signals;

pthread_mutex_t server_window;

pthread_mutex_t* get_server_window_mutex(void) {
	return &server_window;
}

void lock_server_window_mutex() {
	pthread_mutex_lock(&server_window);
	printf("\nMUTEX locked!\n");
}

void unlock_server_window_mutex() {
	printf("MUTEX unlocked!\n\n");
	pthread_mutex_unlock(&server_window);
}

void destroy_server_window_mutex() {
	pthread_mutex_destroy(&server_window);
}

void dummy_handler(int signum) { ; }

void set_alarm(int wait_time) {
	alarm(wait_time);
}

// litener for the SIGALRM signal. Made this way so the handler has access
// to the window pointer without it being global.
// When the alarm arrives, resends the older packet in the window.
void *signal_listener(void *arg) {
	printf("starting signal listener...\n");
	sigset_t set;
	int rc, sig;
	signal(SIGALRM, dummy_handler);

	Window *window = (Window*) arg;
	keep_listening_for_signals = True;

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
			// keep_listening_for_signals may have changed while listener was blocked by sigwait()
			resend_older(window);
			set_alarm(1);
		}
		else if (!keep_listening_for_signals){
			printf("keep_listening_for_signals is FALSE!\n");
		}
		else {
			printf("caugth signal isn't SIGALRM!\n");
		}
	}
	pthread_exit(NULL);
	return NULL; // only to remove warning.
}

pthread_t start_signal_listener(Window *window) {
	int rc;

	pthread_t thread;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	rc = pthread_create(&thread, &attr, signal_listener, (void*) window);
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

	return thread;
}

// waits for the thread to finish.
void stop_listener (pthread_t thread) {
	int rc;
	rc = pthread_join(thread, NULL);
	if (rc) {
		printf("ERROR: return code from pthread_join() is %d\n", rc);
		exit(EXIT_FAILURE);
	}
}


// Listen for ACKs from the client. Exits when all packets arrived without problems.
void *ack_listener(void *info) {
	Window *window = (Window*) info;
	byte buffer[HEADER_SIZE];
	boolean all_received = False;
	unsigned char seq;
	int resp;

	while(!all_received){
		resp = tp_recvfrom(window->info->socket, buffer, HEADER_SIZE, NULL);
		if (resp < 0) {
			perror("ACKlistener()");
//			exit(EXIT_FAILURE);
		}

		seq = (unsigned char) buffer[1];

		printf("[ACK Listener] ");

		switch (buffer[0]) {
		case ACK: // packet received without errors
			printf("ACK %d\n", seq);
			lock_server_window_mutex();
			all_received = mark_received_by_client(window, seq);
			unlock_server_window_mutex();
			char b = all_received ? 'T' : 'F';
			printf("  all_received: %c\n", b);
			break;

		case FAIL: // packet received with errors
			printf("FAIL %d\n", buffer[1]);
			printf("  resending %d\n", seq);
			resend(window, seq);
			break;

		case MORE:
			printf("MORE %d\n", buffer[1]);
			break;

		case END:
			printf("END %d\n", buffer[1]);
			break;

		default:
			printf("ERROR: unknown header (%d)\n", buffer[1]);
			break;
		}
	}
	pthread_exit(NULL);
	return NULL; // only to remove warning.
}

pthread_t start_ack_listener(Window *window) {
	int rc;
	pthread_t thread;
	pthread_attr_t attr;
	pthread_mutex_init(&server_window, NULL);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	rc = pthread_create(&thread, &attr, ack_listener, (void*) window);
	if (rc) {
		 printf("ERROR: return code from pthread_create() is %d\n", rc);
		 exit(EXIT_FAILURE);
	}
	pthread_attr_destroy(&attr);
	return thread;
}
