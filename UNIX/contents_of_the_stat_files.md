#Contents of the stat files


  Field     |  Content  
------------|--------  
 pid        | Process ID
 tcomm      | Filename of the executable
 state      | State (R is running, S is sleeping, D is sleeping in an uninterruptible wait, Z is zombi, T is traced or stopped)
ppid        | Pid of the parent process
pgrp        | Process group id of the process
sid         | Session ID
tty_nr      | tty the process uses
tty_pgrp    | pgrp of the tty
flags       | task flags
min_flt     | number of minor faults
cmin_flt    | number of minor faults with child's
maj_flt     | number of major faults
cmaj_flt    | number of major faults with child's
utime       | CPU time spent in user code (*clock ticks*)
stime       | CPU time spent in kernel code (*clock ticks*)
cutime      | Waited-for children's CPU time spent in user code (*clock ticks*)
cstime      | Waited-for children's CPU time spent in kernel code (*clock ticks*)
priority    | priority level
nice        | nice level
num_threads | number of threads
it_real_value | (obsolete, always 0)
start_time  | time the process started after system boot
vsize       | virtual memory size
rss         | resident set memory size
rsslim      | current limit in bytes on the rss
start_code  | address above which program text can run
end_code    | address below which program text can run
start_stack | address of the start of the main process stack
esp         | current value of ESP
eip         | current value of EIP
pending     | bitmap of pending signals
blocked     | bitmap of blocked signals
sigign      | bitmap of ignored signals
sigcatch    | bitmap of caught signals
0           | (place holder)
0           | (place holder)
0           | (place holder)
exit_signal | signal to send to parent thread on exit
task_cpu    | which CPU the task is scheduled on
rt_priority | realtime priority
policy      | scheduling policy 
blkio_ticks | time spent waiting for block IO
gtime       | guest time of the task in jiffies
cgtime      | guest time of the task children in jiffies
start_data  | address above which program data+bss is placed
end_data    | address below which program data+bss is placed
start_brk   | address above which program heap can be expanded with brk()
arg_start   | address above which program command line is placed
arg_end     | address below which program command line is placed
env_start   | address above which program environment is placed
env_end     | address below which program environment is placed
exit_code   |the thread's exit_code in the form reported by the waitpid system call