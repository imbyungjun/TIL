# Stream Sorted
스트림API의 sorted() 메서드는 두가지 구현이 존재한다. 각 메서드를 이용해서 스트림을 정렬하는 방법을 다룬다.

## Stream.sorted()
매개변수가 없는 sorted() 메서드. 입력 스트림의 요소가 Comparable 인터페이스를 구현해야한다. 요소에 구현된 compareTo() 메서드의 구현에 따라 입력 스트림을 정렬한 새로운 스트림을 출력한다. compareTo() 메서드는 요소 자신이 더 앞에 정렬되기 위해서는 음수를 리턴, 다른 요소가 더 앞에 정렬되기 위해서는 양수를 리턴, 같을 경우는 0을 리턴하도록 구현한다. 쉽게말해 오름차순 정렬을 위해서는 `this - other` 와 같이 구현한다.

#### 1. 사람 스트림중 나이가 어린 순서대로 정렬하는 예제.
```
Person p1 = new Person(11, "Kim");
Person p2 = new Person(39, "Park");
Person p3 = new Person(20, "Lee");

Stream.of(p1, p2, p3)
    .sorted()
    .forEach(System.out::println);

class Person implements Comparable<Person> {
    int age;
    String name;

    public Person(int age, String name) {
        this.age = age;
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    @Override
    public int compareTo(Person other) {
        return this.age - other.age;
    }

    @Override
    public String toString() {
        return age + "\t" + name;
    }
}
```

## Stream.sorted(Comparator)
매개변수로 Comparator를 전달받는 sorted() 메서드. 입력 스트림을 정렬할 수 있는 Comparator가 매개변수로 전달되어야한다. Comparator 메서드는 입력 스트림의 요소를 매개변수로하고 int를 리턴하는 메서드이다. 람다를 이용하여 간단하게 구현할 수 있고, 혹은 별도의 함수를 선언하여 매개변수로 전달할 수 있다.

#### 1. 람다를 이용한 정렬 예제.
```
Stream.of(p1, p2, p3)
    .sorted((a, b) -> a.age - b.age)
    .forEach(System.out::println);
```

#### 2. Comparator.comparing() 메서드를 이용한 정렬 예제.
```
Stream.of(p1, p2, p3)
    .sorted(Comparator.comparing(p -> p.age))
    .forEach(System.out::println);
```

#### 3. 사람 스트림중 나이가 많은 순서대로 정렬하는 예제.
```
Stream.of(p1, p2, p3)
    .sorted(Comparator.comparing(Person::getAge).reversed())    // reversed()가 속성에 대해서는 안되는 이유는 잘 모르겠음...
    .forEach(System.out::println);
```

#### 4. Comparator를 구현하여 오름차순 정렬하는 예제.
```
private int asc(Person a, Person b) {
    return a.age - b.age;
}

Stream.of(p1, p2, p3)
    .sorted(this::asc)
    .forEach(System.out::println);
```

#### 5. Comparator를 구현하여 내림차순 정렬하는 예제.
```
private int desc(Person a, Person b) {
    return b.age - a.age;
}

Stream.of(p1, p2, p3)
    .sorted(this::desc)
    .forEach(System.out::println);
```

