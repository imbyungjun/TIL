# How to Use Runtime exec 
Java에서 command line 명령을 수행하기 위한 방법으로 Runtime.exec() 메서드가 존재한다. 매우 간단하게 child process를 생성하여 command line 명령을 수행할 수 있는것 처럼 보이지만 내부 수행 방식을 모른 채 사용할 경우 오류를 발생시키기 쉽다.

Windows 환경에서 아래와 같은 코드를 수행시켰을때 프로그램이 영원히 종료되지 않을 수 있다.

```java
Process p = Runtime.getRuntime().exec("myCommand");
p.waitFor();
```

지극히 정상적인 코드로 보이는 위 코드에서 오류가 발생하는 원인은 JVM과 external OS process 사이의 커뮤니케이션 방식에 있다. 정확하게 말하면 **Communication buffer** 때문에 오류가 발생한다. Runtime.exec() 메서드를 이용해서 실행시킨 프로그램이 정상적으로 종료하기 위해서는 해당 프로세스의 STDERR과 STDOUT이 반드시 flush되어야한다. 만약 System OS process의 buffer가 가득 찰 경우 process는 JVM이 buffer를 비울때까지 대기하게되고 JVM이 buffer를 비우지 않는다면 영원히 대기하게된다.

STDERR과 STDOUT을 flush하는 일은 매우 간단하지만 이 두 개의 작업은 병렬적으로 이루어져야 한다. 만약 STDOUT을 전부 읽으면서 STDERR를 읽지 않을 경우, STDERR의 출력이 OS process의 buffer를 가득 채워서 프로그램이 영원히 종료하지 않는 상황에 빠질 수 있다. 

## Sample Code
```java
public void run() {
    try {
        Process process = Runtime.getRuntime().exec(commandArray);

        // Runtime.exec()로 생성한 child process의 STDERR과 STDOUT은 반드시 flush 되어야함.
        Thread inputStreamFlushThread = new Thread(() -> flushStream(process.getInputStream()));
        Thread errorStreamFlushThread = new Thread(() -> flushStream(process.getErrorStream()));
		
        inputStreamFlushThread.start();
        errorStreamFlushThread.start();
		
        process.waitFor();
    } catch (IOException | InterruptedException e) {
        log.error("{}", e);
    }
}

private void flushStream(InputStream inputStream) {
    try (InputStreamReader inputStreamReader = new InputStreamReader(inputStream, UTF_8);
         BufferedReader reader = new BufferedReader(inputStreamReader)) {
        reader.lines().forEach(line -> {});
    } catch (IOException e) {
        log.error("Error occurred during flushing child process stream");
    }
}
```

## 또 다른 문제점
Android Debug Bridge version 1.0.39 환경에서 실험한 결과 Runtime.exec() 메서드로 ADB push / pull 기능을 -p 옵션으로 실행하는 프로세스를 생성하면 프로세스의 출력 결과가 일정시간이 지난 이후에 한번에 출력되는 현상이 발생한다. 특정 상황에서 STDOUT buffer가 가득 차길 기다린 후에 출력되는 현상으로 추정된다. [비슷한 사례](https://www.java-forums.org/advanced-java/28815-slow-output-reading-runtime-getruntime-exec.html)를 보면 C++의 endl 문자와 관련되었을 가능성이 있는데, 이것을 해결하고자 줄바꿈 문자를 바꿔서 ADB를 다시 빌드하는것은 너무 많은 시간을 소비한다.

[ADB 파일 전송 출력 소스코드](https://github.com/aosp-mirror/platform_system_core/blob/9ee373ac2c2327e6b44fc9c303b4753dc04d67da/adb/client/file_sync_client.cpp)를 보면 [line_printer.cpp](https://android.googlesource.com/platform/system/core/+/brillo-m7-dev/adb/line_printer.cpp)에 정의된 방식으로 전송 진행상황을 출력하고 있음을 알 수 있고 출력을 위해서 **\n** 문자와 **\r** 문자를 이용한다는 것을 알 수 있다.

### file\_sybc\_client.cpp
```cpp
void ReportProgress(LinePrinter& lp, const std::string& file, uint64_t file_copied_bytes, uint64_t file_total_bytes) {
    ...
    output = android::base::StringPrintf("[%4s] %s", overall_percentage_str, file.c_str());
    lp.Print(output, LinePrinter::LineType::INFO);
}
```

### line\_printer.cpp
```cpp
void LinePrinter::Print(string to_print, LineType type) {
    if (console_locked_) {
        ...
        return;
    }
    if (smart_terminal_) {
        printf("\r");  // Print over previous line, if any.
        // On Windows, calling a C library function writing to stdout also handles
        // pausing the executable when the "Pause" key or Ctrl-S is pressed.
    }
    if (smart_terminal_ && type == ELIDE) {
        ...
    } else {
        printf("%s\n", to_print.c_str());
    }
}
```

## Reference
https://bjurr.com/runtime-exec-hangs-a-complete-solution/

https://stackoverflow.com/questions/13008526/runtime-getruntime-execcmd-hanging
