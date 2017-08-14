# Observer

1. [Observer](https://docs.oracle.com/javase/7/docs/api/java/util/Observer.html)를 구현한 클래스에서 주시하는 값의 변경이 있을 경우 수행할 메서드를 구현한다.
2. [Observable](https://docs.oracle.com/javase/7/docs/api/java/util/Observable.html)을 상속받는 클래스에서 값이 변경되었음을 알린다. 

## 예제 코드
```
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
```
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
```
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
```
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

## instanceof
주시하는 클래스에서 변경된 값이 내가 기다리던 값인지 확인하기 위해서 `instanceof` 키워드를 사용할 수 있다. 하지만 이런 구현은 동일한 타입의 변경사항을 같은 Observable 클래스에서 변경하고자할 경우 예상하지 못한 동작을 하게될 것이다. `getClass()`를 사용하는 경우는 조금 더 나을 수 있지만 결국 비슷한 문제점을 갖고있다. 이런 문제를 해결하는 방법은 무엇인가? 모르겟다.

https://stackoverflow.com/questions/15724917/observer-pattern-in-java-observer-observes-different-unrelated-types-or-class
