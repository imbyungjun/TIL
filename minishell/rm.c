/*
 * rm.c
 *
 * 컴퓨터공학부
 * 20113316 임병준
 *
 * 주어진 파일을 삭제한다.
 * 쓰기권한이 없을 경우 삭제여부를
 * 사용자에게 질의한다.
 */


#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <grp.h>

#define FLAG_F 0x01
#define FLAG_I 0x02
#define MAXLENGTH 256

/* return permission info */
char *getPerm(const struct stat stat_buf) {
	/*
	 * memory allocation for permission string.
	 * It will free after print it out.
	 */
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

void my_rm(int opt, const char *file_name) {
	char ans[MAXLENGTH], *perm;
	struct stat stat_buf;
	struct group *g;

	/* get file information */
	if (lstat(file_name, &stat_buf) < 0) {
		if (!(opt & FLAG_F))
			warn("%s", file_name);
		return;
	}

	/* if file to remove is directory, print error */
	if (S_ISDIR(stat_buf.st_mode)) {
		errno = EISDIR;
		warn("%s", file_name);
		return;
	}

	if (opt & FLAG_I) {		/* option -i */
		printf("remove %s? ", file_name);

		if (scanf("%s", ans) < 0)
			perror("scanf");

		if (ans[0] != 'y' && ans[0] != 'Y')
			return;

	} else if (opt & FLAG_F) {	/* option -f */

		/* Don't ask query for remove */

	} else if (!opt) {			/* default option */
		/* if proccess doesn't have permission for write, ask query */
		if (!(stat_buf.st_mode & S_IWUSR)) {
			g = getgrgid(getgid());		/* get group information */
			perm = getPerm(stat_buf);	/* get permission info as string */

			printf("override %s  %s/%s for %s? ", perm, getenv("USER"),
									g->gr_name, file_name);

			/* memory free for permission string */
			free(perm);

			/* get answer 'Yes' or 'No' */
			if (scanf("%s", ans) < 0)
				perror("scanf");

			/*
			 * if answer is y__ or Y__, remove file.
			 * or not, don't remove file. return here.
			 */
			if (ans[0] != 'y' && ans[0] != 'Y')
				return;
		}
	}

	if (unlink(file_name) < 0)
		warn("%s", file_name);
}

/* print usage and exit */
void print_usage() {
	fprintf(stderr, "usage: rm [-f | -i] file ...\n       unlink file\n");
	exit(1);
}

int main(int argc, char **argv) {
	int i, ch, opt = 0;
	struct stat stat_buf;

	/* argc must be > 1 */
	if (argc < 2) print_usage();

	/* option handler */
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

	/*
	 * i = 1,		option is not specified
	 * i = 2,		option is specified
	 */

	for ((!opt)?(i=1):(i=2); i < argc; i++) {
		my_rm(opt, argv[i]);
	}
}
