# Stream
### 목차
1. [Stream](#stream_1)
2. [Filter, Map, FlatMap 메서드](#filter-map-flatmap)

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



## Reference
**Java SE 8 for the Really Impatient: A Short Course on the Basics** by Cay S. Horstmann
