# Selector
https://docs.oracle.com/javase/7/docs/api/java/nio/channels/Selector.html

## Package
java.nio.channels.Selector

## Description
```
public abstract class Selector
extends Object
implements Closeable
```

A multiplexor of `SelectableChannel` objects.

이 클래스의 `open` 메소드 또는 시스템의 기본 selector provider 가 selector 객체를 생성한다. Custom selector provider에 의해서 생성될 수도 있다. 이 클래스의 `close` 메소드가 호출되기 전까지 selector는 열려있는 상태로 남아있다.

Selector를 이용한 selectable channel의 등록은 `SelectionKey` 객체에 의해 표현될 수 있다. Selector 객체는 3개의 selection keys sets를 유지한다.

* **key set**은 selector의 현재 channel registrations를 표현한다. 이 set은 `keys()`메소드를 호출함으로서 얻을 수 있다.
* **selected-key set**은 이전의 operation이 수행되는 동안 적어도 하나 이상의 operation이 준비되었다고 감지된 키의 채널의 집합이다. (The key's interest set)
* **cancelled-key set**은 취소요청었지만 아직 등록이 취소되지 않은 키들의 집합이다. 이 set은 직접적인 접근이 불가능하다. The cancelled-key set 은 언제나 the key set의 subset이다.


새로 생성된 selector는 비어있는 3개의 key sets 을 갖는다.

Channel의 `register` 메소드를 호출하면 selector의 key set에 key가 추가된다. Cancelled keys는 selection operation을 수행하는 동안 key set에서 삭제된다. The key set 자체는 직접적으로 수정이 불가능하다.

A key가 취소되면 자신의 selector의 cancelled-key set에 추가된다. Key가 취소되는 경우는 자신의 channel을 닫는 경우 또는 자신의 `cancel` 메소드를 호출하는 경우이다. 키를 취소하는 일은 다음 selcetion operation 중에 자신의 channel의 등록 해제를 유발시킨다. 그리고, 그때 모든 selector의 key set에서 제거된다. 

Keys 는 selection operation에 의해서 selected-key set에 추가된다. Set의 `remove` 메소드가 호출되거나 set에서 얻어낸 iterator의 `remove` 메소드가 호출되면 그 즉시 key는 selected-key set에서 제거될 것이다. Keys는 다른 방식으로는 절대 selected-key set에서 제거되지 않는다. 다시말해 그들은 절대 selection operations의 부수효과로 제거되지 않는다는 말이다. Keys는 직접적으로 selected-key set에 추가되지 않을 수 도 있다. <- ???

## Selection
각각의 selection 연산을 수행하는 동안 키가 추가/삭제될 수 있다. Selection 연산은 `select()`, `select(long)` and `selectNow()` 메소드 호출에 의해서 수행된다. Selection 연산은 다음과 같은 순서로 수행된다.

1. Cancelled-key set에 존재하는 키들은 cancelled-key set과 각각 속해있던 key set에서부터 제거된다. 그리고 해당 키를 이용해서 등록되었던 채널은 등록 해제된다. 이 단계에서 cancelled-key set은 비워지게 된다.
2. OS는 selection operation이 시작되는 시점에 각각의 남아있는 채널이 자신의 키의 interest set에 의해 식별되는 operation을 수행할 준비가 되었는지 갱신을 위해서 질의받게된다. 채널은 적어도 하나 이상의 operation이 준비되었는지에 따라서 아래 두개의 action 중 하나가 수행된다.
	a. If the channel's key is not already in the selected-key set then it is added to that set and its ready-operation set is modified to identify exactly those operations for which the channel is now reported to be ready. Any readiness information preveiusly recorded in the ready set is discarded.
	1. 만약 채널의 키가 아직 selected-key set에 존재하지 않는다면, 해당 set에 추가되고 ready-operation set 은 수정된다 위해 식별하다 정확하게 해당 operations 위해 어떤 채널이 현재 준비되었다고 보고되었는지. Ready set에 이전에 기록된 준비 정보가 존재한다면 해당 정보는 버려진다.
	2. 혹은 channel의 key가 이미 selected-key set에 존재한다면, 이것의 ready-operation set 은 채널이 보고하는 새로운 operation을 인식할 수 있도록 수정된다. Ready set에 기존에 기록된 준비 정보는 보존된다. (OS에 의해 리턴된 Ready set이 현재 ready set과 bitwise-disjoined 된다.)
if all of the keys in the key set at the start of this step have empty interest sets then neither the selected-key set nor any of the key's ready operation sets will be updated.
3. 만약 step(2)를 수행하는 도중에 cancelled-key set에 key가 추가되면 그들에게 step(1)의 작업이 수행된다.

Whether or not a selection operation blocks to wait for one or more channels to become ready, and if so for how long, is the only essential difference between the three selection methods.

## Concurrency
Selectors are themselves safe for use by multiple concurrent threads; their key sets, however, are not.

The seelction operations synchronize on the selector itself, on the key set, and on the selected-key set, in that order. They also synchronize on the cancelled-key set during steps(1) and (3) above.

Changes made to the interest sets of a selector's keys while a selection operation is in progess have no effect upon that operation; they will be seen by the next selcetion operation.

Keys may be cancelled and channels may be closed at any time. Hence the presence of a key in one or more of a selector's key sets does not imply that the key is valid or that its channel is open. Application code should be acreful to synchronize and check these conditions as necessary if there is any possiblity that another thrtead will cancel a key or close a channel.

A thread blocked in one of the `select()` or `select(long)` methods may be interrupted by some other thread in one of three ways : 
* By invoking the selector's `wakeup` method
* By invoking the selector's `close` method, or
* By invoking the blocked thread's `interrupt` method, in which case its interrupt status will be set and the selector's `wakeup` method will be invoked.

The `close` method synchronizes on the selector and all three key sets in the same order as in a selection operation.

A selcetor's key and selected-key sets are not, in general, safe for use by mulitple concurrent threads. If such a thread might modify one of these sets directly then access should be controlled by synchronzing on the set itself. The iterators returned by these sets' `iterator` methods are fail-fast.: If the set is modified after the iterator is creatd, in any way except by invoking the iterator's own `remove` method, then a `ConcurrentModificationException` will be thrown.
