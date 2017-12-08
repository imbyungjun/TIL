# Pageable
**Pageable** 클래스는 **Spring Framework**에 포함되어있는 페이지네이션 정보를 저장하는 추상 인터페이스이다. 직접 페이지네이션을 구현하는 일은 매우 귀찮은 일이다. 전체 행 수를 세고, 페이지당 출력할 행의 갯수에 따라서 페이지 갯수를 판단하고 N번부터 M번까지를 가져오는 계산을 해주어야 한다. 이것을 Pageable을 이용하면 보다 편하게 구현할 수 있다.

## Find All
Repository.findAll() 메서드는 매개변수를 입력하지 않을 경우 모든 행을 가져온다. 그 외에도 매개변수를 받아서 조건에 부합하는 행들을 리턴하는 방식도 존재하는데, 아래와 같다.
- findAll(Iterable<Integer> ids): List<Entity>
    ids를 입력하여 다수의 Entity를 리스트로 리턴
- findAll(Sort sort): List<Entity>
    Sort를 입력하여 정렬된 리스트를 리턴
- findAll(Pageable pageable): Page<Entity>
    Pageable을 입력하여 해당 페이지에 출력될 행들과 페이지 정보를 갖는 Pageable 리스트를 리턴

## Example

## Reference
https://docs.spring.io/spring-data/jpa/docs/2.0.2.RELEASE/reference/html/#repositories
