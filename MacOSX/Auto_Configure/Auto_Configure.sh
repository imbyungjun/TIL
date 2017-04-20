#!/bin/bash
# This script will configure all of basic settings for me

# You must install command line tools first.
# $ xcode-select --install

### Install Brew, the package manager for MacOSX ###
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"


### Install basic utilities ###

# Install git
brew install git

# Set up git configure for Github
git config --global user.name "imbyungjun"
git config --global user.email "20113316@kookmin.ac.kr"

# Check git configurations
git config --list

# Install tmux
brew install tmux

# Install tree
brew install tree

# Install bash-completion
brew install bash-completion

# Install grip
brew install grip

# Install Maven3
brew install maven

### End of installing basic utilies ###


### Download and apply configuration files ###

# Download bash_profile
curl https://raw.githubusercontent.com/imbyungjun/TIL/master/MacOSX/Auto_Configure/bash_profile -o ~/.bash_profile

# Download vimrc
curl https://raw.githubusercontent.com/imbyungjun/TIL/master/MacOSX/Auto_Configure/vimrc -o ~/.vimrc

# Download inputrc
curl https://raw.githubusercontent.com/imbyungjun/TIL/master/MacOSX/Auto_Configure/inputrc -o ~/.inputrc

### End of downloading and applying configuration files ###


### Disable dashboard ###
defaults write com.apple.dashboard mcx-disabled -boolean YES && killall Dock


### Set up screen capture directory ###
# Make screen capture directory
mkdir /Users/imb/Desktop/ScreenShots

# Change default location for screen capture
defaults write com.apple.screencapture location ~/Desktop/ScreenShots

# Reset SystemUIServer
killall SystemUIServer

# Download screen capture direcotry icon image
curl https://raw.githubusercontent.com/imbyungjun/TIL/master/MacOSX/Auto_Configure/ScreenShotsIcon.png -o /tmp/icon.png

# Take an image and make the image its own icon:
sips -i /tmp/icon.png

# Extract the icon to its own resource file:
DeRez -only icns /tmp/icon.png > /tmp/tmp.rsrc

# Append a resource to the screen capture folder
Rez -append /tmp/tmp.rsrc -o $'/Users/imb/Desktop/ScreenShots/Icon\r'

# Use the resource to set the icon.
SetFile -a C /Users/imb/Desktop/ScreenShots/

# Hide the Icon\r file from Finder.
SetFile -a V $'/Users/imb/Desktop/ScreenShots/Icon\r'

# clean up.
rm /tmp/tmp.rsrc /tmp/icon.png

### End of setting up screen capture directory ###
