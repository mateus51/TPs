#include <sys/time.h>
#include <stdlib.h>

double get_time() {
	struct timeval time;
	gettimeofday(&time, NULL);
	return time.tv_sec + (time.tv_usec/1000000.0);
}
