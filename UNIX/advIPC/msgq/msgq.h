#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>

#include <sys/errno.h>
extern int errno;

#define MKEY1 12345L

#define PERMS 0666

void err_sys(const char *x) { perror(x); }
