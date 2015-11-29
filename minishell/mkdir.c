#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <libgen.h>

#define PERM 0777
#define MAX_LEN 256
#define FLAG_P 0x01

/* 
 * -p 옵션은 생성할 디렉토리의 경로를 명시할때,
 * 만약 중간과정의 디렉토리들이 존재하지 않는다면
 * 그 디렉토리들도 한번에 만들어주는 옵션이다.
 */

/* -p 옵션을 입력받은 경우의 수행 */
void opt_p(char *path_name) {
	char prePath[MAX_LEN] = "";
	char *dir;

	/* 경로상의 모든 디렉토리를 생성한다. */
	dir = strtok(path_name, "/");

	do {
		strcat(prePath, dir);
		strcat(prePath, "/");
		
		/* EEXIST 에러는 무시 */	
		if(mkdir(prePath, PERM) < 0) {
			if (errno == EEXIST) continue;
			perror("mkdir error");
			exit(2);
		}
	} while ((dir = strtok(NULL, "/"))); 
}

/* 사용법을 출력하고 종료 */
void print_usage() {
	fprintf(stderr, "usage: mkdir [-p] directory ...\n");
	exit(1);
}

int main(int argc, char **argv) {
	int i, ch, opt = 0;

	/* 매개변수는 2개 이상이어야한다. */
	if (argc < 2) 
		print_usage();
	
	/* -p 옵션이 주어졌는지 확인한다. */
	if ((ch = getopt(argc, argv, "p")) != -1) {
		switch (ch) {		
			case 'p':
				opt |= FLAG_P;
				break;
			default :
				exit(1);
		}
	}

	if (opt & FLAG_P) {
		for (i = 2; i < argc; i++) 
			opt_p(argv[i]);
	} else {
		for (i = 1; i < argc; i++) 
		if (mkdir(argv[i], PERM) < 0) {
			if (errno == EEXIST) {
				warn("%s", argv[i]);
				exit(1);
			} else if (errno == ENOENT) {
				warn("%s", dirname(argv[i]));
				exit(1);
			}
		}
	}
	return 0;
}
