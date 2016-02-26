#Screencapture in folder
###Launch Terminal and use following syntax
```
defaults write com.apple.screencapture location /path/to/save
```
###To have the changes take effect, type this
```
killall SystemUIServer
```

####Example
```
defaults write com.apple.screencapture location ~/Desktop/ScreenShots/
```

