# Multi-Release JAR Files
**Multi-release JAR Files**는 JAR 파일이 구동되는 JVM version에 맞추어서 다른 자바 바이트 코드를 사용하는 것이다. 하나의 JAR 파일에 각 버전에 맞는 여러 릴리즈를 포함시킬 수 있다.

## 필요성
1. 하위 호환성을 지키는 방법
```
    if (javaVersion >= 9) {
        // JRE 9 이상에서 동작 가능한 코드
    } else {
        // JRE 8 이하에서 동작 가능한 코드 (+ Reflection)
    }
```
상위 버전의 JDK로 하위 버전의 메서드(상위 버전에선 사라진)를 호출하는 코드를 compile하기 위해서는 Reflection을 사용할 수 밖에 없음. 

## 구조
Multi-release JAR 파일은 아래와 같은 구조를 갖는다.
```
JAR_content_root
    |- A.class
    |- B.class
    |- C.class
    |- META-INF
        |- MANIFEST.MF
        |- versions
            |- 9
                |- A.class
                |- B.class
```

JRE 8 이전의 버전은 JAR_content_root/ 디렉토리 하위의 A.class, B.class 그리고 C.class를 기준으로 JAR 파일을 실행할 것이다.  
JRE 9 버전은 versions/9/ 디렉토리 하위의 A.class, B.class 그리고 JAR_content_root/ 디렉토리 하위의 C.class 파일을 기준으로 JAR 파일을 실행할 것이다.

## MANIFEST.MF
MANIFEST.MF 파일에는 해당 JAR 파일이 multi-release 파일이라는것을 명세하는 정보가 추가된다.
```
# MANIFEST.MF sample
Mnifest-Version: 1.0
Created-By: 9.0.1 (Oracle Corporation)
Multi-Release: true
``` 

## Multi-Release JAR 만들기
[참고 링크](http://www.logicbig.com/tutorials/core-java-tutorial/java-9-changes/multi-release-jars/)
```
multi-release-jar $ tree
.
├── META-INF
│   └── MANIFEST.MF
├── for-jre-8
│   ├── Echo.java
│   ├── Main.java
│   └── out
└── for-jre-9
    ├── Echo.java
    └── out

multi-release-jar $ jar cvf my-lib.jar -C for-jre-8/out . --release 9 -C for-jre-9/out .
```

## Maven을 이용한 Multi-release JAR 만들기
현재 Maven을 이용해서 Mutli-release JAR 파일을 생성하는 방법은 정형화된 형식이나 플러그인이 없다.  
### 적용해 볼 만한 방법들
- Maven을 이용해서 target/META-INF/version/9 디렉토리에 JRE 9 전용 자바 바이트 코드를 넣고 JAR 파일을 생성하기  
JRE 9 전용 클래스가 자주 수정되지 않는다면 한번 생성한 자바 바이트 코드를 재사용해서 간단함
- [IDE에서 Maven을 이용한 프로젝트 구성](https://github.com/hboutemy/maven-jep238)

> [관련 자료](https://events.static.linuxfound.org/sites/events/files/slides/Java9%20and%20the%20impact%20on%20Maven%20projects.pdf) 22페이지 `JEP 238: Multi-Release JAR Files`
