#Partition in Linux with fdisk

Partition allows us seperate some file systems. We can mount the other file system at every branch of the file system.  
Seperating file systems means let them have different i-node numbers. And then, we can attach/dettach file systems to the other.
So if we seperate file system and mount it on the other, we cann't make hard link between different file systems. It's because i-node number is only unique in a file system.


***fdisk*** is the most common command line tool for  partitioning.
	
in Linux, devices(keyboard, monitor, hdd, ...) are abstracted like a file. So we can access to devices by file names in /dev/ directory.

**Primary** partitions can be created up to 4. So the primary partitions have a partition number 1 ~ 4.  
**Logical** partitions have a partition number larger than 4. We can make numerous logical partitions.

If you use HDD, you can access to your HDD in /dev/
	
	hda hdb hdc hdd
	
hda, hdb, hdc, hdd means Hard Disk a ~ d (1 ~ 4).

If you use SD memory, you can access

	mmcblk*
	
	
if you replace dev_name to your disk name, you could start fdisk.

	$ fdisk dev_name
	
Now you can see such like this fdisk prompt.

	Command (m for help):
  	

***fdisk commands***

	m - show fdisk command action's list  
	p - print partition table  
	d - delete partition  
	n - make new partition
	w - save partition table

After you set the file systems, you can cancel the new settings by typing **^C**.  
If you want to save the settings, type command **w** and you should reboot your Linux.
