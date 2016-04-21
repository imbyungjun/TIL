/*
 *  power_manager.c
 *
 *  Set pid and threshold, print current battery usage mode when
 *  status change is occured.
 */

#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define STDOUT 1
#define STDERR 2
#define MAX_SIZE 1024

/* Path for procfs */
#define BATTERY_NOTIFY "/proc/battery_notify"
#define BATTERY_THRESHOLD "/proc/battery_threshold"

int set_pid();
void set_threshold();
void sig_set();
static void sig_handler(int);

/* Set sigactions */
void sig_set() {
	struct sigaction act;

	sigemptyset(&act.sa_mask);

	act.sa_handler = sig_handler;
	act.sa_flags = 0;

	sigaction(SIGUSR1, &act, 0);
	sigaction(SIGUSR2, &act, 0);

	sigaction(SIGINT, &act, 0);
	sigaction(SIGQUIT, &act, 0);
}	

/* Signal handler */
static void sig_handler(int signo) {
	switch (signo) {
		case SIGUSR1 : 
			write(2, "절전모드\n", 13); break;
		case SIGUSR2 :
			write(2, "일반모드\n", 13); break;
		case SIGINT :
			write(2, "Received: SIGINT\n",18); break;
		case SIGQUIT :
			write(2, "Received: SIGQUIT\n", 20); break;
		default : 
			write(2, "Received: Undefined Sigal\n", 11); break;
	}
}

/* Set pid on BATTERY_NOTIFY */
int set_pid() {
	int fd;
	pid_t pid, child;
	char buf[MAX_SIZE];

	pid = getpid();

	printf("PID = %d\n", pid);

	sprintf(buf, "%d", pid);

	if ((child = fork()) == 0) {		/* child */
		fd = open (BATTERY_NOTIFY, O_WRONLY | O_EXCL | O_TRUNC);
		if (fd < 0) { 
			perror("set pid failed");
			exit(1);
		}

		dup2(fd, STDOUT);
        
		execl("/bin/echo", "echo", buf, NULL);
		perror("execl echo error");
		exit(127);
	} else {		/* parent */
		waitpid(child);
	}

	return pid;
}

/* Set threshold value on BATTERY_THRESHOLD */
void set_threshold(char *thr) {
	int fd;
	pid_t child;

	printf("Threshold = %s\n", thr);

	if (strtol(thr, 0, 10) < 0 || strtol(thr, 0, 10) > 100) {
		printf("threshold value %ld is unexceptable\n", strtol(thr, 0, 10));
		exit(2);
	}

	if ((child = fork()) == 0) {		/* child */
		fd = open (BATTERY_THRESHOLD, O_WRONLY | O_EXCL | O_TRUNC);
		if (fd < 0) {
			perror("set threshold failed");
			exit(2);
		}

		dup2(fd, STDOUT);
		
		execl("/bin/echo", "echo", thr, NULL);
		perror("execl echo error");
		exit(127);
	} else {		/* parent */
		waitpid(child);
	}
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Usage :\n%s [threshold]\n", argv[0]);
		exit(0);
	}
		
	if (set_pid() < 0) 
		perror("set pid error");

	set_threshold(argv[1]);
	
	sig_set();		//sigaction()

	for ( ; ; ) pause();
}
