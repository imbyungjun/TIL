#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	int fd;
	struct flock my_lock;

	my_lock.l_type = F_WRLCK;
	my_lock.l_whence = SEEK_SET;
	my_lock.l_start = 0;
	my_lock.l_len = 10;

	fd = open("test", O_RDWR);

	if (fcntl(fd, F_SETLKW, &my_lock) == -1) {
		perror("lock");
		exit(1);
	}
	printf("parent : locked record\n");

	switch(fork()) {
	   	case -1:
		   perror("fork");
		   exit(1);
		case 0:			/* child */
			if (fcntl(fd, F_SETLKW, &my_lock) == -1) {
				perror("lock");
				exit(1);
			}
			printf("child : locked record\n");
			printf("child : exiting\n");
			exit(0);
	}
	sleep(5);

	printf("parent : exiting\n");
	exit(0);
}
