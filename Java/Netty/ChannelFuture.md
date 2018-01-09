# ChannelFuture

## Package
```
public interface ChannelFuture
extends Future<Void>
```
## Description
비동기 Channel I/O 작업의 결과이다.

Netty에서의 모든 I/O 연산은 비동기방식이다. 다시말해서, 어떤 I/O 연산이라도 요청 I/O 연산이 완료되었다는 보장 없이 호출 즉시 리턴한다. 대신에 ChannelFuture 인스턴스를 리턴함으로 써 I/O 연산의 결과나 완료 상태 정보를 제공한다.

ChannelFuture는 미완료 이거나 완료이다. I/O 연산이 시작될 때, 새로운 Future 객체가 생성된다. 새로운 Future는 초기에는 미완료 상태이다. 이것은 성공한것도, 실패한것도, 또는 취소된것도 아니다. 왜나하면 I/O 연산이 아직 종료되지 않았기 때문이다. 만약 I/O연산이 성공적으로, 실패로, 또는 취소됨으로써 종료되면 해당 Future는 좀 더 자세한 정보와 함께 완료되었다고 표시된다. 실패 또는 취소되어도 완료는 된다는점을 인지하자.
```
                                      +---------------------------+
                                      | Completed successfully    |
                                      +---------------------------+
                                 +---->      isDone() = true      |
 +--------------------------+    |    |   isSuccess() = true      |
 |        Uncompleted       |    |    +===========================+
 +--------------------------+    |    | Completed with failure    |
 |      isDone() = false    |    |    +---------------------------+
 |   isSuccess() = false    |----+---->      isDone() = true      |
 | isCancelled() = false    |    |    |       cause() = non-null  |
 |       cause() = null     |    |    +===========================+
 +--------------------------+    |    | Completed by cancellation |
                                 |    +---------------------------+
                                 +---->      isDone() = true      |
                                      | isCancelled() = true      |
                                      +---------------------------+
```

I/O 연산이 완료되었는지 확인할 수 있는 메소드, I/O 연산이 완료될 때까지 기다리는 메소드, 그리고 I/O 연산의 결과를 얻어오는 메소드 등 다양한 메소드가 제공된다. 또한 ChannelFutureListener를 추가할 수 있도록 하여 I/O 연산의 완료를 알림 받을 수 있다.

## API Reference
https://netty.io/4.0/api/io/netty/channel/ChannelFuture.html
