#Signal Processing - 3

###Signal Functions
---
* Superset of the functionality of signal()
* sigprocmask(int how, const sigset_t *setp, sigset_t *osetp);  
	\- examine or change signal masks
* sigpending(sigset_t *setp);
	\- return the set of signals that are blocked and pending
* sigaction(int signo, const struct sigaction *act, struct sigaction oact);  
	\- examine or modify the action associated with a particular signal
* sigsuspend(const sigset_t *sigmask);  
	\- atomic operation(reset the signal mask and pause)
* sigsetjmp(sigjmp_buf env, int savemask) /  
 siglongjmp(sigjmp_buf env, init val))  
	\- nonlocal branching from a signal handler
	
####1. Sigprocmask function
```
#include <signal.h>
int sigprocmask (int how, const sigset_t *set, sigset_t *oset);
	Returns: 0 if OK, -1 on error
```
#####how
* SIG_BLOCK : redefine the new signal mask (set + oset)
* SIG_UNBLOCK : unblock the signals in set
* SIG_SETMASK : new signal mask = set

#####If there are any pending, unblocked signals after *sigprocmask* at least one of these signal is delivered to the process before *sigprocmask* returns

####2. Sigpending function
```
#include <signal.h>
int sigpending (sigset_t *set);
	Returns: 0 if OK, -1 on error
```
#####Returns the set of signals that are blocked from delivery and currently pending for the calling process  
#####- The set of signals is returned through the *set* argument

####3. Sigaction Function
```
#include <signal.h>
int sigaction (int signo, const struct sigaction *act, strcut sigaction *oact);
	Returns: 0 if OK, -1 on error


struct sigaction {
	void	(*sa_handler)(int);		/* address of signal handler */
	sigset_t	sa_mask;			/* additional signals to block */
	int		sa_flags;				/* signal options */
	void	(*sa_sigaction)(int, siginfo_t *, void *);
```
