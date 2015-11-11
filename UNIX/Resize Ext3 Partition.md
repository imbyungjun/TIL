#How to resize ext3 partition

#Resize partition

	$ fdisk /dev/mmcblk0
	
	Command (m for help): p
	Disk /dev/mmcblk0: 7948 MB, 7948206080 bytes
	4 heads, 16 sectors/track, 242560 cylinders, total 15523840 sectors
	Units = sectors of 1 * 512 = 512 bytes
	Sector size (logical/physical): 512 bytes / 512 bytes
	I/O size (minimum/optimal): 512 bytes / 512 bytes
	Disk identifier: 0xa6202af7

	        Device Boot      Start         End      Blocks   Id  System
	/dev/mmcblk0p1            8192      122879       57344    c  W95 FAT32 (LBA)
	/dev/mmcblk0p2          122880     6399999     3138560   83  Linux
	/dev/mmcblk0p3         7800000    15523839     3861920   83  Linux

	Command (m for help): d   
	Partition number (1-4): 2

	Command (m for help): n
	Partition type:
	   p   primary (2 primary, 0 extended, 2 free)
	   e   extended
	Select (default p): p
	Partition number (1-4, default 2): 2
	First sector (2048-15523839, default 2048): 122880
	Last sector, +sectors or +size{K,M,G} (122880-7799999, default 7799999): 
	Using default value 7799999

	Command (m for help): p

	Disk /dev/mmcblk0: 7948 MB, 7948206080 bytes
	4 heads, 16 sectors/track, 242560 cylinders, total 15523840 sectors
	Units = sectors of 1 * 512 = 512 bytes
	Sector size (logical/physical): 512 bytes / 512 bytes
	I/O size (minimum/optimal): 512 bytes / 512 bytes
	Disk identifier: 0xa6202af7

	        Device Boot      Start         End      Blocks   Id  System
	/dev/mmcblk0p1            8192      122879       57344    c  W95 FAT32 (LBA)
	/dev/mmcblk0p2          122880     7799999     3838560   83  Linux
	/dev/mmcblk0p3         7800000    15523839     3861920   83  Linux

	Command (m for help): w
	The partition table has been altered!

	Calling ioctl() to re-read partition table.

	WARNING: Re-reading the partition table failed with error 16: Device or resource busy.
	The kernel still uses the old table. The new table will be used at
	the next reboot or after you run partprobe(8) or kpartx(8)
	Syncing disks.

	$ sudo reboot

-

#resize2fs
reszke2fs command allow us to resize mounted ext2/ext3/ext4  file systems.  
First, check device id. 
		
	$ df -h
	Filesystem		Size	Used	Avail	Use%	Mounted on
	rootfs			7.2G	2.6G	4.3G	38%		/
	/dev/root		7.2G	2.6G	4.3G	38%		/
	devtmpfs		214M	   0	214M	0%		/dev
	tmpfs			44M		240K	44M		1%		/run
	tmpfs			5.0M	   0	5.0M	0%		/run/lock
	tmpfs			88M		   0	88M		0%		/run/shm
	/dev/mmcblk0p1	56M		19M		37M		34%		/boot

Just type your device id to argument.
	
	$ resize2fs /dev/root [size_you_want]
	
-
This is manual information of **resize2fs**

**Name**
	
	resize2fs - ext2/ext3/ext4 file system resizer
	
**Options**

	-f Forces resize2fs to proceed with the filesystem resize operation, 
		overriding some safety checks which resize2fs normally enforces.
	-F Flush the filesystem device's buffer cahces before beginning. 
		Only really useful for doing resize2fs time trials.
	-M Shrink the filesystem to the minimum size.
	-p Prints out a percentage completion bars for each resize2fs 
		operation, so that the user can keep track of what the program is doing.
	-P Print the minimum size of the filesystem and exit.
	
-
Since my raspbian died during practice, today my practice was terminated here.
