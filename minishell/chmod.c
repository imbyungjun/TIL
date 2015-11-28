#include <sys/stat.h>
#include <stdio.h>

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

	perm = strtol(argv[1], (char**)NULL, 8);

	for (i = 2; i < argc; i++) 
		if (chmod(argv[i], perm) < 0)
			warn("%s", argv[i]);
}
