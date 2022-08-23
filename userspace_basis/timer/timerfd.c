
#include <stdio.h>
#include <stdlib.h>		//for exit
#include <string.h>		//for memset
#include <sys/timerfd.h>	//for timerfd_xxx
#include <unistd.h>		//for sleep

#define TIMER_TYPE CLOCK_REALTIME

int main (int argc, char *argv[])
{
	int fd;
	fd_set rfds;
	struct itimerspec it;
	struct timespec start;
	struct timespec end;
	struct timeval tv_start;
	struct timeval tv_end;
	time_t sec;
	long nsec;
	struct timespec interval;
	int usec_delta;
	int sec_delta;
	int retval;

	if (argc < 3) {
		exit(EXIT_FAILURE);
	} else {
		sec = atol(argv[1]);
		nsec = atol(argv[2]);
	}
	retval = clock_getres(CLOCK_REALTIME, &start);
	if (retval != 0) {
		perror("clock_getres");
		exit(EXIT_FAILURE);
	}
	printf("start: %ld.%06ld\n", start.tv_sec, start.tv_nsec / 1000);
	retval = clock_getres(CLOCK_MONOTONIC, &start);
	if (retval != 0) {
		perror("clock_getres");
		exit(EXIT_FAILURE);
	}
	printf("start: %ld.%06ld\n", start.tv_sec, start.tv_nsec / 1000);
	retval = clock_getres(CLOCK_BOOTTIME, &start);
	if (retval != 0) {
		perror("clock_getres");
		exit(EXIT_FAILURE);
	}
	printf("start: %ld.%06ld\n", start.tv_sec, start.tv_nsec / 1000);
	fd = timerfd_create(TIMER_TYPE, TFD_NONBLOCK|TFD_CLOEXEC);
	if (-1 == fd) {
		perror("timerfd_create");
		exit(EXIT_FAILURE);
	}
	memset(&it, 0, sizeof(it));
	gettimeofday(&tv_start, NULL);
	it.it_value.tv_sec = sec;
	it.it_value.tv_nsec = nsec;
	timerfd_settime(fd, 0, &it, NULL);
	FD_ZERO(&rfds);
	FD_SET(0, &rfds);
	FD_SET(fd, &rfds);
	//timerfd_gettime(fd, &it);
	//printf("current: %ld.%06ld\n", it.it_value.tv_sec, it.it_value.tv_nsec / 1000);
	//sleep(1);
	//timerfd_gettime(fd, &it);
	//printf("current: %ld.%06ld\n", it.it_value.tv_sec, it.it_value.tv_nsec / 1000);
	retval = select(fd + 1, &rfds, NULL, NULL, NULL);
	if (retval == -1)
		perror("select()");
	else if (0 == retval) {
		printf("timeout\n");
		exit(EXIT_FAILURE);
	}
	if (FD_ISSET(fd, &rfds)) {
		printf("timer!\n");
		clock_getres(TIMER_TYPE, &end);
		gettimeofday(&tv_end, NULL);
	} else if (FD_ISSET(0, &rfds)) {
		printf("user input!\n");
		clock_getres(TIMER_TYPE, &end);
	} else {
		exit(EXIT_FAILURE);
	}
	printf("timer reached\n");
	if (end.tv_nsec < start.tv_nsec) {
		interval.tv_nsec = end.tv_nsec + 1000000000 - start.tv_nsec;
		interval.tv_sec = end.tv_sec - 1 - start.tv_sec;
	} else {
		interval.tv_nsec = end.tv_nsec - start.tv_nsec;
		interval.tv_sec = end.tv_sec - start.tv_sec;
	}
	printf("start: %ld.%06ld\n", start.tv_sec, start.tv_nsec / 1000);
	printf("end: %ld.%06ld\n", end.tv_sec, end.tv_nsec / 1000);
	printf("real timer passed: %ld.%06ld\n", interval.tv_sec, interval.tv_nsec / 1000);
	printf("time passed from %d.%06d to %d.%06d\n", tv_start.tv_sec, tv_start.tv_usec, tv_end.tv_sec, tv_end.tv_usec);
	if (tv_end.tv_usec < tv_start.tv_usec) {
		usec_delta = tv_end.tv_usec + 1000000 - tv_start.tv_usec;
		sec_delta = tv_end.tv_sec - tv_start.tv_sec - 1;
	} else {
		usec_delta = tv_end.tv_usec - tv_start.tv_usec;
		sec_delta = tv_end.tv_sec - tv_start.tv_sec;
	}

	printf("delta %d.%06d", sec_delta, usec_delta);
	if (sec_delta == sec && usec_delta - nsec / 1000 > 500)
		printf(" accurate more than 0.5ms!\n");
	else
		printf("\n");

	return 0;
}
