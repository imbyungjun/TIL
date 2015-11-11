#MessageQ
-
Message queue is one of methods for advanced InterProcess Communications.  
Each message has a type. So we can read messages with a specific type.

#System call
-
<big>1 ) msgget</big>   
Access to existing message queue or make new message queue.

	#include <sys/types.h>
	#include <sys/ipc.h>
	#include <sys/msg.h>
	
	int msgget(key_t key, int msgflag);

*msgflags  

	MSG_R  			Read by owenr
	MSG_W  			Write by owner
	MSG_R >> 3  		Read by group
	MSG_W >> 3  		Write by group		
	MSG_R >> 6  		Read by world
	MSG_W >> 6  		Write by world
	IPC_CREAT  
	IPC_EXCL
		

<big>2 ) msgsnd</big>  
Push a message to message queue

	#include <sys/types.h>
	#include <sys/ipc.h>
	#include <sys/msg.h>
	
	int msgsnd(int msqid, struct msgbuf *ptr, int length, int flag);
	
	- ptr : struct msgbuf {
			long mtype;		/* message type, must be > 0 */
			char mtext[1];	/* message data */
			};
	- length : length of message(byte)
	- flag : IPC_NOWAIT or 0

*IPC_NOWAIT - If queue is full, return exactly.

<big>3 ) msgrcv</big>  
Read message from message queue

	#include <sys/types.h>
	#include <sys/ipc.h>
	#include <sys/msg.h>
	
	int msgrcv(int msqid, struct msgbuf *ptr, int length, long msgtype, int flag);
	
	- ptr : struct msgbuf
	- length : size of data
	- msgtype : specify type
	- flag : MSG_NOERROR or 0

*msgtype = 0, read first message in queue.  
*msgtype > 0, read message that type == (msgtype)  
*msgtype < 0, read message that type <= abs(msgtype)

*MSG_NOERROR - If data's size is bigger than length, drop extra bytes.

<big>4 ) msgctl</big>  
Provide controls of message queue.
	
	#include <sys/types.h>
	#include <sys/ipc.h>
	#include <sys/msg.h>
	
	int msgctl(int msqid, int cmd, struct msqid_ds *buff);


*cmd  
IPC\_STAT : get status  
IPC\_SET : set status  
IPC\_RMID : remove message queue

-
#Implement Client-Server using message queue

-
Example Code )

	#include ...
	
	if (msgsnd(msqid, &msg, sizeof(msg.buffer), 0) == -1) {
		perror("msgsnd");
		exit(-1);
	}

	if (msgrcv(msqid, &msg, sizeof(msg), msg.type, 0) < 0) {
		perror("msgrcv");
		exit(-1);
	}


