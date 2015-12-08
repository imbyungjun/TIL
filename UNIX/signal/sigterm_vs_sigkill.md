#SIGTERM vs SIGKILL
SIGTERM and SIGKILL have a difference.

###SIGTERM
```
$ kill 2580
```
This command would occur SIGTERM signal.  
When process received SIGTERM, it will do these tasks.  

 \- the process may stop immediately  
 \- the process may stop after a short delay after cleaning up resources  
 \- the process may keep running indefinitely  
 
Most applications will clean up their resources an stop. An application may be configured to do something different when SIGTERM is received.

  
###SIGKILL
```
$ kill -9 2580
```
-9 means signal#9, which is called SIGKILL.  
SIGKILL can not be ignored by signal().
