#PS output meaning
```
$ ps aux
USER       PID  %CPU %MEM  VSZ RSS     TTY   STAT START   TIME COMMAND
timothy  29217  0.0  0.0 11916 4560 pts/21   S+   08:15   0:00 pine  
root     29505  0.0  0.0 38196 2728 ?        Ss   Mar07   0:00 sshd: can [priv]   
can      29529  0.0  0.0 38332 1904 ?        S    Mar07   0:00 sshd: can@notty 
```
- USER : Owner of the process
- PID : Process ID
- %CPU : CPU time used divided by the time the process has been running.
- %MEM : Ratio of the process's resident set size to the physical memory
- VSZ : Virtual memory usage of entire process
- RSS : Resident set size (???)
- TTY : Controlling terminal
- STAT : Current state of the process
- START : Starting time or date of the process
- TIME : Cumulative CPU time
- COMMAND : Command with all its arguments

#/proc
- USER : stat, /etc/passwd
- PID : /proc/PID
- %CPU : [Link](http://stackoverflow.com/questions/16726779/how-do-i-get-the-total-cpu-usage-of-an-application-from-proc-pid-stat)
- %MEM : 