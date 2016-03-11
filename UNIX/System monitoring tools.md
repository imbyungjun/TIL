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