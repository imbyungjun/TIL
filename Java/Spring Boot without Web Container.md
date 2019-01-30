# Spring Boot without Web Container

스프링 부트 프레임워크를 웹 컨테이너 없이 사용하여 DI 컨테이너의 용도로 사용하는 예제입니다.

## WebApplicationType
`SpringApplication`은 기본적으로 웹 프로젝트인지 판단하여 WebApplicationType을 설정하고 그에 따른 ApplicationContext를 생성합니다. Web container 설정이 필요 없음을 명시적으로 설정하기 위해서 아래와 같이 `SpringApplication`을 인스턴스화하고 설정을 변경합니다.

```java
@SpringBootApplication
public class SpringContainerApplication {
    public static void main(String[] args) {
        SpringApplication application = new SpringApplication(SpringContainerApplication.class);
        application.setWebApplicationType(WebApplicationType.NONE);
        application.run(args);
    }
}
```

## ApplicationRunner
위에서 작성한 웹 컨테이너 설정을 제외한 스프링 애플리케이션을 실행시켜보면, 정상적으로 실행된 뒤 바로 종료하게 됩니다. 웹 컨테이너가 없기 때문에 루프를 돌면서 대기하는 스레드가 없기 때문입니다. `ApplicationRunner`를 이용해서 애플리케이션의 메인 루프를 추가합니다.

```java
@Component
public class MyRunner implements ApplicationRunner {

    @Override
    public void run(ApplicationArguments args) throws Exception {
        while (true) {
            // do something...
        }
    }

}
```

## Dependency Injection
이제 정상적으로 `@Autowired` 애노테이션과 `@Value` 애노테이션을 이용한 DI가 가능함을 확인할 수 있습니다.

**application.properties**
```
my.string=hello
```

**MyService.java**
```java
@Service
public class MyService {

    public String getValue() {
        return "without web container";
    }

}
```

**MyRunner.java**
```java
@Component
public class MyRunner implements ApplicationRunner {

    @Value("${my.string}")
    String myString;

    @Autowired
    MyService myService;

    @Override
    public void run(ApplicationArguments args) throws Exception {
        while (true) {
            System.out.println(myString);
            System.out.println(myService.getValue());

            SECONDS.sleep(1);
        }
    }

}
```

**결과**
```
  .   ____          _            __ _ _
 /\\ / ___'_ __ _ _(_)_ __  __ _ \ \ \ \
( ( )\___ | '_ | '_| | '_ \/ _` | \ \ \ \
 \\/  ___)| |_)| | | | | || (_| |  ) ) ) )
  '  |____| .__|_| |_|_| |_\__, | / / / /
 =========|_|==============|___/=/_/_/_/
 :: Spring Boot ::        (v2.1.2.RELEASE)

2019-01-30 14:37:31.912  INFO 79476 --- [           main] c.e.s.SpringContainerApplication         : Starting SpringContainerApplication on imb.local with PID 79476 (/Users/imb/IdeaProjects/spring-container/target/classes started by imb in /Users/imb/IdeaProjects/spring-container)
2019-01-30 14:37:31.918  INFO 79476 --- [           main] c.e.s.SpringContainerApplication         : No active profile set, falling back to default profiles: default
2019-01-30 14:37:32.499  INFO 79476 --- [           main] c.e.s.SpringContainerApplication         : Started SpringContainerApplication in 0.861 seconds (JVM running for 1.492)
hello
without web container
hello
without web container
hello
...
```

