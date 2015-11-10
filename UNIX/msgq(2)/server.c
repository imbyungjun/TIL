#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
 
#define SERVER 1L
typedef struct {
    long    msg_to;
    long    msg_fm;
    char    buffer[BUFSIZ];
} MESSAGE;
 
int mid;
key_t key;
struct msqid_ds buf;
MESSAGE msg;
 
int main(int argc, char** argv) {
 
    //Creating a message queue
    key = ftok(".", 'z');
    if((mid = msgget(key, IPC_CREAT | 0660))<0){
        printf("Error Creating Message Queue\n");
        exit(-1);
    }
 
    //Display Message Queue and Server ID
    printf("Message Queue ID: %d\n", mid);
    printf("Server ID: %ld\n", (long)getpid());    
 
    //Receiving message from client, throws and error if input is invalid
    if(msgrcv(mid, &msg, sizeof(msg.buffer), SERVER, 0)<0){
        perror("msgrcv");
        exit(-1);
    }
 
    //Server displays received message
    printf("SERVER receives:\n");
    printf("%s\n", msg.buffer);
 
    //Aquiring Cliend PID to message return
    long client = msg.msg_fm;
 
    //convert all lowercase characters to uppercase
    int i;
    while(msg.buffer[i] != '\0'){
        msg.buffer[i] = toupper(msg.buffer[i]);
        i++;
    }
 
    //prep return message
    msg.msg_fm = SERVER;
    msg.msg_to = client;
 
    //send converting message back to client, throws and error if input is invalid
    if(msgsnd(mid, (struct MESSAGE*)&msg, sizeof(msg.buffer), 0)==-1){
        perror("msgsnd");
        exit(-1);
    }
 
    //server exits
    return (EXIT_SUCCESS);
}