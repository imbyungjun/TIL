# Observer

1. [Observer](https://docs.oracle.com/javase/7/docs/api/java/util/Observer.html)를 구현한 클래스에서 주시하는 값의 변경이 있을 경우 수행할 메서드를 구현한다.
2. [Observable](https://docs.oracle.com/javase/7/docs/api/java/util/Observable.html)을 상속받는 클래스에서 값이 변경되었음을 알린다. 

## 예제 코드
```java
public class Main {
    public static void main(String[] args) {
        DateCounter dateCounter = new DateCounter();
        SimpleDatePrinter simpleDatePrinter = new SimpleDatePrinter();
        FullDatePrinter fullDatePrinter = new FullDatePrinter();

        dateCounter.addObserver(simpleDatePrinter);
        dateCounter.addObserver(fullDatePrinter);

        for (int i = 0; i < 10; i++) {
            dateCounter.after(1);
        }
    }
}
```
```java
public class DateCounter extends Observable {
    private Date date = new Date();

    public Date getDate() {
        return date;
    }

    public void after(int days) {
        date = new Date(date.getTime() + 86400000 * days);
        setChanged();
        notifyObservers(date);
    }
}
```
```java
public class FullDatePrinter implements Observer {
    public FullDatePrinter() { }

    @Override
    public void update(Observable dateCounter, Object date) {
        if (date instanceof Date) {
            print((Date) date);
        }
    }

    public void print(Date date) {
        System.out.println(date);
    }
}
```
```java
public class SimpleDatePrinter implements Observer {
    private SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd");

    public SimpleDatePrinter() { }

    @Override
    public void update(Observable dateCounter, Object date) {
        if (date instanceof Date) {
            print(date);
        }
    }

    private void print(Date date) {
        System.out.println(formatter.format(date));
    }
}
```

## 수 많은 instanceof
주시하는 클래스에서 변경된 값이 내가 기다리던 값인지 확인하기 위해서 `instanceof` 키워드를 사용할 수 있다. 하지만 이런 구현은 동일한 타입의 변경사항을 같은 Observable 클래스에서 변경하고자할 경우 예상하지 못한 동작을 하게될 것이다. `getClass()`를 사용하는 경우는 조금 더 나을 수 있지만 결국 비슷한 문제점을 갖고있다. 이런 문제를 해결하는 방법은 무엇인가? 

단일 책임 원칙을 철저히 적용해서 하나의 Observer가 최대한 적은 종류의 알림에 대한 로직을 갖도록 하는것이 최선의 방법이라고 생각한다. 하나의 Observer가 여러가지 기능을 수행해야 한다면 여러가지 타입의 알림으로 분기하여 알림을 주고 받을 수 밖에 없게된다. 각각의 Observer가 한 가지 일만 처리하도록 설계된다면 보다 적은 타입에 대하여 알림을 주고 받게되어 이해하기 쉬운 코드를 작성하게 될 것이다.

---

최근에 관심을 갖게된 방식은 [Actor model](https://ko.wikipedia.org/wiki/%ED%96%89%EC%9C%84%EC%9E%90_%EB%AA%A8%EB%8D%B8)이다. Java9에서 Observer, Observable이 deprecated됨에 따라서 대체할 방식을 탐색하던 중 [AKKA-Actors](https://doc.akka.io/docs/akka/2.5.5/scala/actors.html) 라이브러리를 알게되었다. 기존에 Observer pattern을 사용할 때는 누가 알림을 전달하고 누가 받을것인가의 관점에서 생각을 했지만, actor model을 사용하면서 더욱 자연스럽게 객체지향적 사고를 할 수 있었던것 같다. ActorSystem에서 관리되는 각각의 Actors가 존재하는것이 객체지향 관점과 너무 잘 들어맞아서 객체간의 메세지를 주고받는 설계가 너무나 자연스럽게 느껴져서 좋았다. 

AKKA-Actors 관련한 정리는 추후에...


## References
https://stackoverflow.com/questions/15724917/observer-pattern-in-java-observer-observes-different-unrelated-types-or-class
