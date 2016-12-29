
public class AbstractTest {
	public static void main(String[] args) {
		A b = new B();
		A c = new C();

		System.out.println(b.getStr());
		System.out.println(c.getStr());
	}
}

abstract class A {
	protected static String str;

	public String getStr() {
		return str;
	}

	public void setStr(String str) {
		A.str = str;
	}

}

class B extends A {
	private static String str;

	@Override
	public String getStr() {
		return str;
	}

	@Override
	public void setStr(String str) {
		B.str = str;
	}

	public B() {
		str = "123";
	}
}

class C extends A {
	private static String str;

	public C() {
		str = "abc";
	}

	@Override
	public String getStr() {
		return str;
	}

	@Override
	public void setStr(String str) {
		C.str = str;
	}

}
