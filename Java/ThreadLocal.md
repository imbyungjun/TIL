# ThreadLocal
**ThreadLocal**은 해당 스레드에 유일한 변수를 설정할 수 있도록 돕는 클래스이다. ThreadLocal은 스레드 영역에 변수를 생성하여 각 스레드마다 자신만의 변수를 갖도록 한다. ThreadLocal로 변수를 보호하면 Thread-safe하게 만들 수 있지만, 서로 다른 스레드의 데이터에 접근할 수 없다는 한계점을 갖는다. 
> This class provides thread-local variables. These variables differ from their normal counterparts in that each thread that accesses one (via its get or set method) has its own, independently initialized copy of the variable. ThreadLocal instances are typically private static fields in classes that wish to associate state with a thread (e.g., a user ID or Transaction ID).

## 사용시 주의사항
스레드 풀 환경에서 ThreadLocal을 사용하는 경우 ThreadLocal 변수에 보관된 데이터의 사용이 끝나면 반드시 해당 데이터를 삭제해 주어야 한다. 그렇지 않을 경우 재사용되는 쓰레드가 올바르지 않은 데이터를 참조할 수 있다.

## Example
```java
import java.util.concurrent.atomic.AtomicInteger;

public class ThreadId {
    // Atomic integer containing the next thread ID to be assigned
    private static final AtomicInteger nextId = new AtomicInteger(0);

    // Thread local variable containing each thread's ID
    private static final ThreadLocal<Integer> threadId =
    new ThreadLocal<Integer>() {
       @Override protected Integer initialValue() {
           return nextId.getAndIncrement();
       }
   };

   // Returns the current thread's unique ID, assigning it if necessary
   public static int get() {
       return threadId.get();
   }
}
```

## Reference
http://javacan.tistory.com/entry/ThreadLocalUsage
