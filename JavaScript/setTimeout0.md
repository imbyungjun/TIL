# setTimeout(func(), 0)

## setTimeout()
JavaScript에서 `setTimeout()` 함수는 2번째 인자로 주어진 시간만큼 대기 후 1번째 인자로 전달된 함수를 한 번 수행한다. `setInterval()`함수와 함께 기초적인 타이머 함수로 잘 알려져 있다. 그런데 `setTimeout(func(), 0)` 처럼 사용되는 경우가 다수 존재한다.

## setTimeout(func(), 0)
`setTimeout()` 함수의 두번째 인자는 대기시간을 의미한다. 위처럼 사용하였을 경우 0 millisecond를 대기한다는것 즉, 대기하지 않고 즉시 실행한다는 의미를 갖는다. 왜 직접적으로 함수를 호출하지 않고 불필요하게 `setTimeout()` 함수를 사용하여 호출할까?

이유는 브라우저의 멀티테스킹에 있다. 브라우저는 JavaScript를 수행하는 동시에 여러가지 작업들을 수행한다. 이때, JavaScript가 HTML element를 변경하거나 생성할 경우 기대하지 않은 결과를 초래할 수 있다. 

JavaScript가 rendering thread가 완료한 뒤 수행되도록 하기위해서 `setTimeout()`함수를 활용할 수 있다. 0 millisecond를 대기한 후 실행하라는 명령이 즉시 실행하라는 명령처럼 보이지만 실질적으로 `setTimeout()` 함수는 첫 번째 매개변수로 전달된 함수를 non-JavaScript tasks의 수행이 완료된 후 수행한다.

실질적으로 `setTimeout()`함수는 매개변수로 전달된 함수를 execution queue에 re-queue한다.

## Reference
https://stackoverflow.com/questions/779379/why-is-settimeoutfn-0-sometimes-useful
