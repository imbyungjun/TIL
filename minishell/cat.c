#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>

#define BUFSIZE 4096
#define STDOUT 1
#define STDIN 0

/*
 * command line argument로 전달받은 파일을 읽거나
 * 표준입력에서 문자열을 읽어서 표준출력으로 출력한다.
 */


/* read from given file descriptor and write to stdout */
void cat_from(int fd) {
	int n;
	char buf[BUFSIZE];

	while((n = read(fd, buf, BUFSIZE)) > 0) 
		if(n > write(STDOUT, buf, n)) {
			perror("wrtie to stdout");
			exit(1);
		}
}

/* print usage */
void print_usage() {
	fprintf(stderr, "usage: cat [-benstuv] [file ...]\n");
}

/* check file types and print errmsg */
int type_check(char *file_name) {
	struct stat stat_buf;
	char errmsg[BUFSIZE];

	/* get information from given file */
	if (lstat(file_name, &stat_buf) < 0) {
		warn("%s", file_name);
		return -1;
	}
			
	/* print errmsg for not available file type */
	if (!S_ISREG(stat_buf.st_mode)) {
		if (S_ISDIR(stat_buf.st_mode)) {
			errno = EISDIR;
			warn("%s", file_name);
		}
		else if (S_ISCHR(stat_buf.st_mode) || S_ISBLK(stat_buf.st_mode)) {
			errno = ENOTSUP;
			warn("%s", file_name);
		}
		return -1;
	}
	return 0;
}

int main(int argc, char **argv) {
	int i, fd = STDIN, ch;
	char errmsg[BUFSIZE];

	if ((ch = getopt(argc, argv, "benstuv")) != -1) {
		switch(ch) {
			default:
				print_usage();
		}
	} else if (argc < 2 || !strcmp(argv[1], "-")) {
		cat_from(fd);
	} else {			/* read from files */
		for (i = 1; i < argc; i++) {		/* open files sequentially */
			/* file open */
			if ((fd = open(argv[i], O_RDONLY)) < 0) {
				warn("%s", argv[i]);
				continue;
			} 

			/* check file type */	
			if (type_check(argv[i]) < 0) {
				close(fd);
				continue;
			}

			cat_from(fd);

			/* file close */
			close(fd);
		} 
	}
	exit(0);
}
