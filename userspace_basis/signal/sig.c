
#include <stdio.h>	//for printf
#include <stdlib.h>	//for exit
#include <unistd.h>	//for sleep
#include <signal.h>	//for sigaction

volatile int exit_requested = 0;

void user_exit(int sig, siginfo_t *info, void *ucontext)
{
	printf("signal is %d\n", sig);
	exit_requested = 1;
}

int main(int argc, char *argv[])
{
	struct sigaction sig = {
		.sa_sigaction = user_exit,
		.sa_flags = SA_RESTART || SA_SIGINFO
	};
	struct sigaction sigterm_old;
	struct sigaction sigint_old;

	sigemptyset(&sig.sa_mask);
	if (sigaction(SIGTERM, &sig, &sigterm_old) == -1)
		exit(EXIT_FAILURE);

	if (sigaction(SIGINT, &sig, &sigint_old) == -1)
		exit(EXIT_FAILURE);

	while(!exit_requested) {
		printf("waiting for user exit\n");
		sleep(1);
	}
	printf("exit!");

	return 0;
}
