# Observer Pattern

1. [의도](#의도)
2. [동기](#동기)
3. [활용성](#활용성)
4. [참여자](#참여자)
5. [협력 방법](#협력-방법)
6. [예제 코드](#예제-코드)

## 의도
객체 사이에 일 대 다의 의존 관계를 정의해 두어, 어떤 객체의 상태가 변화할 때 그 객체에 의존성을 가진 다른 객체들이 그 변화를 통지받고 자동으로 갱신될 수 있게 만든다.

## 동기
하나의 시스템을 서로 연동되는 다수의 클래스로 분할할 때 발생하는 공통적인 부작용은 관련된 객체 간에 일관성을 유지하도록 해야 한다는 것이다. 그렇다고해서 일관성 관리를 위해서 객체 간의 결합도를 높이고 싶지는 않다. 각 클래스의 재사용성이 떨어지기 때문에.
예를 들어, ***GUI 툴킷은 표현 부분과 이에 대응하는 데이터를 분리한다***. 테이블 형태의 객체와 바 형태의 객체 모두 동일한 자료 값을 나타낸다면, 테이블과 바의 표현은 독립적으로 재사용이 가능해야 한다. 테이블과 바는 데이터 객체에 종속적이기 때문에 그 데이터에 일어난 변경을 통보받아야한다. 서로 다른 다수의 사용자 인터페이스가 하나의 데이터에 종속될 수 있다.  
감시자 패턴은 이런 관련성을 관리한다. 이 패턴에서 중요한 객체는 **주체**(Subject)와 **감시자**(Observer)이다. 주체는 독립된 여러 개의 감시가 있을 수 있다. 모든 감시자는 주체의 상태 변화가 있을 때마다 이 변화를 통보받는다. 각 감시자는 주체의 상태와 자신의 상태를 동기화시키기 위해서 주체의 상태를 알아본다.  
This kind of interaction is called **Publish-Subscribe** relation. 주체는 상태 변경에 대한 통보를 하는 것이므로 누가 감시자인지 모른 채 통보를 발송한다. 불특정 다수의 감시자가 이 통보를 수신하기 위해서 구독을 신청한다.

## 활용성
감시자 패턴을 사용하는 상황

* 어떤 추상 개념이 두 가지 양상을 갖고 하나가 다른 하나에 종속적일 때. 각 양상을 별도의 객체로 캡슐화하여 이들 가각을 재사용할 수 있다.
* 한 객체에 가해진 변경으로 다른 객체를 변경해야 하고, 프로그래머들은 얼마나 많은 객체들이 변경되어야 하는지 몰라도 될 때.
* 어떤 객체가 다른 객체에 자신의 변화를 통보할 수 있는데, 그 변화에 관심있어 하는 객체들이 누구인지에 대한 가정 없이도 그러한 통보가 될 때.

## 참여자
* **Subject**  
감시자들을 알고 있는 주체. 임의 개수의 감시자 객체는 주체를 감시할 수 있다. 주체는 감시자 객체를 붙이거나 떼는 데 필요한 인터페이스를 제공한다.
* **Observer**  
주체에 생긴 변화에 관심 있는 객체를 갱신하는 데 필요한 인터페이스를 정의한다. 이로써 주체의 변경에 따라 변화되어야 하는 객체들의 일관성을 유지한다.
* **ConcreteSubject**    
ConcreteObserver 객체에게 알려주어야 하는 상태를 저장한다. 이 상태가 변경될 때 감시자에게 변경을 통보한다.
* **ConcreteObserver**  
ConcreteSubject 객체에 대한 참조자를 관리한다. 주체의 상태와 일관성을 유지해야 하는 상태를 저장한다. 주체의 상태와 감시자의 상태를 일관되게 유지하는 데 사용하는 갱신 인터페이스를 구현한다.

## 협력 방법
* **ConcreteSubject**는 Observer의 상태와 자신의 상태가 달라지는 변경이 발생할 때마다 감시자에게 통보한다.  
* ConcreteSubject에서 변경이 통보된 후, **ConcreteObserver**는 필요한 정보를 주체에게 질의하여 얻어온다. **ConcreteObserver**는 이 정보를 이용해서 주체의 상태와 자신의 상태를 일치시킨다.  

### 누가 갱신을 촉발시킬 것인가?
Subject와 Observer가 각자 자신의 값을 정확하게 유지하기 위해서는 통보 메커니즘에 의존할 수밖에 없다. 값을 갱신하기 위해 어느 객체가 notify()를 호출해야하는가?

1. Subject 클래스의 상태 변경 후 상태를 지정하는 연산에서 notify()를 호출한다. Subject가 정의한 notify()를 사용자가 호출할 필요가 없다는 장점. 계속되는 연산의 수행으로 여러 번 수정해야한다는 비효율이 단점.
2. 사용자가 적절하게 notify()를 호출하는 책임을 지도록 한다. 이렇게하면 사용자가 일련의 상태 변경이 될 때까지 갱신의 시작을 미룰 수 있다. 그렇기 때문에 중간 중간 불필요한 수정이 일어나지 않는다. 단점은 사용자가 수정하게 하는 추가적인 행동을 정의하도록 해야한다. 사용자가 notify()의 호출을 잊는 경우가 많아서 오류 발생이 증가한다.

## 예제 코드
```java
public interface Observer {
    void update(Subject changedSubject);
}
```

```java
public abstract class Subject {
    private List<Observer> observers = new ArrayList<>();

    public void attach(Observer o) {
        observers.add(o);
    }

    public void detach(Observer o) {
        observers.remove(o);
    }

    public void notifyToObservers() {
        observers.forEach( o -> o.update(this));
    }
}
```

```java
public class DateCounter extends Subject {
    private Date date = new Date();

    public Date getDate() {
        return date;
    }

    public void after(int days) {
        date = new Date(date.getTime() + 86400000 * days);
        notifyToObservers();
    }
}
```

```java
public class SimpleDatePrinter implements Observer {
    private DateCounter dateCounter;
    private SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd");

    public SimpleDatePrinter(DateCounter dateCounter) {
        this.dateCounter = dateCounter;
        this.dateCounter.attach(this);
    }

    @Override
    public void update(Subject changedSubject) {
        if (changedSubject == dateCounter) {
            print();
        }
    }

    public void print() {
        Date date = dateCounter.getDate();
        System.out.println(formatter.format(date));
    }
}
```

```java
public class FullDatePrinter implements Observer {
    private DateCounter dateCounter;

    public FullDatePrinter(DateCounter dateCounter) {
        this.dateCounter = dateCounter;
        dateCounter.attach(this);
    }

    @Override
    public void update(Subject changedSubject) {
        if (changedSubject == dateCounter) {
            print();
        }
    }

    public void print() {
        Date date = dateCounter.getDate();
        System.out.println(date);
    }
}
```

```java
public class Main {
    public static void main(String[] args) {
        DateCounter dateCounter = new DateCounter();
        SimpleDatePrinter simpleDatePrinter = new SimpleDatePrinter(dateCounter);
        FullDatePrinter fullDatePrinter = new FullDatePrinter(dateCounter);

        for (int i = 0; i < 10; i++) {
            dateCounter.after(1);
        }
    }
}
```
### 출력 결과
```
2017-04-29
Sat Apr 29 11:48:19 KST 2017
2017-04-30
Sun Apr 30 11:48:19 KST 2017
2017-05-01
Mon May 01 11:48:19 KST 2017
2017-05-02
Tue May 02 11:48:19 KST 2017
2017-05-03
Wed May 03 11:48:19 KST 2017
2017-05-04
Thu May 04 11:48:19 KST 2017
2017-05-05
Fri May 05 11:48:19 KST 2017
2017-05-06
Sat May 06 11:48:19 KST 2017
2017-05-07
Sun May 07 11:48:19 KST 2017
2017-05-08
Mon May 08 11:48:19 KST 2017
```
