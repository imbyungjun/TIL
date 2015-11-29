#include <unistd.h>
#include <fcntl.h>
#include <utime.h>

#define PERM 0644

/*
 * 존재하지 않는 파일을 매개변수로 입력받은 경우 
 * 내용이 빈 일반파일을 생성한다.
 * 이미 존재하는 파일을 매개변수로 입력받은 경우
 * 파일의 마지막 수정시간, 마지막 접근시간을
 * 현재시간으로 갱신한다.
 */

/* utime함수를 이용해서 마지막 수정시간,
 * 마지막 접근시간을 현재시간으로 갱신.
 */
void set_time(const char *file_name) {
	struct utimbuf ubuf;

	if (utime(file_name, NULL) < 0) {
		warn("%s", file_name);
		exit(1);
	}
}

/* open을 이용해여 파일의 존재 유무를 확인하여
 * 시간을 갱신하거나 빈파일을 새로 생성한다.
 */
int my_touch(const char *file_name) {
	int fd;

	/* file not exists. just close it */
	if ((fd = open(file_name, O_CREAT | O_EXCL, PERM)) > -1) {
		close(fd);
		return 0;
	}
	
	/* file exists. update time */	
	set_time(file_name);
	return 1;
}

int main(int argc, char **argv) {
	int i;

	/* 각각의 매개변수에 touch를 수행 */
	for (i = 1; i < argc; i++)
		my_touch(argv[i]);
	
	exit(0);
}
