#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define STDOUT 1
#define BUFSIZE 4096

void print_head(int lines, FILE *fp) {
	char buf[BUFSIZE];
	
	while(lines-- && fgets(buf, BUFSIZE, fp))
		printf("%s", buf);
}

void print_usage() {
	fprintf(stderr, "usage: head [-n lines] [file ...]\n");
}

int main(int argc, char **argv) {
	int ch, lines = 10;			/* default lines value = 10 */
	int multi_operand = 0, flag = 0;
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
				exit(1);
		}
	}

	if (argc > 2) multi_operand = 1;
	/* print head */
	while (--argc > 0) {
		if ((fp = fopen(argv[optind++], "r")) == NULL) {
			warn("%s", argv[optind-1]);
			flag = 0;
			continue;
		}

		if (flag++ && argc > 1) 
			printf("\n");

		if (multi_operand) 
			printf("==> %s <==\n", argv[optind-1]);

		print_head(lines, fp);
		fclose(fp);
	}	
}
