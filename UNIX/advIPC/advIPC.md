#Advanced Inter Process Communication
* Message Queue
* Semaphore
* Shared Memory

###IPC Key
Identifier for IPC. It can convert from file to key.

```
#include <sys/ipc.h>

key_t ftok(const char *path, int id);
	return key value if OK, -1 on Error
```

###1. Message Queue
####1) msgget system call
Create new message queue, or access to message queue that already exists.

```
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int msgget(key_t key, int msgflag);
	return msqid if OK, -1 on Error
```

#####* msgflag :
 - MSG_R : Read by owner
 - MSG_W : Write by owner
 - IPC_CREAT : If msgq doesn't exist, create new msgq. Not overwrite.
 - IPC_EXCL : If it is set with IPC_CRAET, and msgq is already exist, msgget would fail and return -1
 
####2) msgsnd system call
Send a message to message queue

```
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int msgsnd(int msqid, struct msgbuf *ptr, int length, int flag);
	return 0 if OK, -1 on Error
```
#####* ptr :
```
struct msgbuf {
	long mtype;			/* message type, must be > 0 */
	char mtext[1];		/* message data */
```
#####* length : 
Length of message (byte)

#####* flag :
IPC_NOWAIT - Return immediately if message queue is full.

####3) msgrcv system call