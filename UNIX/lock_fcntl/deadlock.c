#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	int fd;
	struct flock first_lock;
	struct flock second_lock;

	first_lock.l_type = F_WRLCK;
	first_lock.l_whence = SEEK_SET;
	first_lock.l_start = 0;
	first_lock.l_len = 10;

	second_lock.l_type = F_WRLCK;
	second_lock.l_whence = SEEK_SET;
	second_lock.l_start = 10;
	second_lock.l_len = 5;

	fd = open("test", O_RDWR);

	if (fcntl(fd, F_SETLKW, &first_lock) == -1)
		perror("A");

	printf("A : Lock succeeded (proc %d)\n", getpid());

	switch(fork()) {
		case -1:
			perror("fork");
		case 0:
			if (fcntl(fd, F_SETLKW, &second_lock) == -1)
				perror("B");
			
			printf("B : Lock succeeded (proc %d)\n", getpid());

			if (fcntl(fd, F_SETLKW, &first_lock) == -1)
				perror("C");

			printf("C : Lock succeeded (proc %d)\n", getpid());
			exit(0);
		default:
			printf("parent sleeping\n");
			sleep(10);

			if(fcntl(fd, F_SETLKW, &second_lock) == -1)
				perror("D");

			printf("D : Lock succeeded (proc %d)\n", getpid());

	}
}
