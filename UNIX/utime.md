#utime
Modify inode's last access/modification time.

```
#include <sys/types.h>
#include <utime.h>

int utime(const char *filename, struct utimebuf *buf);
	return 0 if Success, -1 on Error
	
struct utimbuf {
	time_t actime;
	time_t modtime;
};
```
Change the access and modification times to each actime and modtime value of buf. If buf is NULL, the access and modification times of the file are set to the current time.

###Example

```
#include <sys/types.h>
#include <utime.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>

int main() {
	struct utimbuf ubuf;
	ubuf.actime = time((time_t *)0);
	ubuf.modtime = time((time_t *)0);
	
	utime("test_file", NULL);
	
	utime("test_file", &ubuf);
```
