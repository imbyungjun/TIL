# Reflection
런타임 시점에 사용되는 자신의 구조와 행위를 관리(type introspection)하고 수정할 수 있는 프로세스.

많은 컴퓨터 아키텍쳐에서 프로그램 명령은 데이터와 같이 메모리에 적재되므로, 명령과 데이터 사이의 구분은 단지 컴퓨터와 프로그램 언어에 의하여 어떻게 정보가 처리되느냐의 문제이다. 일반적으로, 명령은 실행되고, 데이터는 명령의 자료로서 처리된다. 그렇지만, 어떤 언어에서는, 프로그램은 명령 역시 데이터와 같은 방식으로 처리 할 수 있기 때문에, Reflective 수정이 가능하게 된다. 가장 일반적으로 반영은 스몰토크, 스크립트 언어와 같이 높은 수준의 가상 머신 프로그램 언어에서 주로 많이 사용되고, 자바, C언어와 같이 선언적이거나 정적 형식의 프로그램 언어에서는 드물게 사용된다.

## 이용
반영은 런타임에 프로그램의 수행을 수정하고, 관찰하기 위하여 사용할 수 있다. 반영 지향적인 프로그램 구성 요소는 내부 코드의 실행을 감시할 수 있고, 구성 요소 자신의 궁극적인 목표에 맞도록 내부를 수정 할 수 있다. 이는 전형적으로 런타임에 프로그램 코드를 동적으로 할당하여 이루어진다.

반영은 프로그램을 서로 다른 상황에서 동적으로 사용할 수 있게 한다. 예를 들어, 비슷한 동작을 수행하는 서로 다른 클래스 'X'와 클래스 'Y'를 교체하여 사용하는 응용 프로그램을 고려해보자. 반영지향적이 아닌 프로그램 개발에서는, 응용 프로그램은 클래스 'X'와 클래스 'Y'의 함수를 호출하기 위하여, 함수를 직접 코드로 작성해야 한다. 반면, 반영 지향적인 프로그래밍 패러다임에서는 응용 프로그램은 함수를 직접 코드로 작성하지 않고 반영을 이용해서 설계되고 작성될 수 있다. 반영 지향적인 프로그램은 보다 보편적인(Generic) 코드의 수행의 기능을 사용하기 위하여, 대부분 추가적인 정보, 프레임워크, 연관 사상, 객체 관계 등을 필요로 한다. 반영 지향적인 프로그램 기술을 확장하면, 하드 코딩을 방지할 수 있다.

## Java Reflection Example
```
public class Sample {
	public static void main(String[] args) throws Exception {
		Class clazz = Class.forName(args[0]);
		Method methods[] = clazz.getDeclaredMethods();
		for (int i = 0; i < methods.length; i++) {
			System.out.println(methods[i].toString());
		}
	}
}
```
```
$ java Sample java.util.Stack
public java.lang.Object java.util.Stack.push(java.lang.Object)
public synchronized java.lang.Object java.util.Stack.pop()
public synchronized java.lang.Object java.util.Stack.peek()
public boolean java.util.Stack.empty()
public synchronized int java.util.Stack.search(java.lang.Object)
```

## Reference
https://ko.wikipedia.org/wiki/%EB%B0%98%EC%98%81_(%EC%BB%B4%ED%93%A8%ED%84%B0_%EA%B3%BC%ED%95%99)

http://gyrfalcon.tistory.com/entry/Java-Reflection

https://docs.oracle.com/javase/8/docs/api/java/lang/Class.html

https://docs.oracle.com/javase/8/docs/api/java/lang/reflect/package-summary.html
