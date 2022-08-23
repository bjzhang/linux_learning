#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	fd_set rfds;
	struct timeval tv;
	struct timeval start;
	struct timeval end;
	int user_sec;
	int user_usec;
	int usec_delta;
	int sec_delta;
	int retval;

	if (argc < 3)
		exit(EXIT_FAILURE);

	/* Watch stdin (fd 0) to see when it has input. */

	FD_ZERO(&rfds);
	FD_SET(0, &rfds);

	/* Wait up to five seconds. */

	user_sec = atoi(argv[1]);
	tv.tv_sec = user_sec;
	user_usec = atoi(argv[2]);
	tv.tv_usec = user_usec;

	gettimeofday(&start, NULL);
	retval = select(1, &rfds, NULL, NULL, &tv);
	/* Don't rely on the value of tv now! */
	gettimeofday(&end, NULL);

	if (retval == -1)
	perror("select()");
	else if (retval)
	printf("Data is available now.\n");
	/* FD_ISSET(0, &rfds) will be true. */
	else
	printf("No data within user input seconds(%d %d).\n", tv.tv_sec, tv.tv_usec);

	printf("time passed from %d.%06d to %d.%06d\n", start.tv_sec, start.tv_usec, end.tv_sec, end.tv_usec);
	if (end.tv_usec < start.tv_usec) {
		usec_delta = end.tv_usec + 1000000 - start.tv_usec;
		sec_delta = end.tv_sec - start.tv_sec - 1;
	} else {
		usec_delta = end.tv_usec - start.tv_usec;
		sec_delta = end.tv_sec - start.tv_sec;
	}

	printf("delta %d.%06d", sec_delta, usec_delta);
	if (sec_delta == user_sec && usec_delta - user_usec > 500)
		printf(" accurate more than 0.5ms!\n");
	else
		printf("\n");

	exit(EXIT_SUCCESS);
}

