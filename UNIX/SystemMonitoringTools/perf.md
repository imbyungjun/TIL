#Perf

리눅스 커널에 포함된 user-level의 도구. 시스템 성능측정을 위해 다양한 기법을 제공한다. PMU(Performance Monitoring Unit)의 도움을 받아서 동작한다. 커널의 ABI와 밀접한 연관이 있기때문에 사용자 레벨의 프로그램이지만 커널소스에 포함된다. 

```
imb@ubuntu:~/Desktop$ perf usage: perf [--version] [--help] COMMAND [ARGS] The most commonly used perf commands are:   annotate        Read perf.data (created by perf record) and display annotated code   archive         Create archive with object files with build-ids found in perf.data file   bench           General framework for benchmark suites   buildid-cache   Manage build-id cache.   buildid-list    List the buildids in a perf.data file   diff            Read perf.data files and display the differential profile   evlist          List the event names in a perf.data file   inject          Filter to augment the events stream with additional information   kmem            Tool to trace/measure kernel memory(slab) properties   kvm             Tool to trace/measure kvm guest os   list            List all symbolic event types   lock            Analyze lock events   mem             Profile memory accesses   record          Run a command and record its profile into perf.data   report          Read perf.data (created by perf record) and display the profile   sched           Tool to trace/measure scheduler properties (latencies)   script          Read perf.data (created by perf record) and display trace output   stat            Run a command and gather performance counter statistics   test            Runs sanity tests.   timechart       Tool to visualize total system behavior during a workload   top             System profiling tool.   trace           strace inspired tool   probe           Define new dynamic tracepoints See 'perf help COMMAND' for more information on a specific command.```
##1. perf test
test는 unit test를 위한 명령이며 -v 옵션을 통해 더 자세한 실행결과를 얻을 수 있다. list를 매개변수로 전달하면 가능한 모든 테스트의 목록을 출력한다.

```
imb@ubuntu:~/Desktop$ perf test list 1: vmlinux symtab matches kallsyms 2: detect open syscall event 3: detect open syscall event on all cpus 4: read samples using the mmap interface 5: parse events tests 6: x86 rdpmc test 7: Validate PERF_RECORD_* events & perf_sample fields 8: Test perf pmu format parsing 9: Test dso data interface10: roundtrip evsel->name check11: Check parsing of sched tracepoints fields12: Generate and check syscalls:sys_enter_open event fields13: struct perf_event_attr setup14: Test matching and linking multiple hists15: Try 'use perf' in python, checking link problems16: Test breakpoint overflow signal handler17: Test breakpoint overflow sampling18: Test number of exit event of a simple workload19: Test software clock events have valid period values20: Test converting perf time to TSC21: Test object code reading22: Test sample parsing23: Test using a dummy software event to keep tracking24: Test parsing with no sample_id_all bit set
```

##2. perf stat
명령어를 실행하고 퍼포먼스 측정 정보들을 얻어온다.
-e 옵션으로 이벤트를 선택하여 정보를 얻을 수 있다. 이벤트 목록을 보기 위해서는 perf list 명령어를 사용하면된다.

```
imb@ubuntu:~/Desktop$ sudo perf list[sudo] password for imb: List of pre-defined events (to be used in -e):  cpu-clock                                          [Software event]  task-clock                                         [Software event]  page-faults OR faults                              [Software event]  context-switches OR cs                             [Software event]  cpu-migrations OR migrations                       [Software event]  minor-faults                                       [Software event]  major-faults                                       [Software event]  alignment-faults                                   [Software event]  emulation-faults                                   [Software event]  dummy                                              [Software event]  rNNN                                               [Raw hardware event descrip  cpu/t1=v1[,t2=v2,t3 ...]/modifier                  [Raw hardware event descrip   (see 'man perf-list' on how to encode it)  mem:<addr>[:access]                                [Hardware breakpoint]  skb:kfree_skb                                      [Tracepoint event]  skb:consume_skb                                    [Tracepoint event]  skb:skb_copy_datagram_iovec                        [Tracepoint event]  net:net_dev_xmit                                   [Tracepoint event]
  ...```
매우 많은 리스트가 나온다. 필요한것을 선택적으로 찾아서 사용하도록 해야겠다.

관련 웹페이지  
https://perf.wiki.kernel.org/index.php/Tutorial
