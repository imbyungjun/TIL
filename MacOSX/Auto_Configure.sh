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

