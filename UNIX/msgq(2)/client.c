#include "myheader.h"

int main() {
 
    //Aquiring Message Queue ID
    mid = msgget(KEY, 0);
 
    //Display Message Queue and Client ID
    printf("Message Queue ID: %d\n", mid);
    printf("Client ID: %ld\n", (long)getpid());

	while(1) {
    	//Copy input characters into msg.buffer, loops breaks when EOF is reached
		printf("Enter file name : ");
		scanf("%s", &msg.buffer);	
	
		//Getting Client PID and preparing message to message queue
		msg.msg_to = SERVER;
		msg.msg_fm = (long)getpid();
 
		//Send message to Message Queue for Server
		if(msgsnd(mid, &msg, sizeof(msg.buffer), 0)==-1){
			perror("Client : msgsnd");
			exit(-1);
		}

		//Client waits for response from Server, throws an error if invalid input
		if(msgrcv(mid, &msg, sizeof(msg), msg.msg_fm, 0)<0){
			perror("Client : msgrcv");
			exit(-1);
		}
	
		// Print received message
		printf("Client : %s\n", msg.buffer);
	} 
 
    //Client exits
    return (EXIT_SUCCESS);
}
