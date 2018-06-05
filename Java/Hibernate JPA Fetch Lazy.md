# Hibernate JPA Fetch Lazy
Hibernate에서의 fetch 방식은 Eager와 Lazy가 존재한다. Fetch 방식을 Lazy로 설정한 경우에는 조인이 필요한 다른 테이블의 객체를 실질적으로 사용할 때에 읽어올 수 있다. 이를 위해서 hibernate는 최초 조회시에는 lazy fetch를 위한 proxy객체를 만들어 둔다. 실질적으로 사용되는 시점을 판단하는것은 해당 세션이 유지되는 동안에 유효하다. 서로 다른 메서드에서 세션이 유지되길 원한다면 `@Transactional` 어노테이션으로 세션이 유지되도록 설정해야한다.

## Fetch Lazy에서 조회시 연관 객체 로드하기
```java
@Entity
public class Person {
    @Id
    @GeneratedValue
    private Long id;

    @ManyToMany(fetch = FetchType.LAZY)
    private List<Role> roles;
    // etc
}
```
```java
@Controller
@RequestMapping("/person")
public class PersonController {
    @Autowired
    PersonRepository personRepository;

    @RequestMapping("/get")
    public @ResponseBody Person getPerson() {
        Person person = personRepository.findOne(1L);
        return person;
    }
}
```
```java
public interface PersonRepository extends JpaRepository<Person, Long> {
    @Query("SELECT p FROM Person p JOIN FETCH p.roles WHERE p.id = (:id)")
    public Person findByIdAndFetchRolesEagerly(@Param("id") Long id);
}
```

## Reference
http://ecogeo.tistory.com/242

https://stackoverflow.com/questions/15359306/how-to-load-lazy-fetched-items-from-hibernate-jpa-in-my-controller
