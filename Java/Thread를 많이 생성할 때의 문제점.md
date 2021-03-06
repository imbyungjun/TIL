# Thread를 많이 생성할 때의 문제점
- **스레드 라이프 사이클**  
스레드를 생성하고 제거하는 작업에도 자원이 소모된다. 스레드에 소모되는 자원은 시스템마다 다르지만 만약 스레드가 수행할 작업이 간단하고 자주 요청된다면 매 요청마다 새로운 스레드를 생성하는 일이 상대적으로 전체 작업에서 많은 부분을 차지할 수 있다.

- **자원 낭비**  
실행 중인 스레드는 메모리를 차지한다. CPU의 갯수보다 많은 수의 스레드가 만들어져 동작 중이라면, 시레졸는 대부분의 스레드가 대기(Idle) 상태에 머무른다. 대기 상태로 남아있는 스레드가 많아짐에 따라서 많은 메모리를 필요로 하게되고, 가비지 컬렉터에 가해지는 부하가 늘어날 뿐만 아니라 CPU를 사용하기 위해 여러 스레드가 경쟁하는 구도가 되어 메모리 이외에도 많은 자원을 소모한다.

- **안정성 문제**  
모든 시스템에는 생성할 수 있는 스레드의 개수가 제한되어 있다. 몇 개 까지 만들 수 있는지는 플랫폼과 운영체제마다 다르고, JVM을 실행할 때 지정하는 인자나 Thread 클래스에 필요한 스택의 크기에 따라서 달라지기도 한다. 만약 제한된 양을 모두 사용하고 나면 아마도 OutOfMemoryError가 발생한다. OutOfMemoryError가 발생한 상황에서 해당하는 오류를 바로잡을 수 있는 방법은 별로 없으며, 가능하다해도 안정적으로 처리하기 힘들다. 결국 프로그램이 제한된 값 안에서 동작하도록 작성하여 OutOfMemoryError가 발생하지 않도록 미연에 방지하는것이 훨씬 쉽다.
