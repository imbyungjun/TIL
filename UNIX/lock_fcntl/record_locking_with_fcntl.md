#Record locking with fcntl()
In IPC environment, many processes can access to a file at once.  
In this situation, many processes share file pointer that pointing current location in the file. If process call fuctions that using file pointer(lseek, read, write ...) , ***race condition*** would be occured.  
<big>We can solve it by record locking.</big>

```
#include <fcntl.h>
int fcntl(int fd, int cmd, struct flock *ldata);
		returns: 0 if OK, -1 on error
```
<big>**cmd**</big>

```
F_GETLK : Get information from lock struct ldata
F_SETLK : Set lock. If can not, return immediately. Or remove lock.
F_SETLKW : Set lokc, If can not, wait for unlock (sleep)
```
<big>**ldata struct**</big>

```
struct ldata {
	short l_type;
	short l_whence;
	off_t l_start;
	off_t l_len;
	off_t l_pid;
}
```
```
l_type
	F_RDLCK : Lock for read
	F_WRLCK : Lock for write
	F_UNLCK : Lock for unlock
```
```
l_whence
	SEEK_SET : Front of file
	SEEK_CUR : Current file pointer offset
	SEEK_END : End of file
```
###Unlock
```
my_lock.l_type = F_UNLCK;

if (fcntl(fd, F_SETLK, &my_lock) == -1)
	perror("unlock");
```
###Test lock
```
if (fcntl(fd, F_SETLK, &my_lock) == -1) {
	if (errno == EACCES || errno == EAGAIN) {
		fcntl(fd, F_GETLK, &my_lock);
		fprintf(stderr, "record locked by %d\n", my_lock.l_pid);
	}
	else
		perror("unexpected lock error");
}
```