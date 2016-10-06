#ADB Install on Mac OS X

#Android Debug Bridge (ADB)
 ADB is a command line tool that allows us to connect to android device.

#Install
1. Using [homebrew](http://brew.sh/)
1) Install homebrew
```
$ ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```
2) Install adb
```
$ bew install android-platform-tools
```
3) Check connection
```
$ adb devices
```

2. Manually
1) Download Mac SDK Tools from Android developer site ["Get just the command line tools"](https://developer.android.com/studio/index.html#mac-tools)

2) Unzip the tools
```
$ Unzip android-sdk*.zip
```

3) Move them to proper path that you won't accidentally delete them
```
$ mv android-sdk-macosx/ ~/.android/sdk
```

4) Run the SDK Manager
```
$ sh ~/.android/sdk/tools/android
```

5) Uncheck everything but `Android SDK Platform-tools` or check 

6) Click `Install Packages`, accpec licenses, click `Install`

7) Add path setting for `platform-tools`
```
$ echo 'export PATH=$PATH:~/.android/sdk/platform-tools' >> ~/.bash_profile
```

8) Refresh bash_profile
```
$ source ~/.bash_profile
```

9) Check connection
```
$ adb devices
```
