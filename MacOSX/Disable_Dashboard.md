#Disable Dashboard on Mac OS X
###You can simply disable dashboard following way.

## - Open Terminal and paste this.
```
defaults write com.apple.dashboard mcx-disabled -boolean YES && killall Dock
```

## - To enable dashboard, use this.
```
defaults write com.apple.dashboard mcx-disabled -boolean NO && killall Dock

```