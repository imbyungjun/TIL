# This script will configure all of basics settings for me

# Install brew
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"

# Install git
brew install git

# Github configure
git config --global user.name "imbyungjun"
git config --global user.email "20113316@kookmin.ac.kr"

# Install tmux
brew install tmux

# Install tree
brew install tree

# Download bash_profile
curl https://raw.githubusercontent.com/imbyungjun/TIL/master/MacOSX/bash_profile -o ~/.bash_profile

# Download vimrc
curl https://raw.githubusercontent.com/imbyungjun/TIL/master/MacOSX/vimrc -o ~/.vimrc

# Disable dashboard
defaults write com.apple.dashboard mcx-disabled -boolean YES && killall Dock

# Screencapture in folder
mkdir /Users/imb/Desktop/ScreenShots
defaults write com.apple.screencapture location /Users/imb/Desktop/ScreenShots
killall SystemUIServer

# Download icon image
curl https://raw.githubusercontent.com/imbyungjun/TIL/master/MacOSX/ScreenShotsIcon.png -o /tmp/icon.png

# Take an image and make the image its own icon:
sips -i /tmp/icon.png

# Extract the icon to its own resource file:
/Developer/Tools/DeRez -only icns /tmp/icon.png > /tmp/tmp.rsrc

# Append a resource to the folder you want to icon-ize.
Rez -append tmpicns.rsrc -o $'ScreenShots/Icon\r'

# Use the resource to set the icon.
SetFile -a C ScreenShots/

# Hide the Icon\r file from Finder.
SetFile -a V $'ScreenShots/Icon\r'

# clean up.
rm /tmp/tmp.rsrc
