#Perf

리눅스 커널에 포함된 user-level의 도구. 시스템 성능측정을 위해 다양한 기법을 제공한다. PMU(Performance Monitoring Unit)의 도움을 받아서 동작한다. 커널의 ABI와 밀접한 연관이 있기때문에 사용자 레벨의 프로그램이지만 커널소스에 포함된다. 

```
imb@ubuntu:~/Desktop$ perf

test는 unit test를 위한 명령이며 -v 옵션을 통해 더 자세한 실행결과를 얻을 수 있다. list를 매개변수로 전달하면 가능한 모든 테스트의 목록을 출력한다.

```
imb@ubuntu:~/Desktop$ perf test list
```

##2. perf stat
명령어를 실행하고 퍼포먼스 측정 정보들을 얻어온다.
-e 옵션으로 이벤트를 선택하여 정보를 얻을 수 있다. 이벤트 목록을 보기 위해서는 perf list 명령어를 사용하면된다.

```
imb@ubuntu:~/Desktop$ sudo perf list



관련 웹페이지  
https://perf.wiki.kernel.org/index.php/Tutorial