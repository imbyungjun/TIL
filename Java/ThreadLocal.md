# ThreadLocal
ThreadLocal이란 해당 스레드에 유일한 변수를 설정할 수 있도록 돕는 클래스이다. 스레드 영역에 변수를 생성하여 각 스레드마다 자신만의 변수를 갖는다.
> This class provides thread-local variables. These variables differ from their normal counterparts in that each thread that accesses one (via its get or set method) has its own, independently initialized copy of the variable. ThreadLocal instances are typically private static fields in classes that wish to associate state with a thread (e.g., a user ID or Transaction ID).

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
