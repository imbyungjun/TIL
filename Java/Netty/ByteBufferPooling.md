# Netty Byte Buffer Pooling

네티 바이트 버퍼는 자바 바이트 버퍼에 비해서 다양한 기능을 제공한다. 그중에서 가장 중요한 특징은 바이트 버퍼 풀이다. 자바의 바이트 버퍼는 언어 자체에서 제공하는 버퍼 풀이 없다. 그러므로 바이트 버퍼 풀을 사용하려면 객체 풀링을 제공하는 서드파티 라이브러리를 사용하거나 직접 구현해야 한다. 네티는 프레임워크에서 바이트 버퍼 풀을 제공하고 있으며 [다이렉트 버퍼와 힙 버퍼](#direct-bytebuffer-vs-heap-bytebuffer)를 모두 풀링할 수 있다.

바이트 버퍼 풀링을 사용함으로써 얻을 수 있는 가장 큰 장점은 버퍼를 빈번히 할당하고 해제할 때 일어나는 가비지 컬렉션 횟수의 감소이다. 가비지 컬렉션은 자바 가상머신의 축복이자 해악이다. 조금 이상하게 들릴지도 모르지만 사실이다. 두 문자열을 합쳐서 하나로 만드는 연산을 수행했을 때 가상머신에서는 2개의 객체가 생성되었다가 가비지 컬렉터의 대상이 된다. 이 같이 나도 모르는 사이에 다양한 객체가 임시로 생성되었다가 사라진다. 가비지 컬렉터의 대상이 되는 개체들은 가비지 컬렉션이 수행되기 전까지 메모리를 점유하고 있게 된다.

가비지 컬렉션의 기본은 유효한 참조가 없는 객체가 점유하고 있던 메모리를 가상머신으로 돌려주는 것이다. 즉 자바 가상머신이 더 이상 객체를 할당할ㄹ 메모리가 없다고 판단하면 자동으로 가비지 컬렉션을 수행한다. 이때 자바 가상머신은 힙 영역에 할당된 객체 중에서 더 이상 참조하지 않는 객체를 조사하기 위해서 모든 객체를 검사하여 유효참조가 없는 객체에 할당된 메모리를 해제한다. 이 작업에 걸리는 시간은 자바 가상머신에 할당된 메모리 크기와 객체 개수에 따라서 달라진다. 즉 가비지 컬렉션이 완료되는 데 걸리는 시간을 예측할 수 없다.

새로운 JDK가 배포되면서 다양한 가비지 컬렉션 알고리즘으로 성능을 개선하고 있다. 하지만 반대로 메모리 가격이 저렴해지면서 상대적으로 가상머신에 할당하는 메모리 크기가 커지고 있다. 즉 가비지 컬렉션의 대상이 되는 메모리 크기가 커질수록 그리고 객체 개수가 많을수록 가비지 컬렉션에 소요되는 시간은 길어지고 그 동안 자바 가상머신은 멈춘 것처럼 보인다. 따라서 바이트 버퍼 풀링을 사용하여 가비지 컬렉션 수행 횟수를 줄일 수 있다면 그야말로 가장 좋은 선택이다. 네티 바이트 버퍼 풀링은 ByteBufAllocator를 사용하여 바이트 버퍼를 생성할 때 자동으로 수행된다.

네티는 바이트 버퍼를 풀링하기 위해서 바이트 버퍼에 참조 수를 기록한다. 네티는 바이트 버퍼의 참조 수를 관리하기 위해여 ReferenceCountUtil 클래스에 정의된 retain 메서드와 release 메서드를 사용한다. retain 메서드는 참조 수를 증가시키고 release 메서드는 참조 수를 감소시킨다. 바이트 버퍼의 release 메서드를 호출하면 바이트 버퍼의 참조 수가 1 줄어들고 할당된 메모리가 해제된다. 만약 이미 참조 수가 0일 때 release 메서드를 호출하면 IllegalReferenceCountException이 발생한다.

##  버퍼 생성 예제
```java
public class CreateByteBufferByNettyTest {
    @Test
    public void createUnpooledHeapBufferTest() {
        ByteBuf buf = Unpooled.buffer(11);

        testBuffer(buf, false);
    }

    @Test
    public void createUnpooledDirectBufferTest() {
        ByteBuf buf = Unpooled.directBuffer(11);

        testBuffer(buf, true);
    }

    @Test
    public void createPooledHeapBufferTest() {
        ByteBuf buf = PooledByteBufAllocator.DEFAULT.heapBuffer(11);

        testBuffer(buf, false);
    }

    @Test
    public void createPooledDirectBufferTest() {
        ByteBuf buf = PooledByteBufAllocator.DFAULT.directBuffer(11);

        testBuffer(buf, true);
    }

    private void testBuffer(ByteBuf buf, boolean isDirect) {
        assertEquals(11, buf.capacity());

        assertEquals(isDirect, buf.isDirect());

        assertEquals(0, buf.readableBytes());
        assertEquals(11, buf.writableBytes());
    }
}
```

### Direct ByteBuffer VS Heap ByteBuffer
기본적으로 자바에서 "new" 키워드를 이용해서 생성되는 객체들은 모두 Heap 메모리 영역에 할당된다.  
Heap ByteBuffer(Non Direct ByteBuffer)는 byte 배열에 추가적인 기능을 제공하는 wrapper 클래스이다. Heap 메모리 영역에 할당된다.  
Direct ByteBuffer는 운영체제에서 관리하는 메모리 영역에 할당된다. Non Direct ByteBuffer 보다 더 빠른 읽기/쓰기 성능을 갖는다.

Direct ByteBuffer는 운영체제에 의해서 직접 메모리 영역에 I/O 작업이 발생한다. 그로 인해서 bytes의 연속성이 보장되어 더욱 빠른 읽기/쓰기가 가능해진다. JVM 밖의 메모리 공간에 할당되기 때문에 할당된 Direct ByteBuffer의 정보가 memory footprint의 결과에 확실하게 드러나지 않을 수 있다. Direct ByteBuffer는 JVM의 메모리 관리로부터 자유로우므로 가비지 컬렉터의 대상이 되지 않는다. 그러므로 Direct ByteBuffer는 주로 크고, 오랜 시간 사용되며 system의 I/O 작업을 목적으로하는 ByteBuffer의 할당에 추천된다. 

Heap ByteBuffer를 사용할 경우 JVM이 메모리를 관리하므로 가비지 컬렉터에 의해서 bytes가 연속적이지 않은 메모리 영역으로 이동될 수 있고, bytes가 연속된 메모리 공간에 존재하지 않게될 경우 다음 bytes를 찾아가는 작업이 추가적으로 필요하기 떄문에 운영체제에 의해서 직접 관리되는 것 보다 읽기/쓰기 성능이 저하될 수 있다.

[Direct ByteBuffer와 Non Direct ByteBuffer의 성능 비교](https://www.javacodegeeks.com/2013/08/which-memory-is-faster-heap-or-bytebuffer-or-direct.html)

Java Doc에서의 Direct ByteBuffer에 대한 설명
> A direct byte buffer may be created by invoking the allocateDirect factory method of this class. The buffers returned by this method typically have somewhat higher allocation and deallocation costs than non-direct buffers. The contents of direct buffers may reside outside of the normal garbage-collected heap, and so their impact upon the memory footprint of an application might not be obvious. It is therefore recommended that direct buffers be allocated primarily for large, long-lived buffers that are subject to the underlying system’s native I/O operations. In general it is best to allocate direct buffers only when they yield a measureable gain in program performance.

Ron Hitches의 저서 [Java NIO](https://www.amazon.com/dp/0596002882/?tag=stackoverflow17-20)에서의 Dircet Buffer에 대한 설명
> Operating systems perform I/O operations on memory areas. These memory areas, as far as the operating system is concerned, are contiguous sequences of bytes. It's no surprise then that only byte buffers are eligible to participate in I/O operations. Also recall that the operating system will directly access the address space of the process, in this case the JVM process, to transfer the data. This means that memory areas that are targets of I/O perations must be contiguous sequences of bytes. In the JVM, an array of bytes may not be stored contiguously in memory, or the Garbage Collector could move it at any time. Arrays are objects in Java, and the way data is stored inside that object could vary from one JVM implementation to another.
>
> For this reason, the notion of a direct buffer was introduced. Direct buffers are intended for interaction with channels and native I/O routines. They make a best effort to store the byte elements in a memory area that a channel can use for direct, or raw, access by using native code to tell the operating system to drain or fill the memory area directly.
>
> Direct byte buffers are usually the best choice for I/O operations. By design, they support the most efficient I/O mechanism available to the JVM. Nondirect byte buffers can be passed to channels, but doing so may incur a performance penalty. It's usually not possible for a nondirect buffer to be the target of a native I/O operation. If you pass a nondirect ByteBuffer object to a channel for write, the channel may implicitly do the following on each call:
>
> Create a temporary direct ByteBuffer object.
> Copy the content of the nondirect buffer to the temporary buffer.
> Perform the low-level I/O operation using the temporary buffer.
> The temporary buffer object goes out of scope and is eventually garbage collected.
> This can potentially result in buffer copying and object churn on every I/O, which are exactly the sorts of things we'd like to avoid. However, depending on the implementation, things may not be this bad. The runtime will likely cache and reuse direct buffers or perform other clever tricks to boost throughput. If you're simply creating a buffer for one-time use, the difference is not significant. On the other hand, if you will be using the buffer repeatedly in a high-performance scenario, you're better off allocating direct buffers and reusing them.
>
> Direct buffers are optimal for I/O, but they may be more expensive to create than nondirect byte buffers. The memory used by direct buffers is allocated by calling through to native, operating system-specific code, bypassing the standard JVM heap. Setting up and tearing down direct buffers could be significantly more expensive than heap-resident buffers, depending on the host operating system and JVM implementation. The memory-storage areas of direct buffers are not subject to garbage collection because they are outside the standard JVM heap.
>
> The performance tradeoffs of using direct versus nondirect buffers can vary widely by JVM, operating system, and code design. By allocating memory outside the heap, you may subject your application to additional forces of which the JVM is unaware. When bringing additional moving parts into play, make sure that you're achieving the desired effect. I recommend the old software maxim: first make it work, then make it fast. Don't worry too much about optimization up front; concentrate first on correctness. The JVM implementation may be able to perform buffer caching or other optimizations that will give you the performance you need without a lot of unnecessary effort on your part.

## Reference
[자바 네트워크 소녀 네티 : 비동기, 이벤트 기반 고성능 네트워크 애플리케이션 프레임워크 Netty](http://www.yes24.com/24/goods/20600128?scode=032&OzSrank=1)

https://stackoverflow.com/questions/5670862/bytebuffer-allocate-vs-bytebuffer-allocatedirect
