#Partition - 2
-
**Environment**  

* Raspberry Pi (version 1)
* Raspbian-wheezy
* 8GB SD card

After installing raspbian, default partition setting is like this..

	$ df -h
	Filesystem		Size	Used	Avail	Use%	Mounted on
	rootfs			2.9G	2.4GB	335M	88%		/
	/dev/root		2.9G	2.4GB	335M	88%		/
	devtmpfs		214M	0		214M	0%		/dev
	tmpfs			44M		236K	44M		1%		/run/
	tmpfs			5.0M	0		5.0M	0%		/run/lock
	tmpfs			88M		0		88M		0%		/run/shm
	/dev/mmcblk0p1	56M		19M		37M		34%		/boot
	
#Let's make partition!

	$ sudo fdisk /dev/mmcblk0

	Command (m for help): p

	Disk /dev/mmcblk0: 7884 MB, 7884242944 bytes
	4 heads, 16 sectors/track, 240608 cylinders, total 15398912 sectors
	Units = sectors of 1 * 512 = 512 bytes
	Sector size (logical/phisical): 512 bytes / 512 bytes
	I/O size (minimum/optimal): 512 bytes /512 bytes
	Disk identifier: 0xa6202af7
	
		Device Boot		Start		End		Blocks	Id	System
	/dev/mmcblk0p1		 8192	 122879		 57344	 c	W95 FAT32 (LBA)
	/dev/mmcblk0p2		122880	6399999	   3138560	83	Linux

	Command (m for help): n
	Partition type:
		p	primary (2 primary, 0 extended, 2 free)
		e	extended
	Select (defualt p): p
	Partition number (1-4, default 3): 3
	Frist sector (2048 - 15398911, default 2048): 6400000
	Last sector, +sectors or +size{K,M,G} (6400000-15398911, default 15398911): 12399999
	
	Command (m for help): p
	
	Disk /dev/mmcblk0: 7884 MB, 7884242944 bytes
	4 heads, 16 sectors/track, 240608 cylinders, total 15398912 sectors
	Units = sectors of 1 * 512 = 512 bytes
	Sector size (logical/phisical): 512 bytes / 512 bytes
	I/O size (minimum/optimal): 512 bytes /512 bytes
	Disk identifier: 0xa6202af7
	
		Device Boot		Start			End		Blocks	Id	System
	/dev/mmcblk0p1		 8192	 	  122879	57344	 c	W95 FAT32 (LBA)
	/dev/mmcblk0p2		122880		 6399999	3138560	83	Linux
	/dev/mmcblk0p3		6400000		12399999	3000000	83	Linux

	Command (m for help): w
	
	$ sudo reboot
	
	
**-- Sector must be continuous, so if you select first sector to 2048, you can select last sector up to 8191. (partition1 is start at 8192)**

Let's mount the new filesystem into original filesystem.

	$ sudo mount /dev/mmcblk0p3 /home/
	mount: you must specify the filesystem type

It doesn't work....

#Format the partition 

	$ mkfs
	Usage: mkfs [-V] [-t fstype] [fs-options] device [size]

Let's make the partition to ext2 type.

	$ mkfs -t ext2 /dev/mmcblk0p3
	
It is same with
	
	$ mkfs.ext2 /dev/mmcblk0p3
	
After some mkfs informations showing up, it done.


#Let's mount the new filesystem.

	$ sudo mount /dev/mmcblk0p3 /home/

If you want to unmount the filesystem.

	$ sudo umount /home/
	
It works but, I don't know yet if it correctly works.

#If you can't umount directory.
(when "device is busy" occured)

	$ fuser -ck /your/mounted/dir
	
This command kills all processes that using the directory.