/*
 * head.c
 *
 * 컴퓨터공학부
 * 20113316 임병준
 *
 * 주어진 라인수 만큼 파일 또는 표준입력에서
 * 읽어서 가장 앞부분부터 표준출력으로 출력하는 프로그램.
 */


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/* read from fp and write to stdout */
void my_head(int lines, FILE *fp) {
	char buf[BUFSIZ];

	while(lines-- && fgets(buf, BUFSIZ, fp))
		printf("%s", buf);
}

/* print usage and exit */
void print_usage() {
	fprintf(stderr, "usage: head [-n lines] [file ...]\n");
	exit(1);
}

int main(int argc, char **argv) {
	int ch, lines = 10;			/* default lines value = 10 */
	int multi_operand = 0, newline_flag = 0;
	FILE *fp;
	extern char* optarg;		/* option argument */
	extern int optind;			/* option index */

	/* option handler */
	optind = 1;
	if ((ch = getopt(argc, argv, "n:")) != -1) {
		switch(ch) {
			case 'n':
				lines = strtol(optarg, (char**)NULL, 10);
				if (lines < 1) {
					errx(1, "illegal line count -- %s", optarg);
				}
				argc -= 2;
				break;
			default :		/* unexpected options */
				print_usage();
		}
	}

	/* no input file, read from stdin */
	if (argc < 2) my_head(lines, stdin);

	/* flag for multiple operands */
	if (argc > 2) multi_operand = 1;

	while (--argc > 0) {
		/* file open */
		if ((fp = fopen(argv[optind++], "r")) == NULL) {
			warn("%s", argv[optind-1]);
			newline_flag = 0;
			continue;
		}

		/* newline for multiple operands */
		if (newline_flag++)
			printf("\n");

		/* print file name for multiple operands */
		if (multi_operand)
			printf("==> %s <==\n", argv[optind-1]);

		my_head(lines, fp);
		fclose(fp);
	}
}
