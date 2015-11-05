#include <stdio.h>
#include "mesg.h"
#include "msgq.h"

Mesg mesg;

void client(int id) {
	int n;
	/*
	 * Read the filename from standard input, write it as
	 * a message tot he IPC descriptor.
	 */
	write(1, "Enter file name : ", 20);
	if (fgets(mesg.mesg_data, MAXMESGDATA, stdin) == NULL)
		err_sys("filename read error");

	n = strlen(mesg.mesg_data);
	if (mesg.mesg_data[n-1] == '\n')	/* ignore newline */
		n--;
	mesg.mesg_data[n] = '\0';
	mesg.mesg_len = n;
	mesg.mesg_type = 1;
	mesg_send(id, &mesg);
	/*
	 * Receive the message from the IPC descriptor and write
	 * the data to the standard output.
	 */
	mesg.mesg_type = 2;		/* receive messages of this type */
	while ((n = mesg_recv(id, &mesg)) > 0)
		if (write(1, mesg.mesg_data, n) != n)
			err_sys("data write error");
	if (n < 0)
		err_sys("data read error");
}

int main() {
	int id;

	/*
	 * Open the message queues. The server must have 
	 * already created it
	 */
	if ((id = msgget(MKEY1, 0)) < 0)
		err_sys("clent: can't msgget message queue 1");

	client(id);

	/*
	 * Now we can delete the message queues.
	 */
	if (msgctl(id, IPC_RMID, (struct msqid_ds *) 0) < 0)
		err_sys("client: can't RMID message queue 1");
	exit(0);
}
