#Raspbian install in Mac OS
-
* Your SD card must be formatted in FAT32.
* Open terminal, and run
* 
		$ diskutil list
then, identify the disk(not partition) of your SD card. (ex. disk4)

* Unmount your SD card

		$ diskutil unmountDisk /dev/disk# (your disk number)
		
* Copy the data to your SD card

		$ sudo dd bs=1m if=2015-05-05-raspbian-wheezy.img of=/dev/disk# (disk# from diskutil)
		
* This will take a few minutes, you can check progress by sending SIGINFO (pressing Ctrl+T).