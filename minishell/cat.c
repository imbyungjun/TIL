/*
 * cat.c
 *
 * 컴퓨터공학부
 * 20113316 임병준
 *
 * command line argument로 전달받은 파일을 읽거나
 * 표준입력에서 문자열을 읽어서 표준출력으로 출력하는 프로그램.
 */


#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>

#define STDOUT 1
#define STDIN 0

/* read from given file descriptor and write to stdout */
void my_cat(int fd) {
	int n;
	char buf[BUFSIZ];

	while((n = read(fd, buf, BUFSIZ)) > 0)
		if(n > write(STDOUT, buf, n)) {
			perror("wrtie to stdout");
			exit(1);
		}
}

/* print usage and exit*/
void print_usage() {
	fprintf(stderr, "usage: cat [-benstuv] [file ...]\n");
}

/*
 * check file type and print errmsg
 * return 0 on Success, -1 on Error
 */
int type_check(char *file_name) {
	struct stat stat_buf;
	char errmsg[BUFSIZ];

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
	int i, fd, ch;
	char errmsg[BUFSIZ];

	/* all options are not available */
	if ((ch = getopt(argc, argv, "benstuv")) != -1) {
		switch(ch) {
			default:
				print_usage();
		}
	}

	/* read from standard input */
	if (argc < 2 || !strcmp(argv[1], "-"))
		my_cat(STDIN);

	/* read from files */
	for (i = 1; i < argc; i++) {
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

		my_cat(fd);

		/* file close */
		close(fd);
	}

	exit(0);
}
