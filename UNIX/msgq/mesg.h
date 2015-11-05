/*
 * Definition of "our" message.
 *
 * You may have to change the 4096 to a smaller value, if message queues
 * on your system were configured with "msgmax" less than 4096
 */

#define MAXMESGDATA 4096
#define MESGHDRSIZE (sizeof(Mesg) - MAXMESGDATA)

typedef struct {
	int mesg_len;
	long mesg_type;
	char mesg_data[MAXMESGDATA];
} Mesg;

int mesg_recv(int id, Mesg *mesgptr) {
	int n;
	/*
	 * Read the first message on the queue of the specified type.
	 */
	n = msgrcv(id, (char *) &(mesgptr->mesg_type), MAXMESGDATA, mesgptr->mesg_type, 0);
	if ((mesgptr->mesg_len = n) < 0)
		perror("msgrcv error");
	return (n);
}

void mesg_send(int id, Mesg *mesgptr) {
	/*
	 * Send the message - the type followed by the optional data.
	 */
	if (msgsnd(id, (char *) &(mesgptr->mesg_type), mesgptr->mesg_len, 0) != 0)
		perror("msgsnd error");
}

