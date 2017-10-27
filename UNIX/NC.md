# NC
NC(NetCat) 유틸리티는 TCP 혹은 UDP 연결을 위한 거의 모든 것들을 수행할 수 있다. TCP 연결을 열 수 있고, UDP packet을 보낼 수 있다. 또한 TCP 와 UDP ports를 통해 들어오는 packets를 감지할 수 있고, port scanning을 수행할 수 있다. telnet과 다른점은 에러를 STDERR로 출력하고 사용법이 더 간단하다.

Common uses include:

* simple TCP proxies
* shell-script based HTTP clients and servers
* network daemon testing
* a SOCKS or HTTP ProxyCommand for ssh
* and much, much more

## Client/Server Model
**nc**를 이용하면 간단한 client/server를 구성하는일을 매우 쉽게 수행할 수 있다.

#### 1) nc를 이용하여 특정 포트 Listen
```
$ nc -l 9999
```

#### 2) nc를 이용하여 특정 포트로 접속하기
```
$ nc 127.0.0.1 9999
```

**위와 같은 수행에서 Protocol을 명시하지 않을 경우 기본적으로 TCP를 이용하게 된다.**

## Data Transfer
Client/Server 예제를 확장하여 기본적인 데이터 전송을 구현할 수 있다.

#### 1) 특정 포트 Listen & 결과를 저장
```
$ nc -l 9999 > file.out
```
#### 2) 특정 포트에 파일의 내용을 전달
```
$ nc 127.0.0.1 9999 < file.in
```

## Request to Server
가끔은 직접 서버에 요청을 전달해서 결과를 확인하는 일이 필요하다. 
```
$ echo -n "GET / HTTP/1.0\r\n\r\n" | nc www.example.com 80
```

SMTP 서버에 email을 전송하는 일도 수행할 수 있다.
```
$ nc localhost 25 << EOF
> HELO host.example.com
> MAIL FROM: <user@host.example.com>
> RCPT TO: <user2@host.example.com>
> DATA
> Body of email.
> .
> QUIT
> EOF
```

## Port Scanning
-z 옵션으로 열린 포트에 바로 접속하는것이 아닌, 열린 포트들을 리포트하도록 할 수 있다.
```
$ nc -z localhost 20-30
Connection to localhost port 22 [tcp/ssh] succeeded!
```

## Examples
Open a TCP connection to port 42 of host.example.com, using port 31337 as the source port, with a timeout of 5 seconds:
```
$ nc -p 31337 -w 5 host.example.com 42
```

Open a UDP connection to port 53 of host.example.com:
```
$ nc -u host.example.com 53
```

Open a TCP connection to port 42 of host.example.com using 10.1.2.3 as the IP for the local end of the connection:
```
$ nc -s 10.1.2.3 host.example.com 42
```

Create and listen on a Unix Domain Socket:
```
$ nc -lU /var/tmp/dsocket
```

Connect to port 42 of host.example.com via an HTTP proxy at 10.2.3.4, port 8080. This example could also be used by ssh(1); see the ProxyCommand directive in ssh_config(5) for more information.
```
$ nc -x10.2.3.4:8080 -Xconnect host.example.com 42
```

## Reference
http://www.tutorialspoint.com/unix_commands/nc.htm

