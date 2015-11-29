/*
 * Tail.c
 *
 * 주어진 라인수 만큼 파일 또는 표준입력에서
 * 읽어서 표준출력으로 출력하는 프로그램.
 */


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFSIZE 4096

/* read from fp and wrtie to stdout */
void print_tail(int lines, FILE *fp) {
	int i, cnt = 0;
	int p;
	char **buf = (char **)malloc(sizeof(char*) * lines);

	for (i = 0; i < lines; i++) 
		buf[i] = (char *)malloc(sizeof(char) * BUFSIZE);

	while (fgets(buf[++cnt%lines], BUFSIZE, fp)) { }
	
	p = cnt % lines;

	do {
		printf("%s", buf[cnt++%lines]);
	} while (p != cnt % lines);

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
	int multi_operand = 0, flag = 0;
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

	/* 매개변수로 파일이 입력되지 않은 경우 */
	if (argc < 2) print_tail(lines, stdin);

	if (argc < 2) multi_operand = 1;

	while (--argc > 0) {
		if ((fp = fopen(argv[optind++], "r")) == NULL) {
			warn("%s", argv[optind-1]);
			flag = 0;
			continue;
		}

		if (flag++ && argc > 0)
			printf("\n");

		if (multi_operand)
			printf("==> %s <==\n", argv[optind-1]);

		print_tail(lines, fp);
		fclose(fp);
	}
}
