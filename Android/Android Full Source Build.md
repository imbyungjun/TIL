# Android Full Source Build
Android의 전체 소스코드를 다운받아서 빌드하는 방법을 기록합니다. **안드로이드 M 버전 기준**

## 빌드 요구 사항
### 하드웨어
* 여유 저장 공간 250GB를 권장하고 있다.
* 가상 머신의 Linux 환경에서 빌드하고자 한다면 최소 16GB의 메모리와 swap메모리를 권장하고 있다.

### 소프트웨어
#### OS
Ubuntu 14.04 LTS
#### JDK
Marshmallow 버전의 빌드를 위해서는 OpenJDK 7버전을 필요로한다. 아래의 명령어를 입력해서 설치한다.
```
$ apt-get install openjdk-7-jdk
```
Java 환경 변수 설정 (~/.bashrc 파일에 아래 내용 추가)
```
export JAVA_HOME=/usr/lib/jvm/java-7-openjdk-amd64
ecport ANDROID_JAVA_HOME=$JAVA_HOME
```
환경 변수 갱신
```
$ source ~/.bashrc
```
#### Python
Python 2.6 - 2.7 버전을 설치한다.
```
$ apt-get install python2.7
```
#### GNU Make
GNU Make 3.81 - 3.82 버전을 설치한다.
```
$ wget http://ftp.gnu.org/gnu/make/make-3.82.tar.gz
$ tar -zxvf make-3.82.tar.gz
$ cd make-3.82/
$ ./configure
$ ./build.sh
$ mv make /usr/local/bin/
$ cd ..
$ rm -rf make-3.82/ make-3.82.tar.gz
```
#### Git
Git 1.7 이상 버전을 설치한다.
```
$ apt-get install git
```
#### Device binaries
필요한지모르겠다
#### 기타 패키지들
```
$ apt-get install git-core gnupg flex bison gperf build-essential zip curl zlib1g-dev gcc-multilib g++-multilib libc6-dev-i386 lib32ncurses5-dev x11proto-core-dev libx11-dev lib32z-dev ccache libgl1-mesa-dev libxml2-utils xsltproc unzip
```

### 빌드 환경 최적화
#### ccache 설정
이게 뭔지는 잘 몰르것음.. 본인은 생략했다.
```
export USE_CCACHE=1
prebuilts/misc/linux-x86/ccache/ccache -M 50G
```

## 빌드
#### Repo Tool 다운 및 설정
```
$ wget http://commondatastorage.googleapis.com/git-repo-downloads/repo -O /usr/local/bin/repo
$ chmod +x /usr/local/bin/repo
```

#### Git 설정
```
$ git config --global user.email "im@byungjun.me"
$ git config --global user.name "imbyungjun"
```

#### Android 소스 다운
```
$ repo init -u https://android.googlesource.com/platform/manifest -b android-6.0.1_r81
$ repo sync -j2
```
sync 중 다음과 같은 에러가 발생할 경우 이어받기
```
.. error: Exited sync due to fetch errors
$ repo sync -f
```

#### Android 명령셋 등록
```
$ source build/envsetup.sh
```

#### Build
```
$ make -j2
```

## Reference
http://thdev.net/498

https://source.android.com/source/
