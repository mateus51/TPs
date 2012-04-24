#include "benchmark.h"


struct timeval elapsedTime(struct timeval *start_time, struct timeval *end_time) {
	struct timeval result;

	/* Perform the carry for the later subtraction by updating y. */
	if (end_time->tv_usec < start_time->tv_usec) {
		 int nsec = (start_time->tv_usec - end_time->tv_usec) / 1000000 + 1;
		 start_time->tv_usec -= 1000000 * nsec;
		 start_time->tv_sec += nsec;
	}

	if ((end_time->tv_usec - start_time->tv_usec) > 1000000) {
		 int nsec = (end_time->tv_usec - start_time->tv_usec) / 1000000;
		 start_time->tv_usec += 1000000 * nsec;
		 start_time->tv_sec -= nsec;
	}

	/* Compute the time remaining to wait.
	  tv_usec is certainly positive. */
	result.tv_sec = end_time->tv_sec - start_time->tv_sec;
	result.tv_usec = end_time->tv_usec - start_time->tv_usec;

	/* Return result in seconds */
	return result;
}

void printTime(struct timeval *start_time, struct timeval *end_time) {
	struct timeval result = elapsedTime(start_time, end_time);
	float elapsed_time = (float) result.tv_sec + ((float) result.tv_usec / 1000000);
	printf(" -> %f segundos\n", elapsed_time);
}
