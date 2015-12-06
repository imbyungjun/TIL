#include "mesg.h"

/*
 * Receive a message from a System V message queue.
 * The caller must fill in the mesg_type field with the desired type.
 * Return the number of bytes in the data portion of the message.
 * A O-length data message implies end-of-file.
 */

int mesg_recv(int id, Mesg *mesgptr) {
	int n;

	/*
	 * Read the first message on the queue of the specified type.
	 */
	n = msgrcv(id, (char *) &(mesgptr->mesg_type), MAXMESGDATA, mesgptr->mesg_type, 0);
	if ((mesgptr->mesg_len = n) < 0)
		err_sys("msgrcv error");
	return(n);
}
