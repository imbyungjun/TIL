#include <stdio.h>
#include <unistd.h>

#define STDOUT 1
#define BUFSIZE 4096

void print_head(int lines, const char *name) {
	char buf[BUFSIZE];
	FILE *fin = fopen(name, "r");

	while(lines-- && fgets(buf, BUFSIZE, fin))
		printf("%s", buf);
}

int main(int argc, char **argv) {
	int ch, lines = 10;
	extern char* optarg;		/* option argument */
	extern int optind;			/* option index */

	optind = 1;
	while((ch = getopt(argc, argv, "n:")) != -1) {
		switch(ch) {
			case 'n':
				lines = strtol(optarg, (char**)NULL, 10);
				break;
		}
	}

	print_head(lines, argv[optind]);
}
