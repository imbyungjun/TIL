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

#3. Trace

#4. Strace












