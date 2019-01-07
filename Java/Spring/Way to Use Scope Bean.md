# The Way to Use Scope Bean
## Spring Scopes
- Singleton : Only one
- Prototype : Each bean request
- Session : Each session
- Request : Each HTTP request
- Application : Only one also. [similar to singleton?](https://stackoverflow.com/questions/33571259/java-spring-bean-scopes-singleton-vs-application)


## Example
LoginController.java

```java
@RestController
public class LoginController {

    @Autowired
    private LoginUser loginUser;

    @GetMapping("/login")
    public String login() throws Exception {
        // ObjectMapper may be not compatible
        // https://stackoverflow.com/questions/29439528/spring-mvc-scope-proxy-bean-jackson-2
        return new ObjectMapper().writerFor(LoginUser.class).writeValueAsString(loginUser);
    }
}
```

LoginUser.java

```java
@Component
@Scope(value = "request", proxyMode = ScopedProxyMode.TARGET_CLASS)
public class LoginUser {
    private long loggedInTime = System.currentTimeMillis();

    public long getLoggedInTime() {
        return loggedInTime;
    }
}
```
