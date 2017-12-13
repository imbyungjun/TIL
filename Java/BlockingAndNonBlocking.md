# Blocking and Nonblocking
소켓의 동작 방식은 블로킹 모드와 논블로킹 모드로 나뉜다. 블로킹은 요청한 작업이 성공하거나 에러가 발생하기 전까지는 응답을 돌려주지 않는 것을 말하며 논블로킹은 요청한 작업의 성공 여부와 상관없이 바로 결과를 돌려주는 것을 말한다. 이때 요청의 응답값에 의해서 에러나 성공 여부를 판단한다.

## Blocking
자바에서 블로킹 소켓은 **ServerSocket**, **Socket** 클래스로 구현되어있다.

**Blocking 모드의 서버**
```java
public class BlockingServer {
	public static void main(String[] args) throws Exception {
		BlockingServer server = new BlockingServer();
		server.run();
	}

	private void run() throws IOException {
		ServerSocket server = new ServerSocket(8888);
		System.out.println("Waiting for client...");

		while (true) {
			Socket sock = server.accept();
			System.out.println("Client is connected");

			OutputStream out = sock.getOutputStream();
			InputStream in = sock.getInputStream();

			while (true) {
				try {
					int request = in.read();
					out.write(request);
				} catch (IOException e) {
					System.out.println("Client is disconnected");
					break;
				}
			}
		}
	}
}
```
1. 클라이언트가 서버로 연결 요청을 보내면 서버는 연결을 수락하고 클라이언트와 연결된 소켓을 새로 생성하는데 이때 해당 메서드의 처리가 완료되기 전까지 스레드의 블로킹이 발생한다.
2. 클라이언트가 연결된 소켓을 통해서 서버로 데이터를 전송하면 서버는 read 메서드를 호출하고 이 메서드의 처리가 완료되기 전까지 스레드가 블로킹된다.
3. 클라이언트 또한 서버에서 클라이언트로 전송한 데이터를 읽기 위한 메서드에서 블로킹이 발생한다.

블로킹 소켓은 데이터 입출력에서 스레드의 블로킹이 발생하기 때문에 동시에 여러 클라이언트에 대한 처리가 불가능하게 된다. 다중 클라이언트의 접속 처리를 하지 못하는 문제점을 해결하기 위해서 등장한 모델은 연결된 클라이언트별로 각각 스레드를 할당하는 방법이다. 

```
클라이언트1 -|           |- 스레드1
클라이언트2 -|- 서버 소켓 -|- 스레드2
클라이언트3 -|           |- 스레드3
```

위와 같은 구조에서는 서버 소켓은 각 스레드에게 처리를 넘기기 때문에 다음 클라이언트에 대한 연결을 수행할 수 있다. 여기서 서버 소켓의 accept 메서드가 병목구간이다. ServerSocket 클래스의 accept 메서드는 블로킹 모드로 동작하기 때문에 여러 클라이언트가 동시에 접속을 요청하는 경우에는 대기시간이 길어질 수 밖에 없다. 스레드가 증가하면 Out Of Memory 오류가 발생할 수 있기에 스레드 풀링을 사용하기도 한다. 스레드 풀링을 사용할 경우 동시 접속 가능한 사용자 수가 스레드 풀에 지정된 최대 스레드 수에 의존하는 현상이 발생한다. **동시 접속 수를 늘리기 위해서 스레드 풀의 크기를 자바 힙이 허용하는 최대 한도에 도달할 때까지 늘리는 것이 합당한지 두 가지 관점에서 생각해 볼 필요가 있다.**

첫번째, 자바의 가비지 컬랙션. 자바 프로세스의 힙 사이즈를 크게 잡을 경우 프로세스가 동작하면서 가비지 컬랙션의 대상이 되는 객체 수가 늘어나게 되고 가비지 컬랙션이 동작하게된다. 이때 자바 프로세스는 가비지 컬랙셔능ㄹ 완료하기 위해서 다른 스레드를 멈추게 되는데, 그러면 애플리케이션이 먹통이 된 것처럼 보이게 된다. 힙 크기가 크면 클수록 가비지 컬랙션에 드는 시간이 길어진다. **즉, 힙 크기와 생성 가능한 스레드 수는 비례한다. 힙에 할당된 메모리가 크면 클수록 가비지 컬랙션이 수행되는 횟수는 줄어들지만 수행시간은 상대적으로 길어진다.**

