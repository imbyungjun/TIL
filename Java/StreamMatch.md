# Match
Java 8 stream의 match를 이용하면 간략하게 원하는 데이터의 존재 유무를 알아낼 수 있다.

## Stream.allMatch
Stream의 모든 원소가 주어진 조건을 만족할 때 True를 리턴, 아닐경우 False를 리턴한다.

## Stream.anyMatch
Stream의 원소 중 하나의 원소라도 주어진 조건을 만족할 때 True를 리턴, 아닐경우 Flase를 리턴한다.

## Stream.noneMatch
Stream의 원소들 중 어느것도 주어진 조건을 만족하지 않을 때 True를 리턴, 아닐경우 Flase를 리턴한다.

## Example
```
import static org.junit.Assert.*;

import java.util.ArrayList;
import java.util.List;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;

@RunWith(JUnit4.class)
public class Match {
    List<Person> people;

    @Before
    public void setup() {
        people = new ArrayList<>();
        people.add(new Person("A", 10));
        people.add(new Person("B", 15));
        people.add(new Person("C", 20));
        people.add(new Person("D", 30));
    }

    @Test
    public void allMatchTest() {
        // Given, When
        boolean allOverFive = people.stream()
                                .allMatch(p -> p.getAge() > 5);
        boolean allOverFifteen = people.stream()
                                    .allMatch(p -> p.getAge() > 15);
        // Then
        assertTrue(allOverFive);
        assertFalse(allOverFifteen);
    }

    @Test
    public void anyMatchTest() {
        // Given, When
        boolean anyOverFifteen = people.stream()
                                .anyMatch(p -> p.getAge() > 15);
        boolean anyOverThirty = people.stream()
                                    .anyMatch(p -> p.getAge() > 30);
        // Then
        assertTrue(anyOverFifteen);
        assertFalse(anyOverThirty);
    }

    @Test
    public void noneMatchTest() {
        // Given, When
        boolean noneUnderTen = people.stream()
                                .noneMatch(p -> p.getAge() < 10);
        boolean noneUnderFifteen = people.stream()
                                    .noneMatch(p -> p.getAge() < 15);
        // Then
        assertTrue(noneUnderTen);
        assertFalse(noneUnderFifteen);
    }
}

class Person {
    String name;
    int age;

    public Person(String name, int age) {
        this.name = name;
        this.age = age;
    }

    public String getName() {
        return name;
    }

    public int getAge() {
        return age;
    }
}
```
