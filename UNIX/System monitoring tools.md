#System Monitoring tools
---
#1. Sar
<big>By using **sar**, you can monitor performance of various system information.  
**Sar** is part of the sysstat package, so you can install **sar** by installing sysstat. (sysstat also includes sadf, mpstat, iostat, tapestat, pidstat, cifsiostat and sa tools.)  
sar는 시스템의 활동로그를 수집하여 시스템의 부하량을 예측하고 사용자가 대처할 수 있도록 하는 명령어.
###Options
\- A : 모든 관련된 정보를 출력.  
\- b : I/O와 transfer의 통계를 백분율로 출력.  
\- B : 페이징 통계를 출력한다.  
\- c : 새롭게 만들어져 활동하고있는 프로세스를 출력한다.  
\- e : 리포트의 종료시간을 설정한다. 시간표시형식은 hh:mm:dd 24시간 format을 사용해야하며 기본 종료 시간은 18:00이다.
\- r : 메모리와 스왑 공간의 이용 통계를 출력한다.
</big>


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
\- w <sec>: Set response wait time
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