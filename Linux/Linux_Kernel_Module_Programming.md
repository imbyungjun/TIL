#Linux_Kernel_Module_Programming
##Environment
\- Raspberry pi 2  
\- Raspbian Jessie

##Common Preparations
####gcc version check
gcc version used for compling kernel  

```
$ cat /proc/version
Linux version 4.1.18-v7+ (dc4@dc4-XPS13-9333) (gcc version 4.9.3 (crosstool-NG crosstool-ng-1.22.0-88-g8460611) ) #846 SMP Thu Feb 25 14:22:53 GMT 2016
```
Current gcc version

```
$ gcc --version | grep gcc
gcc (Raspbian 4.7.3-11+rpi1) 4.7.3
```

####Match the gcc version
1) add apt-get repository

```
$ sudo vi /etc/apt/source.list.d/jessie.list
```
and add following lines     

```
deb http://mirrordirector.raspbian.org/raspbian/ jessie main contrib non-free rpi
```

2) package update

```
$ sudo apt-get update
```

3) install

```
$ sudo apt-get install -y gcc-4.9 g++-4.9
```

4) set up gcc version priority

```
$ sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.7 20
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.9 50
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.7 20
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.9 50
```

5) gcc version check

```
$ gcc --version | grep gcc
gcc (Raspbian 4.9.2-10) 4.9.2
```
---
###Way 1. Get linux-headers
1) download linux-headers  
[Download page](https://www.niksula.hut.fi/~mhiienka/Rpi/linux-headers-rpi/) **(you must download exactly same version)**  

```
$ cat /proc/version
Linux version 4.1.18-v7+ (dc4@dc4-XPS13-9333) (gcc version 4.9.3 (crosstool-NG crosstool-ng-1.22.0-88-g8460611) ) #846 SMP Thu Feb 25 14:22:53 GMT 2016
```
In this case, download version 4.1.18-v7+  

```
$ wget https://www.niksula.hut.fi/~mhiienka/Rpi/linux-headers-rpi/linux-headers-4.1.18-v7%2B_4.1.18-v7%2B-2_armhf.deb
```
2) install package

```
$ sudo dpkg -i linux-headers-4.1.18-v7%2B_4.1.18-v7%2B-2_armhf.deb
```

---
###Way 2. Using Rpi-source
1) Install [rpi-source](https://github.com/notro/rpi-source/wiki)

```
sudo wget https://raw.githubusercontent.com/notro/rpi-source/master/rpi-source -O /usr/bin/rpi-source && sudo chmod +x /usr/bin/rpi-source && /usr/bin/rpi-source -q --tag-update
```
2) Update raspberrypi

```
$ rpi-update
```
then, your Linux version will be updated.

3) Run rpi-source

```
$ rpi-source
```
