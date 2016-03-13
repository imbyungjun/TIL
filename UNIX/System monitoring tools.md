#System Monitoring tools

#1. Sar
<big>
By using **sar**, you can monitor performance of various system information.  
**Sar** is part of the sysstat package, so you can install **sar** by installing sysstat. (sysstat also includes sadf, mpstat, iostat, tapestat, pidstat, cifsiostat and sa tools.)  
sar는 시스템의 활동로그를 수집하여 시스템의 부하량을 예측하고 사용자가 대처할 수 있도록 하는 명령어.
###Options
\- A : 모든 관련된 정보를 출력.  
\- b : I/O와 transfer의 통계를 백분율로 출력.  
\- B : 페이징 통계를 출력한다.  
\- c : 새롭게 만들어져 활동하고있는 프로세스를 출력한다.  
\- e : 리포트의 종료시간을 설정한다. 시간표시형식은 hh:mm:dd 24시간 format을 사용해야하며 기본 종료 시간은 18:00이다.  
\- r : 메모리와 스왑 공간의 이용 통계를 출력한다.  

---
\- u : 모든 CPU의 현재사용정보를 출력한다.

usage:

```
$ sar -u 1 3        # "1 3" reports for every 1 seconds for 3 times.
Linux 4.1.18-v7+ (raspberrypi) 	13/03/16 	_armv7l_	(4 CPU)

08:20:17        CPU     %user     %nice   %system   %iowait    %steal     %idle
08:20:18        all      0.00      0.00      0.25      0.00      0.00     99.75
08:20:19        all      0.00      0.00      0.25      0.00      0.00     99.75
08:20:20        all      0.00      0.00      0.25      0.00      0.00     99.75
Average:        all      0.00      0.00      0.25      0.00      0.00     99.75
```

\- r : This option reports memory statistics. Memory free and used.

```
$ sar -r 1 3
Linux 4.1.18-v7+ (raspberrypi) 	13/03/16 	_armv7l_	(4 CPU)

17:25:58    kbmemfree kbmemused  %memused kbbuffers  kbcached  kbcommit   %commit  kbactive   kbinact   kbdirty
17:25:59       607064    340996     35.97     46152    205356    594508     56.60    200864     95352         8
17:26:00       607048    341012     35.97     46152    205356    594508     56.60    200864     95352         8
17:26:01       607080    340980     35.97     46152    205356    594508     56.60    200872     95352         8
Average:       607064    340996     35.97     46152    205356    594508     56.60    200867     95352         8
```

\- S : Reports swap statistics. Swap space used.

```
$ sar -S 1 3
Linux 4.1.18-v7+ (raspberrypi) 	13/03/16 	_armv7l_	(4 CPU)

17:27:08    kbswpfree kbswpused  %swpused  kbswpcad   %swpcad
17:27:09       102396         0      0.00         0      0.00
17:27:10       102396         0      0.00         0      0.00
17:27:11       102396         0      0.00         0      0.00
Average:       102396         0      0.00         0      0.00
```

\- b : I/O statistics. Overall I/O activities.

```
$ sar -b 1 3
Linux 4.1.18-v7+ (raspberrypi) 	13/03/16 	_armv7l_	(4 CPU)

17:33:29          tps      rtps      wtps   bread/s   bwrtn/s
17:33:30       317.00      0.00    317.00      0.00   2536.00
17:33:31       190.00      0.00    190.00      0.00   1520.00
17:33:32       493.00      0.00    493.00      0.00   3944.00
Average:       333.33      0.00    333.33      0.00   2666.67
```

\- w : Reports total number of processes created per second, and total number of context switches per second.

```
$ sar -w 1 3
Linux 4.1.18-v7+ (raspberrypi) 	13/03/16 	_armv7l_	(4 CPU)

17:35:44       proc/s   cswch/s
17:35:45         0.00    164.00
17:35:46         0.00    199.00
17:35:47         0.00    153.00
Average:         0.00    172.00
```

#2. Tcpdump
**Tcpdump** prints all of packet header go through the network interfaces that satisfy a given condition.

###Options
\- i <interface_name> : 해당 인터페이스를 이용하는 TCP 패킷에 대한 정보를 보여줌.   
\- w <file_name> : 결과를 파일로 저장한다. bin형식으로 저장된다.  
\- r <file_name> : 저장한 파일을 읽어서 표준출력으로 출력한다.  
tcp : TCP를 이용하는 패캣을 탐지한다  
port <port#> : 해당 포트넘버를 사용하는 패킷을 탐지한다.  
src / dst <IPv4_addr> : source IP 또는 destination IP가 주어진 IP주소와 일치하는 패킷을 탐지한다.  
첨부 : and / or / not 을 조합하여 사용할 수 있다.

#3. Traceroute
Print route packets trace to network host.  
**Traceroute** uses TTL field in IP header. 
TTL 필드를 이용해서 hop수를 알아내고 TTL값이 줄어들어서 폐기된 패킷을 받은 라우터는 ICMP error message를 source에 전달하게 된다.
이를 통하여 source에서 destination까지의 모든 라우터의 IP주소를 알아내게 된다.  

###Options
\- n : Print mapping of IP addresses without host name.  
\- w <second>: Set response wait time
\- 


###Result
```
$ traceroute google.com
traceroute to google.com (216.58.199.14), 64 hops max, 52 byte packets
 1  192.168.219.1 (192.168.219.1)  6.350 ms  1.746 ms  1.953 ms
 2  115.140.34.129 (115.140.34.129)  10.120 ms  15.184 ms  7.694 ms
 3  10.240.205.153 (10.240.205.153)  131.229 ms  5.655 ms  6.090 ms
...
```

#4. Strace
**Strace** monitors system calls and signals of a specific program. It would be helpful when you'd like to debug the execution of a program that you don't have source code of it.

###Options
<any_command> : strace will trace execution of any executable commands.  
\- e <system_call> <command> : 해당 명령어에대하여 명시한 시스템콜에 대해서만 출력한다.  
\- e trace=[system_call] <command> : 해당 명령어에 대하여 명시한 다수의 시스템콜에 대해서 출력.  
```
$ strace -e trace=open,read ls
```  
\- o <file_name> : Save trace execution output to a file.  
\- p <PID> : Execute strace on a current running program using process id.  
\- t : Print timestamp for each strace output.  
\- r : Print execution time for system calls  
\- c : Generate statistics report of system calls