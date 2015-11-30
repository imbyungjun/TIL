/*
 * ln.c
 *
 * 컴퓨터공학부
 * 20113316 임병준
 *
 * 주어진 파일명으로 원본파일의
 * link 또는 symbolic link를 생성하는 프로그램.
 */


#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>

#define FLAG_S 0x01

int (*linkf)(const char *, const char *);

/* print usage and exit */
void print_usage() {
	fprintf(stderr, "usage: ln [-s] source_file [target_file]\n");
	fprintf(stderr, "       ln [-s] source_file ... target_dir\n");
	fprintf(stderr, "       link source_file target_file\n");
	exit(1);
}

int main(int argc, char **argv) {
	int i, ch, opt = 0;
	struct stat stat_buf;
	char path[BUFSIZ];
	extern int optind;

	/* argv must be > 2 */
	if (argc < 3)
		print_usage();

	optind = 1;
	if ((ch = getopt(argc, argv, "s")) != -1) {
		switch(ch) {
			case 's':
				opt |= FLAG_S;
				break;
			default:
				print_usage();
		}
	}

	/* use symlink function or link function depending on option */
	linkf = (opt & FLAG_S)? (symlink) : (link);

	/* make link */
	if (linkf(argv[optind], argv[optind+1]) < 0)
		warn("%s", argv[optind+1]);
}
