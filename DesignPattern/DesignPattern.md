# Design Pattern
디자인 패턴이란 컴퓨터 프로그램의 설계에 있어서 자주 사용되는 기법들을 정리한 것이다. 디자인 패턴을 따르면 어느 정도 잘 정리되고 타인이 이해하기 쉬운 코드를 작성할 수 있게 된다. 이것은 디자인 패턴이 선조들의 지혜를 담고 있기 때문만은 아니다. 디자인 패턴은 특정한 이름으로 대다수의 프로그래머들에게 잘 알려져 있기 때문에 커뮤니케이션을 수월하게 하고 코드의 가독성을 높이는 데에 기여한다. 
> 최초 프로그램 설계시에 적합한 디자인 패턴을 선정하고 그에 따른 구현을 한다면 프로그램을 구현하는 데에 훨씬 수월함을 느낄 수 있을 것이다. 하지만 프로그램의 설계 단계에서 모든 기능적인 요구 사항이나 변경 가능성을 염두에 두고 적합한 디자인 패턴을 선정하는 일은 쉬운 일이 아니다. 반드시 디자인 패턴을 선정한 이후에 프로그래밍에 착수해야 하는 것은 아니다. 프로그램의 개발이 진행됨에 따라서 자연스럽게 어떠한 디자인 패턴과 비슷한 양상을 띄게 되거나 적용할만한 디자인 패턴을 발견하게 될 수 있다.

## 디자인 패턴의 분류
*Gof의 디자인 패턴*에서는 아래와 같이 디자인 패턴을 분류한다.
### 첫 번째 분류 기준 : 목적
### 두 번째 분류 기준 : 범위
<table>
<tr>
    <td colspan="2" rowspan="2"></td>
    <td colspan="3"><strong>Purpose</strong></td>
</tr>
<tr>
    <td><strong>Creational</strong></td>
    <td><strong>Structural</strong></td>
    <td><strong>Behavioral</strong></td>
</tr>
<tr>
    <td rowspan="2"><strong>Scope</strong></td>
    <td><strong>Class</strong></td>
    <td>Factory Method</td>
    <td>Adapter</td>
    <td>Interpreter<br>Template Method</td>
</tr>
<tr>
    <td><strong>Object</strong></td>
    <td>Abstract Factory<br>Builder<br>Prototype<br>Singleton</td>
    <td>Adapter<br>Bridge<br>Composite<br>Decorator<br>Facade<br>Proxy</td>
    <td>Chain of Responsibility<br>Command<br>Iterator<br>Mediator<br>Memento<br>Flyweight<br>Observer<br>State<br>Strategy<br>Visitor
</td>
</tr>
</table>

## Reference
[GoF의 디자인 패턴 : 재사용성을 지닌 객체지향 소프트웨어의 핵심요소](https://ko.wikipedia.org/wiki/%EB%94%94%EC%9E%90%EC%9D%B8_%ED%8C%A8%ED%84%B4_(%EC%B1%85))
