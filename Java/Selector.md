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

A multiplexor of SelectableChannel objects.

이 클래스의 open 메소드 또는 시스템의 기본 selector provider 가 selector 객체를 생성한다. Custom selector provider에 의해서 생성될 수도 있다. 이 클래스의 close 메소드가 호출되기 전까지 selector는 열려있는 상태로 남아있다.

Selector를 이용한 selectable channel의 등록은 `SelectionKey` 객체에 의해 표현될 수 있다. Selector 객체는 3개의 selection keys sets를 유지한다.

* The **key set** contains the keys representing the current channel registrations of this selector. A selector maintains three sets of selection keys
* The **selected-key set** is the set of keys such that each key's channel was detected to be ready for at least one of the operations identified in the key's interest set during a prior selection operation. This set is returned by the `selectedKeys()` method. The selected-key set is always a subset of the key set.
* The **cancelled-key set** is the set of keys that have been cancelled but whose channels have not yet been deregistered. This set is not directly accessible. The cancelled-key set is always a subset of the key set.

새로 생성된 selector는 비어있는 3개의 key sets 을 갖는다.

A key is added to a selector's **key set** as a side effect of registering a channel via the channel's register method. Cancelled keys are removed from the key set during selection operations. The key set itself is not directly modifiable.

A key is added to its selector's **cancelled-key set** when it it cancelled, whether by closing its channel or by invoking its cancel method. Cancelling a key will cause its channel to be deregistered during the next selection operation, at which time the key will removed from all of the selector's key sets.

Keys are added to the **selected-key set** by selection operations. A key may be removed directly from the selected-key set by invoking the set's remove method or by invoking the `remove` method of an iterator obtained from the set. Keys are never removed from the selected-key set in any other way they ar not, in particular, removed as a side effect of selection operations. Keys may not be added directly to the selected-key set.

## Selection
각각의 selection 연산을 수행하는 동안 키가 추가/삭제될 수 있다. Selection 연산은 `select()`, `select(long)` and `selectNow()` 메소드 호출에 의해서 수행된다. Selection 연산은 다음과 같은 순서로 수행된다.

1. Each key in the cancelled-key set is removed from each key set of which it is a member, and its channel is deregistered. This step leaves the cancelled-key set empty.
2. The underlying operating system is queried for an update as to the readiness of each remaining channel to perform any of the operations identified by its key's interest set as of the moment that the selection operation began. For a channel that is ready for at least one such operation, one of the following two actions is performed.
	a. If the channel's key is not already in the selected-key set then it is added to that set and its ready-operation set is modified to identify exactly those operations for which the channel is now reported to be ready. Any readiness information preveiusly recorded in the ready set is discarded.
	b. Otherwise the channel's key is already in the selected-key set, so its ready-operation set is modified to identify any new oprations for which the channel is reported to be ready. Any readiness information previously recorded in the ready set is preserved; in other words, the ready set returned by the underlying system is bitwise-disjoined into the key's current ready set.
if all of the keys in the key set at the start of this step have empty interest sets then neither the selected-key set nor any of the key's ready operation sets will be updated.
3. If any keys were added to the cancelled-key set while step(2) was in progress then they are processed as in step(1).

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
