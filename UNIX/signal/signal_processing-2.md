# Signal Processing - 2

### Signals were unreliable in earlier version of UNIX
* If kernel is busy, signals could get lost.
* The action for the signal was reset to its default each time the signal occurred. (We had to reset action in processing function)
* A process had a little control over a signal.
	- can catch or ignore the signal, but can't *block* it
	- unable to turn a signal off when it didn't want the signal to occur. (all it can do was ignore the signal)

###Can't prevent the following signals from occurring, but only *remember* if they do occur

	int sig_int();		/* my signal handling func */
	...
	signal(SIGINT, sig_int);	/* establish handler */
	...
	sig_int() {
		signal(SIGINT, sig_int);	/* reestablish handler */
		...		/* process the signal */
	}
Q ) What happens if the interrupt signal occurs again before signal() in sig_int() executes?  
A ) Can't reestablish handler, so process would die.

	/* set the flag to remember that an interrupt occurs */
	int sig_int_flag;
	int sig_int();	
	
	int main() {
		signal(SIGINT, sig_int);
		...
		while(sig_int_flag == 0)
			pause();	/* waiting for signal */
		...
	}
	
	sig_int() {
		signal(SIGINT, sig_int);
		sig_int_flag = 1;	/* set flag for main loop to examine */
	}
Q ) What happens if the interrupt signal occurs again before pause() and after while statment?  
A ) ???

--- 
### Reliable Signal Terminology and Semantics
* A signal is **generated** for a process when the event that causes the signal occurs.
* A signal is **delivered** to a process when the action for a signal is taken.
* During the time between the generation of signal and its delivery, the signal is said to be **pending**.
* Each process has a signal mask that defines the set of signals currently blocked from delivery to that process
* **blocking** the delivery of a signal
	- A blocked signal(with default or catch signal action) remains pending until
		- unblocks the signal
		- changes the action to ignore the signal
	- What to do with a blocked signal is determined when the signal is delivered, not when it is generated
		- This allows the process to change the action for the signal before it is delivered
	- Most Unix does not queue blocked signals generated more than once. The Unix kernel just delivers the signal once.
	
---
#Signal sets
* A data type to represent multiple signals (sigset_t)  
* Do no assume global/static variable initialization in C for sigset_t  
* Functions to manipulate signal sets

``` 
#include <signal.h>
int sigemptyset(sigset_t *set);
int sigfillset(sigset_t *set);
int sigaddset(sigset_t *set, int signo);
int sigdelset(sigset_t *set, int signo);
		all return : 0 if OK, -1 on Error
int sigismember(const sigset_t *set, int signo);
		returns: 1 if True, 0 if false
```