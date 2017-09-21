# Stream
### 목차
1. [Stream](#stream_1)
2. [Filter, Map, FlatMap 메서드](#filter-map-flatmap)
3. [서브스트림 추출과 스트림 결합](#_2)
4. [상태 유지 변환](#_3)

## Stream
Java 8에서 추가된 API로 기존의 Iterator과 Collection을 보다 편리하게 사용할 수 있게 해준다.  
스트림과 컬렉션은 매우 유사하지만 다음과 같은 차이점이 있다.

* 스트림은 요소들을 보관하지 않는다. 요소들은 하부의 컬렉션에 보관되거나 필요할 때 생성된다.
* 스트림 연산은 원본을 변경하지 않는다. 대신 결과를 담은 새로운 스트림을 반환한다.
* 스트림 연산은 가능하면 지연 처리된다. 지연 처리란 결과가 필요하기 전에는 실행되지 않음을 의미한다. (예를 들어, 긴 단어를 모두 세는 대신 처음 5개 긴 단어를 요청하면, filter 메서드는 5번 째 처리 후 필터링을 중단한다.)

ex) 사람 이름 목록중에 특정 철자가 포함된 사람의 인원수를 세는 프로그램

```
List<String> people = Arrays.asList("John", "Sam", "Robert");
long count = 0;
for (String person : people) {
    if (person.toLowerCase().contains("s")) {
        count++;
    }
}
```

위 코드를 Stream API를 사용하면 아래와 같이 구현이 가능하다.

```
List<String> people = Arrays.asList("John", "Sam", "Robert");
long count = people.stream()
                .filter(person -> person.toLowerCase().contains("s"))
                .count();
```

filter와 같은 메서드들로 기존에 반복문을 사용하여 수행하던 전형적인 작업들을 간단하게 표현할 수 있다. 이런 특성을 **반복의 내재화**라고 한다. 이를 통해 우리는 코드의 작성량을 줄일 수 있다. 코드의 작성량이 줄어들면 우리가 버그를 만들어낼 확률도 줄어든다.

추가적으로, 스트림을 사용하면 병렬수행을 쉽게 할 수 있다는 장점이 있다.
```
long count = people.parallelStream()
                 .filter(person -> person.toLowerCase().contains("s"))
                 .count();
```
Stream API는 단순히 stream을 parallelStream으로 변경하는 것만으로 Thread safety를 보장한다.  
[Parallel Streams Collectors and Thread Safety](https://stackoverflow.com/questions/22350288/parallel-streams-collectors-and-thread-safety)

스트림은 **어떻게가 아니라 무엇을** 원칙을 따른다. 작업이 어떤 순서로 또는 어떤 스레드에서 일어나야 하는지 명시하지 않는다. 이것은 [함수형 프로그래밍](https://medium.com/@jooyunghan/%ED%95%A8%EC%88%98%ED%98%95-%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%98%EB%B0%8D%EC%9D%B4%EB%9E%80-%EB%AC%B4%EC%97%87%EC%9D%B8%EA%B0%80-fab4e960d263) 또는 선언형 프로그래밍에서 추구하는 함수의 모습과 비슷하다. **어떻게**에 해당하는 시퀀스는 의존관계를 만든다. 코드에서 의존관계를 제거하면 코드 작성량을 줄일 수 있다. **무엇을**에 집중하면 side-effect를 줄이고, 합성성(재사용성)을 얻을 수 있다.
> 명령형 프로그래밍(Declarative Programming)은 어떻게 수행할지를 명세한다.  
> 선언형 프로그래밍(Imperative Programming)은 무엇을 수행할지를 명세한다.

## Filter, Map, FlatMap 메서드

### Filter
Filter는 입력 스트림에서 데이터를 읽어서 특정 조건에 부합하는 데이터들을 추려내어 새로운 스트림으로 반환한다. Filter는 [Predicate&lt;T&gt;](https://docs.oracle.com/javase/8/docs/api/java/util/function/Predicate.html)를 매개변수로 입력받는다. 쉽게말해서 해당 스트림의 타입 T를 매개변수 전달받고 boolean을 리턴하는 함수이다.

ex) 사람 스트림중 나이가 20살보다 적은 사람만을 얻는 필터
```
Stream<Person> youngPeople = people.filter(person -> person.getAge() < 20);
```

### Map


### FlatMap


## 서브스트림 추출과 스트림 결합
`stream.limit(n)` 메서드는 n개 요소 이후(원본 스트림이 n보다 짧은 경우는 원본 스트림이 끝날 때) 끝나는 새로운 스트림을 리턴한다. 이 메서드는 무한 스트림을 필요한 크기로 잘라낼 때 유용하다. 

ex) 100개의 난수를 포함하는 스트림
```
Stream<Double> randoms = Stream.generate(Math::random).limit(100);
```

`stream.skip(n)` 메서드는 처음 n개 요소를 버린다.

`stream.peek()` 메서드는 원본과 동일한 스트림을 리턴하면서 전달받은 함수를 요소마다 수행한다. 디버깅에 유용하다.  
[Stream Peek vs ForEach](https://stackoverflow.com/questions/33635717/in-java-streams-is-peek-really-only-for-debugging)

`Stream.concat()` 메서드는 매개변수로 전달되는 두 스트림을 연결시킨다. 첫번째 스트림이 무한 스트림일 경우엔 연결이 불가능하다.

ex) 무한 스트림에 다른 스트림을 연결하는 예제
```
Stream<Double> one = Stream.generate(Math::random);     // 무한 스트림
Stream<Double> another = Stream.of(1.0, 2.0, 0.3, 0.4);

Stream<Double> concat = Stream.concat(one, another);
```
위 예제를 실행할 경우 아무런 이상이 없이 프로그램이 종료한다. 그 이유는 해당 스트림을 사용하지 않았기 때문에 `Lazy evaluation`에 의해서 스트림을 실질적으로 생성하기위한 무한 반복을 수행하지 않기 때문이다. 만약 위 예제에서 one 또는 concat 스트림을 호출할 경우 예외는 발생하지 않지만 무한 스트림을 생성하기 위해서 무한 반복을 수행한다.

## 상태 유지 변환
필터 또는 맵핑된 스트림에서 요소를 추출할 때 결과가 이전 요소에 의존하지 않는다`stateless transformation`. 상태에 의존적인 변환`stateful transformation`의 예로 `distinct()` 메서드가 있다. distinct() 메서드는 원본 스트림에서 중복되는 요소들을 제거하여 원본과 같은 순서를 갖는 스트림을 출력한다.

`sorted()` 메서드도 상태에 의존적이다. 가장 마지막 요소까지 정렬하기 전까지의 정렬 상태를 유지해야한다. sorted() 메서드는 Comparable 인터페이스를 구현한 요소들을 정렬하거나 매개변수로 Comparator를 전달받아서 정렬을 수행한다.  
[Stream.sort() 사용하기](../StreamSort.md)
> Collections.sort 메서드는 컬렉션을 직접 정렬한다.
> Stream.sorted 메서드는 정렬된 새로운 스트림을 리턴한다.

## Reference
**Java SE 8 for the Really Impatient: A Short Course on the Basics** by Cay S. Horstmann
