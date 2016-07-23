#ADB commands
###1. Check connection
```
$adb devices
List of devices attached
BABABEEFBABABEEF	device
```

###2. Stop current working application
```
$ adb shell am force-stop com.example.app
```

###3. Input command to device
1) input back button

```
$ adb shell input keyevent 4
```

2) input touch event at the point (x, y)

```
$ adb shell tap x y
```


###4. Install an application
```
$ adb install example.apk
```

###5. Capture a snapshot
```
adb shell screencap -p /mnt/sdcard/capture.png
adb pull /mnt/sdcard/sc.png
```
