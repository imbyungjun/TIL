/*
 * ls.c
 *
 * 컴퓨터공학부
 * 20113316 임병준
 *
 * 파일 또는 디렉토리의 정보를 출력해주는 프로그램.
 * -l 옵션은 부가적인 정보들을 함께 출력해주는 옵션이다.
 * -a 옵션은 숨김파일들도 모두 출력해주는 옵션이다.
 * -R 옵션은 디렉토리가 있다면 그 디렉토리의 내용까지
 * 재귀적으로 출력해주는 옵션이다.
 */

#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#define FLAG_L 0x01
#define FLAG_A 0x02
#define FLAG_R 0x04

static int start_flag;
int my_ls(const char *, int);

/* print usage and exit */
void print_usage() {
	fprintf(stderr, "usage: ls [-alR] [file...]\n");
	exit(1);
}

/* return permission info */
char *get_perm(const char *name) {
	struct stat stat_buf;
	char *perm = (char *)malloc(sizeof(char)*11);

	if (lstat(name, &stat_buf) < 0)
		warn("%s", name);

	if (S_ISDIR(stat_buf.st_mode))
		perm[0] = 'd';
	else if (S_ISREG(stat_buf.st_mode))
		perm[0] = '-';
	else if (S_ISFIFO(stat_buf.st_mode))
		perm[0] = 'p';
	else if (S_ISLNK(stat_buf.st_mode))
		perm[0] = 'l';
	else if (S_ISSOCK(stat_buf.st_mode))
		perm[0] = 's';
	else if (S_ISCHR(stat_buf.st_mode))
		perm[0] = 'c';
	else if (S_ISBLK(stat_buf.st_mode))
		perm[0] = 'b';

	perm[1] = (stat_buf.st_mode & S_IRUSR) ? 'r' : '-';
	perm[2] = (stat_buf.st_mode & S_IWUSR) ? 'w' : '-';
	perm[3] = (stat_buf.st_mode & S_IXUSR) ? 'x' : '-';
	perm[4] = (stat_buf.st_mode & S_IRGRP) ? 'r' : '-';
	perm[5] = (stat_buf.st_mode & S_IWGRP) ? 'w' : '-';
	perm[6] = (stat_buf.st_mode & S_IXGRP) ? 'x' : '-';
	perm[7] = (stat_buf.st_mode & S_IROTH) ? 'r' : '-';
	perm[8] = (stat_buf.st_mode & S_IWOTH) ? 'w' : '-';
	perm[9] = (stat_buf.st_mode & S_IXOTH) ? 'x' : '-';
	perm[10] = '\0';

	return perm;
}

/* 
 * read directory and get each file name,
 * and call my_ls function with file name as argument
 */
void print_dir(const char *name, int opt) {
	struct dirent *dir;
	struct stat stat_buf;
	DIR *dp;
	char *perm;
	ssize_t cnt = 0;		/* count for file sizes */

	if (strcmp(name, ".")) {
		chdir(name);
		strcpy(name, ".");
	}

	if ((dp = opendir(name)) == NULL) {
		warn("%s", name);
		return;
	}

	/*
	 * get total blocks and print it 
	 * before other informations
	 */
	if (opt & FLAG_L) {
		while ((dir = readdir(dp))) {
			if (dir->d_ino != 0) {
				if (!(opt & FLAG_A) && (dir->d_name[0] == '.'))
					continue;

				if (lstat(dir->d_name, &stat_buf) < 0) {
					warn("%s", dir->d_name);
					return;
				}
				cnt += stat_buf.st_blocks;
			}
		}
		printf("total %d\n", cnt);
	}

	/* go back to the beginning of the directory */
	rewinddir(dp);

	/* print informations by call my_ls function */
	while ((dir = readdir(dp))) {
		if (dir->d_ino != 0) {
			if (!(opt & FLAG_A) && (dir->d_name[0] == '.'))
				continue;
			
			my_ls(dir->d_name, opt);
		}
	}
	closedir(dp);
}

int my_ls(const char *name, int opt) {
	struct stat stat_buf;
	struct passwd *pw;
	struct group *gr;
	struct tm *tm;
	char *perm;
	int cnt = 0;

	if (lstat(name, &stat_buf) < 0) {
		warn("%s", name);
		return -1;
	}


	if (start_flag & (opt & FLAG_R)) {				/* option -R */
		/* 아직 구현 못함 */
	}
	else if (!(start_flag++) && S_ISDIR(stat_buf.st_mode)) {
		print_dir(name, opt);
	} else if (opt & FLAG_L) {		/* option -l */
		perm = get_perm(name);
		pw = getpwuid(stat_buf.st_uid);
		gr = getgrgid(stat_buf.st_gid);
		tm = localtime(&stat_buf.st_mtime);

		printf("%s %2d %s  %s  %4d %02d %02d %02d:%02d %s\n",
				perm, stat_buf.st_nlink, pw->pw_name, gr->gr_name, stat_buf.st_size,
				tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, name);
		free(perm);
	} else {				/* default option */
		printf("%s\t", name);
	}

	return 0;
}

int main(int argc, char **argv) {
	int i;
	int ch, opt = 0;

	/* option handler */
	while ((ch = getopt(argc, argv, "alR")) != -1) {
		switch(ch) {
			case 'a':
				opt |= FLAG_A;
				break;
			case 'l':
				opt |= FLAG_L;
				break;
			case 'R':
				opt |= FLAG_R;
				break;
			default:
				print_usage();
		}
	}

	if ((opt && argc < 3) || (!opt && argc < 2))
		my_ls(".", opt);
	else {
		/*
		 * i = 1,		option is not specified
		 * i = 2,		option is specified
		 */
		for ((opt!=0)?(i=2):(i=1); i < argc; i++)
			my_ls(argv[i], opt);
	}
	printf(!(opt & FLAG_L)?"\n":"");
}
