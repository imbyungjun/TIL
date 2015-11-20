#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>

#define STDIN 0
#define STDOUT 1
#define BUFSIZE 4096

/*
 * command line argument로 전달받은 파일을 읽거나
 * 표준입력에서 문자열을 읽어서 표준출력으로 출력한다.
 * 파일로의 리다이렉션을 할 경우 fully-buffered io로 변환되어
 * 정상작동이 되지 않는 경우를 방지하기 위해 non-buffered io인
 * system call read()와 write()를 이용해서 구현하였다.
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

/* check file types and print errmsg */
int type_check(char *file_name) {
	struct stat stat_buf;
	char errmsg[BUFSIZE];

	/* get information from given file */
	if (lstat(file_name, &stat_buf) < 0) {
		sprintf(errmsg, "cat: %s", file_name);
		perror(errmsg);
		return -1;
	}
			
	/* print errmsg for not available file type */
	if (!S_ISREG(stat_buf.st_mode)) {
		if (S_ISDIR(stat_buf.st_mode))
			fprintf(stderr, "cat: %s: Is a direcotry\n", file_name);
		else if (S_ISCHR(stat_buf.st_mode) || S_ISBLK(stat_buf.st_mode))
			fprintf(stderr, "cat: %s: Operation not supported by device\n", file_name);
		close(fd);
		return -1;
	}
	return 0;
}


int main(int argc, char **argv) {
	int i, fd;
	char errmsg[BUFSIZE];

	if (argc < 2 || !strcmp(argv[1],"-")) {		/* read from stdin */
		cat_from(STDIN);	
	} else {			/* read from files */
		for (i = 1; i < argc; i++) {	/* open files sequentially */
			/* file open */
			if ((fd = open(argv[i], O_RDONLY)) < 0) {
				sprintf(errmsg, "cat: %s", argv[i]);
				perror(errmsg);
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
