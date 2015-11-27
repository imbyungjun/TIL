#include <unistd.h>
#include <fcntl.h>
#include <utime.h>

#define PERM 0644

void set_time(const char *file_name) {
	struct utimbuf ubuf;

	utime(file_name, NULL);
}

int mytouch(const char *file_name) {
	int fd;

	/* file not exists. just close it */
	if ((fd = open(file_name, O_CREAT | O_EXCL, PERM)) > -1) {
		close(fd);
		return 0;
	}
	
	/* file exists. update time */	
	if ((fd = open(file_name, O_WRONLY)) < 0) {
		perror("file open");
		return -1;
	} else {
		set_time(file_name);
		return 1;
	}
}

int main(int argc, char **argv) {
	int i;

	for (i = 1; i < argc; i++)
		mytouch(argv[i]);
	
	exit(0);
}
