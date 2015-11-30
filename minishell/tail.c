/*
 * tail.c
 *
 * 컴퓨터공학부
 * 20113316 임병준
 *
 * 주어진 라인수 만큼 파일 또는 표준입력에서
 * 읽어서 가장 뒷부분부터 표준출력으로 출력하는 프로그램.
 */


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/* read from fp and wrtie to stdout */
void my_tail(int lines, FILE *fp) {
	int i, cnt = 0;
	int p;
	char **buf;

	/* memory allocation for tail buffer */
	buf = (char **)malloc(sizeof(char*) * lines);
	for (i = 0; i < lines; i++)
		buf[i] = (char *)malloc(sizeof(char) * BUFSIZ);

	/* read file while fill tail buffer */
	while (fgets(buf[cnt++%lines], BUFSIZ, fp)) { }

	/* offset of current buffer index */
	p = (--cnt) % lines;

	/* flush buffer while reach the offset */
	do {
		printf("%s", buf[cnt++%lines]);
	} while (p != cnt % lines);

	/* memory free */
	for (i = 0; i < lines; i++)
		free(buf[i]);
	free(buf);
}

/* print usage and exit */
void print_usage() {
	fprintf(stderr, "usage: tail [-n #] [file ...]\n");
	exit(1);
}

int main(int argc, char **argv) {
	int ch, lines = 10;
	int multi_operand = 0, newline_flag = 0;
	FILE *fp;
	extern char* optarg;
	extern int optind;

	/* option handler */
	optind = 1;
	if ((ch = getopt(argc, argv, "n:")) != -1) {
		switch (ch) {
			case 'n':
				lines = strtol(optarg, (char**)NULL, 10);
				if (lines < 1) {
					errx(1, "illegal line count -- %s", optarg);
				}
				argc -= 2;
				break;
			default:
				print_usage();
		}
	}

	/* no input file, read from stdin */
	if (argc < 2) my_tail(lines, stdin);

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
		if (newline_flag++ && argc > 0)
			printf("\n");

		/* print file name for multiple operands */
		if (multi_operand)
			printf("==> %s <==\n", argv[optind-1]);

		my_tail(lines, fp);
		fclose(fp);
	}
}
