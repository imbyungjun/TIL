# Method References

Lambda expression을 사용하다보면 메소드를 호출하기만하는 경우가 있다. **Method References**는 이런 경우에 메소드의 이름으로 접근해서 아주 간결한 표현을 하도록 도와준다.

## When using Lambda Expression
```
public class Person {
	private String name;
	...

	/* Getters and Setters ... */
	
	public static int compareByName(Person p1, Person p2) {
		return p1.getName().compareTo(p2.getName());
	}
}
```
```
@Test
public void sortByPersonNameWithLambda() {
	Person a = new Person("AAA");
	Person b = new Person("BBB");
	Person c = new Person("CCC");

	List<Person> people = Arrays.asList(a, b, c);

	// Comparator is a functional interface
	people.sort( (Person a, Person b) -> {
			return a.getName().compareTo(b.getName());
	});

	// Using compareByName method in Person class
	people.sort( (a, b) -> Person.compareByName(a, b) );
}
```

## When using Method References
```
@Test
public void sortByPersonNameWithMethodReferences() {
	Person a = new Person("AAA");
	Person b = new Person("BBB");
	Person c = new Person("CCC");

	List<Person> people = Arrays.asList(a, b, c);

	people.sort(Person::compareByName);
}
```

## Kinds of Method References
| Kind | Example |
|:----|:-------|
| Reference to a static method | ContainingClass::staticMethodName |
| Reference to an instance method of a particular object | containingObject::instanceMethodName|
| Reference to an instance method of an arbitrary object of a particular type | ContainingType::methodName |
| Reference to a constructor | ClassName::new |
