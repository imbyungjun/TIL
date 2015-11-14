#include "myheader.h"

int main(int argc, char** argv) {
 
    //Creating a message queue
    if((mid = msgget(KEY, IPC_CREAT | 0644))<0){
        printf("Error Creating Message Queue\n");
        exit(-1);
    }
 
    //Display Message Queue and Server ID
    printf("Message Queue ID: %d\n", mid);
    printf("Server ID: %ld\n", (long)getpid());

	while (1) { 
    	// Receiving message from client, throws and error if input is invalid
	    if(msgrcv(mid, &msg, sizeof(msg.buffer), SERVER, 0)<0){
        	perror("Server : msgrcv");
			exit(-1);
		}
 
		//Server displays received message
		//printf("From client(%s) : ", msg.msg_fm);
		//printf("%s\n", msg.buffer);
 
		//Aquiring Cliend PID to message return
		long client = msg.msg_fm;
		msg.msg_to = client;
		msg.msg_fm = (long)getpid();

		// Open and read file
		FILE *fin;
	   	if ((fin = fopen(msg.buffer, "r")) == NULL)	{
			strcpy(msg.buffer, "Invalid file name");
			if (msgsnd(mid, (struct MESSAGE*)&msg, sizeof(msg.buffer), 0) == -1) {
				perror("Server : msgsnd");
				exit(1);
			}
			break;
		}
		read(fileno(fin), msg.buffer, BUFSIZ);
	 
		// Prepare return message
		msg.msg_fm = SERVER;
		msg.msg_to = client;

		// Remove last newline
		msg.buffer[strlen(msg.buffer)-1] = '\0';
 
    	//send converting message back to client, throws and error if input is invalid
    	if(msgsnd(mid, (struct MESSAGE*)&msg, sizeof(msg.buffer), 0)==-1){
        	perror("Server : msgsnd");
        	exit(-1);
		}
	
	}
	// Wait for client's exit
	int status;
	wait(&status);

	// Removing message queue	
	msgctl(mid, IPC_RMID, (struct msqid_ds *) 0);

    //server exits
    return (EXIT_SUCCESS);
}
