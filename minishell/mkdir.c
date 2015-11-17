#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

#define PERM 0777
#define MAX 100

/* 
 * -p 옵션은 생성할 디렉토리의 경로를 명시할때,
 * 만약 중간과정의 디렉토리들이 존재하지 않는다면
 * 그 디렉토리들도 한번에 만들어주는 옵션이다.
 */

int main(int argc, char **argv) {
	char buf[MAX], prePath[MAX] = "";
	char *dir;

	/* argc must be > 1 */
	if (argc < 2) {
		perror("Usage: mkdir <directories>");
		exit(1);
	}

	dir = strtok(argv[1], "/");
	if(mkdir(dir, PERM) < 0) {
		if (errno != EEXIST) {
			perror("mkdir error");
			exit(2);
		}
	}
	strcat(prePath, dir);

	while ((dir = strtok(NULL, "/"))) {
		if(mkdir(dir, PERM) < 0) {
			if (errno == EEXIST) continue;
			perror("mkdir error");
			exit(2);
		}
		strcat(dir, "/");
		strcat(prePath, dir);
	}
		
	return 0;
}
