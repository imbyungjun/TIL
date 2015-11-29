#include <sys/stat.h>
#include <stdio.h>

/* 사용법 출력 */
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

	/* 옵션을 8진수로 입력받음 */
	perm = strtol(argv[1], (char**)NULL, 8);

	/* 뒤이어 전달받는 모든 파일을 해당 모드로 변환 */
	for (i = 2; i < argc; i++) 
		if (chmod(argv[i], perm) < 0)
			warn("%s", argv[i]);
}
