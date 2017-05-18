# Difference between Thread Start and Run

Given
```
class R1 implements Runnable {
	@Override
	public void run() { ... }
}

class R2 implements Runnable {
	@Override
	public void run() { ... }
}
```

1. Create each objects that implements Runnable interface
```
public static void main(String[] args) {
	R1 r1 = new R1();
	R2 r2 = new R2();

	r1.run();
	r2.run();
}
```
No multiple threads. Both execute in single(existing) thread. No thread creation. => Just call a method.

2. Create two seperate threads.
```
public static void main(String[] args) {
	R1 r1 = new R1();
	R2 r2 = new R2();

	Thread t1 = new Thread(r1);
	Thread t2 = new Thread(r2);

	t1.start();
	t2.start();
}
```
**t1** and **t2** are the objects of the class `Thread`. When you call `t1.start()`, it starts a new thread and calls the `run()` method of **r1** internally to execute it within that new thread.

If you just invoke run() directly, it's executed on the calling thread, just like any other method call.  Thread.start() is required to actually create a new thread so that the runnable's run method is executed in parallel.

Couuld I consider that before we call Thread#start() ,nothing really relative to os thread happens? It is only a java object.  
That's correct according to the documentation. Check the thread object initialization code, which conforms to the documentation. Also in the source code, it's the start(), which is calling a natvie method, which must be making the os thread related things happen.  
Just to make it clear. There is no need to create Threads with new Thread( r1 ) instead of new R1(). The key is to use the start() method instead of run

http://stackoverflow.com/questions/8579657/whats-the-difference-between-thread-start-and-runnable-run
