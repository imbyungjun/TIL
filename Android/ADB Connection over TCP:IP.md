#ADB Connection over TCP/IP

```
$ adb tcpip 5555
restarting in TCP mode port: 5555
```

Find android device's IP address : Settings -> About tablet -> Status -> IP address.

```
$ adb connect 000.000.000.000
connected to 000.000.000.000:5555
```

[Related Link](http://developer.android.com/tools/help/adb.html#wireless)