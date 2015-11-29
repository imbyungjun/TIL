#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>

#define FLAG_S 0x01

int (*linkf)(const char *, const char *);

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

	/* 옵션에 따라 symlink 또는 link 함수를 사용 */
	linkf = (opt&FLAG_S)? (symlink) : (link);
	
	if (linkf(argv[optind], argv[optind+1]) < 0)
		warn("%s", argv[optind+1]);
}
