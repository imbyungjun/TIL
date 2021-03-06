# Strategy Pattern
> 자신의 기능 맥락에서, 필요에 따라 변경이 필요한 알고리즘을 인터페이스를 통해 통째로 외부로 분리시키고, 이를 구현한 구체적인 알고리즘 클래스를 필요에 따라 바꿔서 사용할 수 있게 하는 디아진 패턴.

## 의도
동일한 계열의 알고리즘들을 정의하고, 각 알고리즘을 캡슐화하면, 이들을 상호교환이 가능하도록 만든다.

## 동기
입력값에 따라서 원하는 결과를 만들어내기까지 서로 다른 알고리즘이 필요한 경우가 존재한다. 이런 알고리즘들을 직접 클래스에 하드코딩하는 것은 바람직하지 않다. 

- 알고리즘을 직접 클래스에 명시하면 클래스의 크기가 점점 커지고 클래스가 복잡해짐에 따라서 유지보수하기가 점점 힘들어진다. 만약 같은 결과를 낼 수 있는 다수의 알고리즘을 제공한다면 더욱 그렇다.
- 때에 따라서 필요한 알고리즘이 다르기 때문에 모든 알고리즘을 제공할 필요는 없다.
- 알고리즘이 클래스와 합쳐져있다면 새로운 알고리즘을 추가하기가 어렵다.

## 활용성
- 행동들이 조금씩 다를 뿐 개념적으로 관련된 많은 클래스들이 존재할 때. 전략 패턴은 많은 행동 중 하나를 가진 클래스를 구성할 수 있도록 한다.
- 알고리즘의 변형이 필요할 때. 
- 사용자가 몰라야 하는 데이터를 사용하는 알고리즘이 있을 때. 노출하지 말아야 할 복잡한 자료 구조는 Straegy 클래스에만 두면 되므로 사용자는 몰라도 된다.
- 하나의 클래스가 많은 행동을 정의하고, 이런 행동들이 그 클래스의 연산 안에서 복잡한 다중 조건문의 모습을 취할 때. 많은 조건문보다는 각각을 strategy 클래스로 옮기는것이 좋다.

## 참여자
- Strategy : 제공하는 모든 알고리즘에 대한 공통의 연산들을 인터페이스로 정의한다.
- ConcreteStrategy : Strategy 인터페이스를 실제 알고리즘으로 구현한다.
- Context : ConcreteStrategy 객체를 사용한다. Strategy 객체에 대한 참조자를 관리한다.

## 협력 방법
- Context 클래스는 알고리즘에 해당하는 연산이 호출되면, 알고리즘 처리에 필요한 모든 데이터를 Strategy 클래스로 보낸다. (Context 객체 자체를 Strategy 연산의 인자로 전달하는것도 좋은 방법이다.)
- Context 클래스는 사용자 쪽에서 온 요청을 각 전략 객체로 전달한다. 이를 위해서 사용자는 필요한 알고리즘에 해당하는 ConcreteStrategy 객체를 생성하여 알고리즘 처리에 활용한다.

## 결과
1. 동일 계열의 관련 알고리즘들이 생긴다.
Strategy 클래스 계층은 동일 계열의 알고리즘군 혹은 행동군을 정의한다. 이런 알고리즘 자체의 재사용도 가능하다. 상속을 통해서 알고리즘 공통의 기능들을 추출하고 이를 재사용할 수 있다.
2. 서브클래싱을 사용하지 않는 대안이다. 상속은 다양한 알고리즘이나 행동을 지원하는 방법이다. 서로 다른 행동을 제공하기 위해 Context 클래스를 직접 상속받을 수 있다. 그러나 행동의 처리 방법을 Context에 직접 코딩하면 추후 수정이 어렵다. 즉, Context 자체의 행동과 알고리즘이 혼합되어 Context 클래스를 이해하거나 유지보수하기 어렵다. 그러므로 다양하게 알고리즘을 만들어 낼 수 없다. 
3. 조건문을 없앨 수 있다.
전략 패턴을 사용하면 원하는 행동들을 선택하는 조건문을 없앨 수 있다. 서로 다른 행동이 하나로 묶이면 조건문을 사용해서 정확한 행동을 선택할 수밖에 없다. 서로 다른 Strategy 클래스의 행동을 캡슐화하면 조건문을 없앨 수 있다. 많은 조건문을 포함하는 코드는 전략 패턴의 필요성을 생각하게 한다.
4. 구현의 선택이 가능하다.
동일한 행동에 대해서 서로 다른 구현(Strategy)을 제공할 수 있다.

## 구현
