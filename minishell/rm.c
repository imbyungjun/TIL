#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <grp.h>

#define FLAG_F 0x01
#define FLAG_I 0x02
#define MAXLENGTH 256

char *getPerm(const struct stat stat_buf) {
	char *perm = (char *) malloc (sizeof(char) * 10);

	perm[0] = (stat_buf.st_mode & S_IRUSR) ? 'r' : '-';
	perm[1] = (stat_buf.st_mode & S_IWUSR) ? 'w' : '-';
	perm[2] = (stat_buf.st_mode & S_IXUSR) ? 'x' : '-';
	perm[3] = (stat_buf.st_mode & S_IRGRP) ? 'r' : '-';
	perm[4] = (stat_buf.st_mode & S_IWGRP) ? 'w' : '-';
	perm[5] = (stat_buf.st_mode & S_IXGRP) ? 'x' : '-';
	perm[6] = (stat_buf.st_mode & S_IROTH) ? 'r' : '-';
	perm[7] = (stat_buf.st_mode & S_IWOTH) ? 'w' : '-';
	perm[8] = (stat_buf.st_mode & S_IXOTH) ? 'x' : '-';
	perm[9] = '\0';

	return perm;
}

void opt_rm(int opt, const char *file_name) {
	char ans[MAXLENGTH], *perm;
	struct stat stat_buf;
	struct group *g;

	if (lstat(file_name, &stat_buf) < 0) {
		if (!(opt & FLAG_F))
			warn("%s", file_name);
		return;
	}

	/* 지울 파일이 디렉토리이면 에러를 출력 */
	if (S_ISDIR(stat_buf.st_mode)) {
		errno = EISDIR;
		warn("%s", file_name);
		return;
	}

	if (opt & FLAG_I) {		/* 옵션 -i */
		printf("remove %s? ", file_name);

		if (scanf("%s", ans) < 0)
			perror("scanf");
		
		if (ans[0] != 'y' && ans[0] != 'Y')
			return;

	} else if (opt & FLAG_F) {
		/* 삭제에 관련하여 질의를 받지 않음 */
	} else if (opt == 0) {
		if (!(stat_buf.st_mode & S_IWUSR)) {	/* 쓰기권한이 없는경우 질의요청 */
			g = getgrgid(getgid());		/* 그룹정보를 group 구조체에 할당받음 */
			perm = getPerm(stat_buf);	/* 접근권한을 문자열로 전달받음 */
		
			printf("override %s  %s/%s for %s? ", perm, getenv("USER"), 
									g->gr_name, file_name);
			
			/* 할당받은 접근권한 문자열의 할당해제 */
			free(perm);
			
			if (scanf("%s", ans) < 0)
				perror("scanf");

			if (ans[0] != 'y' && ans[0] != 'Y')
				return;
		}
	}
	
	if (unlink(file_name) < 0)
		warn("%s", file_name);	
}

void print_usage() {
	fprintf(stderr, "usage: rm [-f | -i] file ...\n       unlink file\n");
	exit(1);
}

int main(int argc, char **argv) {
	int i, ch, opt = 0;
	struct stat stat_buf;

	if (argc < 2) print_usage();

	if ((ch = getopt(argc, argv, "fi")) != -1) {
		switch (ch) {
			case 'f':
				opt |= FLAG_F;
				break;
			case 'i':
				opt |= FLAG_I;
				break;
			default:
				print_usage();
		}
	}

	if (opt == 0) i = 1;	/* 옵션이 명시되지 않은경우 */
	else i = 2;				/* 옵션이 명시된 경우 */

	for (; i < argc; i++) {
		opt_rm(opt, argv[i]);
	}
}
