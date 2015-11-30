/*
 * chmod.c
 *
 * 컴퓨터공학부
 * 20113316 임병준
 *
 * 주어진 8진수옵션으로 입력파일의
 * 접근권한을 변경하는 프로그램.
 */

#include <sys/stat.h>
#include <stdio.h>

/* print usage and exit */
void print_usage() {
	fprintf(stderr, "usage:  chmod mode file ...\n");
	exit(0);
}

int main(int argc, char **argv) {
	int i, ch;
	int perm;

	/* argc must be > 2 */
	if (argc < 3)
		print_usage();

	/* get option as octal number */
	perm = strtol(argv[1], (char**)NULL, 8);

	/* change permission */
	for (i = 2; i < argc; i++)
		if (chmod(argv[i], perm) < 0)
			warn("%s", argv[i]);
}
