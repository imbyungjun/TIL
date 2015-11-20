#Get Current Time

```
#include <time.h>
int clock_getres(clockid_t clk_id, struct timespec *res);
int clock_gettime(clockid_t clk_id, struct timepsec *tp);
int clock_settime(clockid_t clk_id, const struct timespec *tp);
	returns : 0 if success, -1 on error
```
###1. clock_getres()  
Finds the resolution of the specified clock clk_id. And stores it in the *res.

###2. clock_gettime()
Get time from specified clock clk_id.

###3. clock_settime()
Set time from specified timespec *tp.

###Clocks
- CLOCK_REALTIME  
 Realtime clock. Setting this clock may requires permission.
- CLOCK_MONOTONIC  
 Clock that cannot be set and represents monotonic time since some unspecified starting point.
- CLOCK_PROCESS_CPUTIME_ID
- CLOCK_THREAD_CPUTIME_ID 