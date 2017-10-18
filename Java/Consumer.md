# Consumer

## Package
java.util.function

## Description
```
Interface Consumer<T>
```

T - 수행할 입력의 타입

주어진 한개의 매개변수에 대한 처리를 수행한다. 리턴값은 없다. 함수형 인터페이스이므로 람다 표현식이 사용될 수 있다. `accept(T t)` 메서드를 함수형 메서드로 갖는다.

> Consumer is expected to operate via side-effects.

## Methods
1. `void accept(T t)`  
주어진 입력에 대한 수행을 한다.
2. `default Consumer<T> andThen(Consumer<? super T> after)`  
매개변수로 전달된 after와 결합된 Consumer를 리턴한다. 이 작업 다음에 after가 순차적으로 수행된다. 예외를 던질 수 있으며 예외는 결합된 연산의 호출자에게 전달된다. 만약 이 작업을 수행하는 도중에 예외가 발생한다면 after의 작업은 수행되지 않는다.

## Examples
#### Consumer를 매개변수로 이용하는 방법
```java
class Person {
    String name;
    int age;
}

List<Person> people = Arrays.asList(new Person("A", 1), new Person("B", 2));
acceptAll(people, System.out::println);
acceptAll(people, p -> p.age += 1);

void acceptAll(List<Person> people, Consumer<Person> c) {
    for (Person p : people) {
        c.accept(p);
    }
}
```

#### Consumer를 Exception handler로 이용하는 방법
```java
void doInOrder(Runnalbe first, Runnable second) {
    first.run();
    second.run();
}
```
위와 같이 구현할 경우 first.run()을 수행하는 도중 예외가 발생한다면 second는 실행되지 않을 것이다.

```java
void doInOrderAsync(Runnalbe first, Runnable second) {
    Thread t = new Thread(() -> {
        first.run();
        second.run();
    });
    t.start();
}
```
위의 경우는 first가 수행되는 도중 예외가 발생할 경우 호출자가 예외를 처리할 수 없다. 위와 같은 상황에서 예외를 처리하기 위해서 Consumer를 이용할 수 있다.

```java
void doInOrderAsync(Runnable first, Runnable second, Consumer<Throwalbe> handler) {
    Thread t = new Thread(() -> {
        try {
            first.run();
            second.run();
        } catch (Throwable t) {
            handler.accept(t);
        }
    });
    t.start();
}
```
## Reference
https://docs.oracle.com/javase/8/docs/api/java/util/function/Consumer.html

http://www.java2s.com/Tutorials/Java/java.util.function/Consumer/index.htm
