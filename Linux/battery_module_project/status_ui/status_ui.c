#include "../battery/chardev.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> 		/* open */
#include <unistd.h> 	/* exit */
#include <sys/ioctl.h> 	/* ioctl */

#define MAX_SIZE 1024
#define INTERVAL 1
#define STDOUT 1

void print_battery(int status) {
	int i;
	char battery_bar[MAX_SIZE] = "";
	char buffer[MAX_SIZE];

	/* Get battery bar */
	for (i = 0; i < status/5; i++) 
		strcat(battery_bar, "#");

	/* Print battery status */
	sprintf(buffer, "Battery status : [%s] %d %%", battery_bar, status);
	write(STDOUT, buffer, strlen(buffer));

	/* Clear line */
	for (i = 0; i < 80 - strlen(buffer); i++) 
		write(STDOUT, " ", 2);
	write(STDOUT, "\r", 2);
}

char* ioctl_get_msg(int file_desc) {
    int ret_val;
    char message[MAX_SIZE];
  
    ret_val = ioctl(file_desc, IOCTL_GET_MSG, message);
    if (ret_val < 0) {
        printf("ioctl_get_msg failed:%d\n", ret_val);
        exit(-1); 
    }

	print_battery(strtol(message, 0, 10));
}

int main() {
	int fd, status;

	printf("opening device %s\n", DEVICE_FILE_NAME);

	while (1) {
		fd = open(DEVICE_FILE_NAME, O_RDWR);

		if (fd < 0) {
			perror("file open faild");
			exit(1);
		}

		ioctl_get_msg(fd);

		close(fd);
	}
}

