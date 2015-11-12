#Pipe
-
**Pipe** is one of interprocess communication(IPC) method in UNIX.   

* **Two constraint of pipe**
	- Half-duplex : data flows only in one direction.
	- Can be used between processes that have common ancestor.  
	
	int pipe(int filedes[2]);
			returns: 0 if OK, -1 on Error
				
	filedes[0] : open for reading  
	filedes[1] : open for writing
	
* **Pipes - parent and child processes**
	
		parent => child				child => parent
		parent closes fd[0];		parent closes fd[1];
		child closes fd[1];			child closes fd[0];
	- If writer close fd, send EOF to reader.
	- If reader close fd, generate SIGPIPE, write got signal and return -1.

-
* **dup**  

		int dup(int filedes);  
				returns: file descriptor number, -1 on Error
	Allocate the first available descriptor same as filedes.
* **dup2**

 		int dup2(int fd1, int fd2);
 				returns: file descriptor number, -1 on Error
 	Allocate fd2 as fd1.
 	
-
#Example  
	
	#include <fcntl.h>
	#include <unistd.h>
	
	#define MAXLINE 30
	#define STDIN_FILENO 0
	
	int main(int argc, char *argv[]) {
		int n, fin, fd[2];
		pid_t pid;
		char line[MAXLINE];
		
		if(pipe(fd) < 0) err_sys("pipe error");
		fin = open(argv[1], O_RDONLY);
		
		if((pid = fork()) < 0) err_sys("fork error");
		else if (pid > 0) {			/* parent */
			close(fd[0]);
			while((n = read(fin, line, MAXLINE))
				write(fd[1], line, n);
		} else {			/* child */
			close(fd[1]);
			
			close(STDIN_FILENO);
			dup(fd[0]);		/* duplicate stdin */
			execl("/bin/more", "more", (char *)0);
		}
		exit(0);
	}

Parent read the file(argv[1]) and write to pipe.  
Child duplicate read from pipe to stdin, then execute "more".  
( more - pager command line tool )  
It's the same as executing "more", but using pipe.

-
#Popen and Pclose
Using pipe as a FILE struct.
	
	FILE *popen(const char *cmdstring, const char *type);
			returns: file pointer if OK, NULL on Error

	int pclose(FILE *fp);
			returns: termination status, -1 on Error
-
	fp = popen(command, "r");
parent : fp <= command : stdout

	fp = popen(command, "w");
parent : fp => command : stdin


-
#Coprocesses
Interprocess communication with 1:1.
	
	parent					child
	fd1[1] =>	pipe1 => 	stdin
	fd2[0] <=	pipe2 <=	stdout
	
-
#Example

	static void sig_pipe(int signo) {
		printf("SIGPIPE caught\n");
		exit(1); 
	}

	int main() {
		int n, fd1[2], fd2[2];
		pid_t pid;
		char line[MAXLINE];
		if (signal(SIGPIPE, sig_pipe) == SIG_ERR)
			err_sys("signal error");
		if (pipe(fd1) < 0 || pipe(fd2) < 0)
			err_sys("pipe error");
		if ( (pid = fork()) < 0)
			err_sys("fork error");
		else if (pid > 0) { /* parent */ 
			close(fd1[0]);
			close(fd2[1]);
			
			while (fgets(line, MAXLINE, stdin) != NULL) {
				n = strlen(line);
				if (write(fd1[1], line, n) != n)
					err_sys("write error to pipe");
				if ( (n = read(fd2[0], line, MAXLINE)) < 0)
					err_sys("read error from pipe"); 
				if (n == 0) {
					err_msg("child closed pipe"); 
					break;
				}
				line[n] = 0; /* null terminate */ 
				
				if (fputs(line, stdout) == EOF)
					err_sys("fputs error");
			}
       	if (ferror(stdin))
				err_sys("fgets error on stdin"); 
			exit(0);
		} else { /* child */ 
			close(fd1[1]);
			close(fd2[0]);
			if (fd1[0] != STDIN_FILENO) {
				if (dup2(fd1[0], STDIN_FILENO) != STDIN_FILENO) 
					err_sys("dup2 error to stdin");
        	close(fd1[0]);
			}
			if (fd2[1] != STDOUT_FILENO) {
				if (dup2(fd2[1], STDOUT_FILENO) != STDOUT_FILENO) 
					err_sys("dup2 error to stdout");
        		close(fd2[1]);
			}
			if (execl("./add2", "add2", (char *) 0) < 0)
				err_sys("execl error");
		}
	}
-
#FIFO
* Named pipe
* Unrelated processes can exchange data
* FIFO is a type of file : FIFO type
* Normal file I/O functions all works with FIFO

		int mkfifo(const char *path, mode_t mode);
				returns: 0 if OK, -1 on Error

-
#Example
dummy.c

	#include <stdio.h>
	#include <sys/types.h>
	#include <fcntl.h>

	#define MAXLINE 30
	#define STDIN_FILENO 0
	#define STDOUT_FILENO 1

	void err_sys(const char *x) { perror(x); }

	int main(int argc, char *argv[]) {
		int n;
		pid_t pid;
		char line[MAXLINE];
		int fifo1, fifo2;

		fifo1 = open(argv[1], O_WRONLY);
		fifo2 = open(argv[2], O_RDONLY);

		while(fgets(line, MAXLINE, stdin) != NULL) {
			n = strlen(line);
			if(write(fifo1, line, n) != n)
				err_sys("write error to pipe");
			if((n = read(fifo2, line, MAXLINE)) < 0)
				err_sys("read error from pipe");
			if(n == 0) {
				err_sys("child closed pipe");
				break;
			}
			line[n] = 0;
			if(fputs(line, stdout) == EOF)
				err_sys("fputs error");
		}
		close(fifo1);
		close(fifo2);
	
		exit(0);
	}

-
	$ mkfifo fifo1
	$ mkfifo fifo2
	$ cat < fifo1 > fifo2 &
	$ dummy fifo1 fifo2
