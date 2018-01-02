# 소프트웨어 개발 Javascript로 시작하기

## 프로그램이 동작한다는것...
우리가 작성하는것은 소스코드. 사람이 읽을 수 있는 형태로 기계가 수행할 명령을 정의해 놓은 문서.  
Javascript의 경우 Javascript engine이 소스코드를 읽고 내용을 분석하여 정의된 명령을 실행함.

## Javascript의 특징
* 웹 브라우저 상에서 동적으로 컨텐츠를 바꾸고, 이미지를 움직이는 등 웹 페이지를 꾸며주는데에 사용됨.
* Node.js라는 환경을 통해서 서버로 사용할 수 있음.
* 명시적인 자료형이 없다...?

## Javascript 개발 환경 설치하기 (Mac)
### Homebrew 설치하기
Homebrew는 macOS 용 패키지 관리자 프로그램이다. 패키지(프로그램) 설치를 편리하게 할 수 있다. 사실은 옛날 프로그래머들한테 편리한 방법인데, 익숙해지면 편하다.
```
$ /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```

### Node 설치하기
Node.js는 Chrome V8 Javascript engine 으로 만들어졌다. Javascript로 서버를 만들 수 있음.
```
$ brew install node
```

## Javascript로 프로그램 만들어보기
### REPL 실행하기
REPL은 Read Eval Print Loop의 줄임말이다. 사용자가 입력하는대로 즉시 결과를 출력하는 환경이다. 간단하게 테스트할 때 유용한 환경.
```
$ node
> console.log('Hello, Javascript!');
Hello, Javascript!
undefined
```
이렇게하면 "Hello, Javascript!"라는 문구를 출력하는 프로그램을 만든것임.

### 작성된 js를 실행시키기
```
$ echo "console.log('Hello JS');" > sayHello.js
$ node sayHello.js
```

### REPL에서 작성된 js 파일을 로드하기
```
$ node
> .load foo.js
```

## 출력
```
> console.log('줄바꿈은 \n입니다.');
줄바꿈은
입니다.
```

```
> console.log('진짜 back-slash는 두번 \\');
진짜 back-slash는 두번 \
> console.log('\\n');
\n
```

## 함수
```
function foo(param) {
    return;
}
```

## 조건문
### 비교 연산자의 종류
- ==
- !=
- <, <=
- \>, >=
- &&
- ||

```
> if (1 == 1) {
...     console.log('true');
... } else {
...     console.log('false');
... }
true
> if (1 == 2) {
...     console.log('true');
... } else {
...     console.log('false');
... }
false
```

## 반복문
### For loop
숫자 0 ~ 9 를 순서대로 출력하는 예제.
```
var n = 10;
for (var i = 0; i < n; i++) {
    console.log(n);
}
```
### While loop
숫자 10 ~ 1 을 순서대로 출력하는 예제.
```
var n = 10;
while (n > 0) {
    console.log(n);
    n--;
}
```

### 문제: 다이아몬드 출력
3보다 크거나 같은 홀수 N이 주어졌을때 다이아몬드 모양을 출력하는 프로그램 작성. 빈공간은 \_ 로 표시, 다이아몬드는 \*로 표시

입력예)
```
3
```
출력예)
```
_*_
***
_*_
```

입력예)
```
5
```
출력예)
```
__*__
_***_
*****
_***_
__*__
```

```javascript
function diamond(n) {
    var half = n / 2;

    var result = '';
    for (var i = 0; i < half; i++) {
        for (var j = 0; j < n; j++) {
            if (half - i - 1 < j && j < half + i) {
                result += '*';
            } else {
                result += '_';
            }
        }
        result += '\n';
    }
    for (var i = half-1; i > 0; i--) {
        for (var j = n-1; j >= 0; j--) {
            if (half - i - 1 < j && j < half + i) {
                result += '*';
            } else {
                result += '_';
            }
        }
        result += '\n';   
    }
    console.log(result.substr(0, result.length-1));
}
```

## Reference
https://developer.mozilla.org/ko/docs/Learn/JavaScript/First_steps/What_is_JavaScript