두번째, 컨텍스트 스위칭. 수많은 스레드를 생성할 경우 각 스레드가 CPU 자원을 얻기 위해서 경쟁하면서 CPU 자원을 소모하기 때문에 실제로 작업에 사용되는 CPU 시간은 줄어들게 된다.

결국 블로킹 소켓의 동작 방식으로 인하여 블로킹 소켓을 사용한 서버는 충분히 많은 동시접속 사용자를 수용하지 못한다. 이런 단점을 개선한 방식이 논블로킹  소켓 방식이다.

## 논블로킹 소켓
자바에서 논블로킹 소켓은 **ServerSocketChannel**, **SocketChannel** 클래스로 구현되어있다.
```java
public class NonBlockingServer {
	private Map<SocketChannel, List<byte[]>> keepDataTrack = new HashMap<>();
	private ByteBuffer buffer = ByteBuffer.allocate(2 * 1024);

	private void startEchoServer() {
		try (
			Selector selector = Selector.open();
			ServerSocketChannel serverSocketChannel = ServerSocketChannel.open() ) {

			if (serverSocketChannel.isOpen() && selector.isOpen()) {
				serverSocketChannel.configureBlocking(false);
				serverSocketChannel.bind(new InetSocketAddress(8888));

				serverSocketChannel.register(selector, SelectionKey.OP_ACCEPT);
				System.out.println("Waiting for clients ...");

				while (true) {
					selector.select();
					Iterator<SelectionKey> keys = selector.selectedKeys().iterator();

					while (keys.hasNext()) {
						SelectionKey key = (SelectionKey) keys.next();
						keys.remove();

						if (key.isValid() == false) {
							continue;
						}

						if (key.isAcceptable()) {
							acceptOP(key, selector);
						} else if (key.isReadable()) {
							readOP(key);
						} else if (key.isWritable()) {
							writeOP(key);
						} else {
							System.out.println("Fail to create ServerSocket");
						}
					}
				}
			}
		} catch (IOException e) {
			System.out.println(e);
		}
	}

	private void acceptOP(SelectionKey key, Selector selector) throws IOException {
		ServerSocketChannel serverSocketChannel = (ServerSocketChannel) key.channel();
		SocketChannel socketChannel = serverSocketChannel.accept();
		socketChannel.configureBlocking(false);

		System.out.println("Client is connected : " + socketChannel.getRemoteAddress());

		keepDataTrack.put(socketChannel, new ArrayList<byte[]>());
		socketChannel.register(selector, SelectionKey.OP_READ);
	}

	private void readOP(SelectionKey key) {
		try {
			SocketChannel socketChannel = (SocketChannel) key.channel();
			buffer.clear();
			int numRead = -1;

			try {
				numRead = socketChannel.read(buffer);
			} catch (IOException e) {
				System.out.println("읽기 에러");
			}

			if (numRead > -1) {
				byte[] data = new byte[numRead];
				System.arraycopy(buffer.array(), 0, data, 0, numRead);
				System.out.println(new String(data, "UTF-8") + " from " + socketChannel.getRemoteAddress());
				doEchoJob(key, data);
			} else {
				keepDataTrack.remove(socketChannel);
				System.out.println("클라이언트 종료 : " + socketChannel.getRemoteAddress());
				socketChannel.close();
				key.cancel();
			}
		} catch (IOException e) {
			System.out.println(e);
		}
	}

	private void writeOP(SelectionKey key) throws IOException {
		SocketChannel socketChannel = (SocketChannel) key.channel();

		List<byte[]> channelData = keepDataTrack.get(socketChannel);
		Iterator<byte[]> its = channelData.iterator();

		while (its.hasNext()) {
			byte[] it = its.next();
			its.remove();
			socketChannel.write(ByteBuffer.wrap(it));
		}

		key.interestOps(SelectionKey.OP_READ);
	}

	private void doEchoJob(SelectionKey key, byte[] data) {
		SocketChannel socketChannel = (SocketChannel) key.channel();
		List<byte[]> channelData = keepDataTrack.get(socketChannel);
		channelData.add(data);

		key.interestOps(SelectionKey.OP_WRITE);
	}

	public static void main(String[] args) {
		NonBlockingServer server = new NonBlockingServer();
		server.startEchoServer();
	}
}
```
