# Docker Container Logging

Log를 남기는일은 장애상황 발생시 디버깅에 큰 도움이 된다. 애플리케이션 레벨에서 로깅 설정을 하는것이 보통이지만 도커를 이용할 경우 컨테이너의 표준 출력(STDOUT)과 에러(STDERR)를 이용하여 로깅할 수 있는 기능을 제공한다.  

기본 로깅 드라이버는 로그 정보를 JSON 형식으로 저장한다. 도커 데몬 실행 옵션으로 `--log-driver`옵션을 사용하여 syslog, journald, fluentd, awslogs 등의 로깅 드라이버를 설정할 수 있다.
```
$ docker logs [container_name]
```

#### options
* --tail n : 마지막 n줄만을 출력
* --since time : 특정 시간 이후의 로그를 출력 (단위는 유닉스 시간)
* -t : timestamp를 함께 출력
* -f : 실시간으로 출력 (스트림)

## Logging Drivers

### syslog

### fluentd

### awslogs
