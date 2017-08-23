# Switch 문을 회피하는 방법
switch 문은 작게 만들기 어렵다. switch 문은 N가지를 처리하므로 한가지 작업만 수행한다는 원칙에 위반한다. switch 문을 완전히 피할 방법은 없다. 하지만 각 switch 문을 저차원 클래스에 숨기고 절대로 반복하지 않는 방법은 있다. Polymorphism을 활용.

```
public byte[] getScreenBuffer(DeviceConnection conn) throws InvalidOSType {
    switch (conn.getOS()) {
        case OSType.ANDROID:
            return getAndroidScreenBuffer(conn);
        case OSType.IOS:
            return getIOSScreenBuffer(conn);
        default:
            throw new InvalidOSType(conn.getOS());
    }
}
```
위 함수의 문제점은

* 함수가 길다. 새로운 타입이 추가될 경우 더욱 길어질 것이다.
* 한 가지 작업만 수행하지 않는다. Swith 문을 사용하는 경우 어쩔 수 없는 부분이다.
* SRP를 위반한다. 코드를 변경할 이유가 여럿이기 때문이다.
* OCP를 위반한다. 새로운 타입을 추가할 때마다 코드를 변경하기 때문이다.
* **프로젝트내에 위와 같은 switch 분기가 수없이 많이 존재할 것이다.**

switch 문을 추상 팩토리에 숨겨서 보이지 않게하여 해결한 예시이다. 팩토리는 switch 문을 사용해서 OS type에 적합한 DeviceController 파생 클래스의 인스턴스를 생성한다. 

```
public abstract class DeviceController {
    public abstract boolean isReady();
    public abstract byte[] getScreenBuffer();
    public abstract void reboot();
}
```
```
public interface DeviceControllerFactory {
    public DeviceController createDeviceController(DeviceController controller) throws InvalidOSType;
}
```
```
public class DeviceControllerFactoryImpl implements DeviceControllerFactory {
    public DeviceController createDeviceController(DeviceConnection conn) throws InvalidOSType {
        switch (conn.getOS()) {
            case OSType.ANDROID:
                return new AndroidController(conn);
            case OSType.IOS:
                return new IOSController(conn);
            default:
                throw new InvalidOSType(conn.getOS());
        }
    }
}
```
> [G23] If/Else 혹은 Switch/Case 문보다 다형성을 사용하라.

예외상황은 존재하지만 다형적 객체를 생성하는 부분 이외에는 Switch case의 사용을 지양하는것이 좋다.
