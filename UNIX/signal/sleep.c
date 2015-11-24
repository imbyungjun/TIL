#include <signal.h>

static void sig_alrm() {
	return;
}

unsigned int sleep(unsigned int nsecs) {
	struct sigaction newact, oldact;
	sigset_t newmask, oldmask, suspmask;
	unsigned int unslept;

	newact.sa_handler = sig_alrm;
	sigemptyset(&newact.sa_mask);
	newact.sa_flags = 0;
	sigaction(SIGALRM, &newact, &oldact);
	/* set handler */

	sigemptyset(&newmask);
	sigaddset(&newmask, SIGALRM);
	sigprocmask(SIG_BLOCK, &newmask, &oldmask);
	/* block SIGALRM */

	alarm(nsecs);

	suspmask = oldmask;
	sigdelset(&suspmask, SIGALRM);

	sigsuspend(&suspmask);

	unslept = alarm(0);
	sigaction(SIGALRM, &oldact, 0);

	sigprocmask(SIG_SETMASK, &oldmask, 0);

	return (unslept);
}

int main() {
	sleep(5);
}
