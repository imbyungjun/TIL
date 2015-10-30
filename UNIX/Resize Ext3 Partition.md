#How to resize ext3 partition
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