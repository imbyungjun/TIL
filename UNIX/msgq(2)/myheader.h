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
#define KEY 12345L

typedef struct {
    long    msg_to;
    long    msg_fm;
    char    buffer[BUFSIZ];
} MESSAGE;
 
int mid;
key_t key;
struct msqid_ds buf;
MESSAGE msg;
 
