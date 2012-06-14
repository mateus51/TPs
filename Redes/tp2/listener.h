#include <pthread.h>
#include "window.h"

pthread_mutex_t* get_server_window_mutex();

void lock_server_window_mutex();

void unlock_server_window_mutex();

void destroy_server_window_mutex();

void set_alarm(int wait_time);

pthread_t start_signal_listener(Window *window);

pthread_t start_ack_listener(Window *window);

void stop_listener (pthread_t thread);
