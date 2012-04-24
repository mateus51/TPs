#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <stdio.h>
#include <sys/time.h>

struct timeval elapsedTime(struct timeval *start_time, struct timeval *end_time);

void printTime(struct timeval *start_time, struct timeval *end_time);

#endif
