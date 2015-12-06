#include "mesg.h"

/*
 * Send a message using the System V message queues.
 * The mesg_len, mesg_type and mesgdata fields must be filled
 * in by the caller.
 */

void mesg_send(int id, Mesg *mesgptr) {
	/*
	 * Send the message - the type followed by the optional data.
	 */

	if (msgsnd(id, (char *) &(mesgptr->mesg_type), mesgptr->mesg_len, 0) != 0)
		err_sys("msgsnd error");
}
