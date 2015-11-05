#include <stdio.h>
#include "mesg.h"
#include "msgq.h"
Mesg mesg;

void server(int id) {
	int n, filefd;

	/*
	 * Read the filename message from the IPC descriptor
	 */
	mesg.mesg_type = 1;
	if ((n = mesg_recv(id, &mesg)) <= 0)
		err_sys("serevr: filename read error");
	mesg.mesg_data[n] = '\0';


	mesg.mesg_type = 2;
	if ((filefd = open(mesg.mesg_data, 0)) < 0) {
		write(1, "file open error", 20);
		/*
		 * Error
		 */
		strcpy(mesg.mesg_data,"file open fail\n");
		mesg.mesg_len = strlen(mesg.mesg_data);
		mesg_send(id, &mesg);
	} else {
		/*
		 * Raed the data from the file and send a message to
		 * the IPC descirptor.
		 */
		while ((n = read(filefd, mesg.mesg_data, MAXMESGDATA)) > 0) {
			mesg.mesg_len = n;
			mesg_send(id, &mesg);
		}
		close(filefd);
		if (n < 0)
			err_sys("server: read error");
	}

	/*
	 * Send a message with a length of 0 to signify the end.
	 */
	mesg.mesg_len = 0;
	mesg_send(id, &mesg);
}

int main() {
	int id;
	Mesg mesg;

	if ((id = msgget(MKEY1, PERMS | IPC_CREAT)) < 0)
		err_sys("server: can't get message queue 1");

	server(id);

	exit(0);
}
