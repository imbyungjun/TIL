#include "chardev.h"
#include <linux/sched.h>
#include <linux/rcupdate.h>
#include <linux/module.h>   /* Needed by all modules */
#include <linux/kernel.h>   /* Needed for KERN_INFO */
#include <linux/proc_fs.h>
#include <linux/string.h>
#include <linux/vmalloc.h>
#include <asm/uaccess.h>
#include <linux/init.h>
#include <asm/siginfo.h>
#include <linux/signal.h>
#include <linux/sched.h>
#include <linux/rcupdate.h>
#include <linux/string.h>
#include <linux/signal.h>

MODULE_LICENSE("GPL");

#define PROCFS_MAX_SIZE         1024
#define PROCFS_TESTLEVEL        "battery_test"
#define PROCFS_NOTIFYPID        "battery_notify"
#define PROCFS_THRESHOLD        "battery_threshold"

/* Declaration of battery level status */

#define BATTERY_LOW 0x01
#define BATTERY_HIGH 0x02


/* Device */
#define SUCCESS 0
#define BUF_LEN 80
/* Device end */

/* Declaration of variables used in this module */

static int level = 100;			// maximum level of battery.
static int test_level = 0;		// level of battery remain.
static int notify_pid = -1;		// pid for send_sig
static int threshold = -1;		
static int battery_status = 0;

/* End of declaration */

/* Declaration of ancillary variables */
static char test_level_buffer[PROCFS_MAX_SIZE];     
static size_t test_level_buffer_size = 0;    

static char notify_buffer[PROCFS_MAX_SIZE];
static size_t notify_buffer_size = 0;

static char threshold_buffer[PROCFS_MAX_SIZE];
static size_t threshold_buffer_size = 0;

static struct proc_dir_entry *test_level_entry;       
static struct proc_dir_entry *notify_entry;
static struct proc_dir_entry *threshold_entry;

struct task_struct *my_task;
/* End of declaration */

/* Declaration for device */

static int Device_Open = 0;
static char Message[BUF_LEN];
static char *Message_Ptr;

static int device_open(struct inode *inode, struct file *file)
{
    /* Don't let it talk to two processes at the same time */
    if (Device_Open)
        return -EBUSY; 
    Device_Open++;
    
    /* Initialize the message */
    Message_Ptr = Message; 
	try_module_get(THIS_MODULE); 
	return SUCCESS;
}

static int device_release(struct inode *inode, struct file *file) {
    /* Now ready for next caller */
    Device_Open--; 
    module_put(THIS_MODULE);
    return SUCCESS;
}

static ssize_t device_read(struct file *file, char __user * buffer, size_t length, loff_t * offset) 
{
    /* Number of bytes actually written to the buffer */
    int bytes_read = 0;

	snprintf(Message, 10, "%d", test_level);

    if (*Message_Ptr == 0)
            return 0;
    
    /* Put the data into the buffer */
    while (length && *Message_Ptr) {
        put_user(*(Message_Ptr++), buffer++);
        length--;
        bytes_read++;
    }
    
    return bytes_read;
}

long device_ioctl(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param)
{
    int i;
    
    switch (ioctl_num) { 
    case IOCTL_GET_MSG: 
        i = device_read(file, (char *)ioctl_param, 99, 0);
        
        /* Put a zero at the end of the buffer, so it will be properly */
        put_user('\0', (char *)ioctl_param + i);
        break;
    }
    return SUCCESS; 
}

/* End of device */


/*
        Implementation of write function for procfs battery_test
*/
static ssize_t test_level_write( struct file *filp, const char *user_space_buffer, size_t len, loff_t *off )
{

    int status = 0;
    int requested;

    test_level_buffer_size = len;

    if (test_level_buffer_size > PROCFS_MAX_SIZE ) {
        test_level_buffer_size = PROCFS_MAX_SIZE;
    }

    /* write data to the buffer */
    if ( copy_from_user(test_level_buffer, user_space_buffer, test_level_buffer_size) ) {
            return -EFAULT;
    }

    status = kstrtoint(test_level_buffer, 10, &requested);

    if(status < 0)
    {
        printk(KERN_INFO "Error while called kstrtoint(...)\n");
        return -ENOMEM;
    }

    /* level value check */
    if(requested < 0 || requested > level){
        printk(KERN_INFO "Invalid battery level.\n");
        return -ENOMEM;
    }

	/* accept value. */
    test_level = requested;

    /* Find task by pid */
	my_task = pid_task(find_vpid(notify_pid), PIDTYPE_PID);

	/* Send signal to userspace */
	if (test_level <= threshold && battery_status != BATTERY_LOW) {
		battery_status = BATTERY_LOW;
		printk(KERN_INFO "Low battery\n");
		send_sig(SIGUSR1, my_task, 0);
	} else if (test_level > threshold && battery_status != BATTERY_HIGH) {
		battery_status = BATTERY_HIGH;
		printk(KERN_INFO "High battery\n");
		send_sig(SIGUSR2, my_task, 0);
	} else if (test_level >= level) {
		printk(KERN_INFO "Fully charged\n");
	}

    return test_level_buffer_size;
}

/*
        Implementation of write function for procfs battery_notify
*/
static ssize_t notify_write( struct file *filp, const char *user_space_buffer, size_t len, loff_t *off )
{
    int status = 0;
    int requested;

    notify_buffer_size = len;

    if (notify_buffer_size > PROCFS_MAX_SIZE ) {
        notify_buffer_size = PROCFS_MAX_SIZE;
    }

    // write data to the buffer 
    if ( copy_from_user(notify_buffer, user_space_buffer, notify_buffer_size) ) {
		printk(KERN_INFO "Error while called copy_from_user\n");
        return -EFAULT;
    }

    status = kstrtoint(notify_buffer, 10, &requested);

    if(status < 0)
    {
        printk(KERN_INFO "Error while called kstrtoint(...)\n");
        return -ENOMEM;
    }
     
	// accept value.
    notify_pid = requested;

    return notify_buffer_size;
}

/*
        Implementation of write function for procfs battery_threshold
*/
static ssize_t threshold_write( struct file *filp, const char *user_space_buffer, size_t len, loff_t *off )
{

    int status = 0;
    int requested;

    threshold_buffer_size = len;

    if (threshold_buffer_size > PROCFS_MAX_SIZE ) {
        threshold_buffer_size = PROCFS_MAX_SIZE;
    }

    /* write data to the buffer */
    if ( copy_from_user(threshold_buffer, user_space_buffer, threshold_buffer_size) ) {
		printk(KERN_INFO "Error while copy_from_user\n");
        return -EFAULT;
    }

    status  = kstrtoint(threshold_buffer, 10, &requested);

    if(status < 0)
    {
        printk(KERN_INFO "Error while called kstrtoint(...)\n");
        return -ENOMEM;
    }
        
	if (requested < 0 || requested > level) {
		printk(KERN_INFO "Invalid threshold value request\n");
		return -EFAULT;
	}
		
	// accept value.
    threshold = requested;

    return threshold_buffer_size;
}


/*
        Implementation of read function for procfs battery_test
*/
static int test_level_read( struct file *filp, char *user_space_buffer, size_t count, loff_t *off )
{
    int ret = 0;
    int flag = 0;

    if(*off < 0) *off = 0;

    snprintf(test_level_buffer, 10, "%d", test_level);
    test_level_buffer_size = strlen(test_level_buffer);

    if(*off > test_level_buffer_size)
        return -EFAULT;
    else if(*off == test_level_buffer_size)
        return 0;
    
    if(test_level_buffer_size - *off > count)
        ret = count;
    else
        ret = test_level_buffer_size - *off;

    flag = copy_to_user(user_space_buffer, test_level_buffer + (*off), ret);

    if(flag < 0)
        return -EFAULT;

    *off += ret;

    return ret;
}

/*
        Implementation of read function for procfs battery_notify
*/
static int notify_read( struct file *filp, char *user_space_buffer, size_t count, loff_t *off )
{
    int ret = 0;
    int flag = 0;

    if(*off < 0) *off = 0;

    snprintf(notify_buffer, 10, "%d", notify_pid);
    notify_buffer_size = strlen(notify_buffer);

    if(*off > notify_buffer_size)
        return -EFAULT;
    else if(*off == notify_buffer_size)
        return 0;

    if(notify_buffer_size - *off > count)
        ret = count;
    else
        ret = notify_buffer_size - *off;

    flag = copy_to_user(user_space_buffer, notify_buffer + (*off), ret);

    if(flag < 0)
        return -EFAULT;

    *off += ret;

    return ret;
}

/*
        Implementation of read function for procfs battery_threshold
*/
static int threshold_read( struct file *filp, char *user_space_buffer, size_t count, loff_t *off )
{
    int ret = 0;
    int flag = 0;

    if(*off < 0) *off = 0;

    snprintf(threshold_buffer, 10, "%d", threshold);
    threshold_buffer_size = strlen(threshold_buffer);

    if(*off > threshold_buffer_size)
        return -EFAULT;
    else if(*off == threshold_buffer_size)
        return 0;
        

    if(threshold_buffer_size - *off > count)
        ret = count;
    else
        ret = threshold_buffer_size - *off;

    flag = copy_to_user(user_space_buffer, threshold_buffer + (*off), ret);

    if(flag < 0)
        return -EFAULT;

    *off += ret;

    return ret;
}

/*
    Configuration of file_operations

    This structure indicate functions when read or write operation occured.
*/
static const struct file_operations test_level_fops = {
	.write = test_level_write,
    .read = test_level_read,
};

static const struct file_operations notify_fops = {
	.write = notify_write,
	.read = notify_read,
};

static const struct file_operations threshold_fops = {
    .write = threshold_write,
    .read = threshold_read,
};


/* Device file_operations */
struct file_operations chardev_fops = {
    .read = device_read,
    .unlocked_ioctl = device_ioctl,
    .open = device_open,
    .release = device_release, /* close */
};
/* Device end */

/*
    This function will be called on initialization of kernel module
*/
int init_module(void)
{
	int ret = 0;

	printk(KERN_INFO "Battery module initialize\n");

    test_level_entry = proc_create(PROCFS_TESTLEVEL, 0666, NULL, &test_level_fops);
    notify_entry = proc_create(PROCFS_NOTIFYPID, 0666, NULL, &notify_fops);
    threshold_entry = proc_create(PROCFS_THRESHOLD, 0666, NULL, &threshold_fops);

    if(!test_level_entry || !notify_entry || !threshold_entry)
    {
       return -ENOMEM;
    }
	
	/* Regist character device */
    ret = register_chrdev(MAJOR_NUM, DEVICE_FILE_NAME, &chardev_fops);
    
    if (ret < 0) {
        printk(KERN_ALERT "%s failed with %d\n",
        "Registering the character device ", ret); 
        return ret;
    }
    
	printk(KERN_INFO "%s The major device number is %d.\n",
        "Registeration is a success", MAJOR_NUM);
	printk(KERN_INFO "you have to create a device file. \n");
    printk(KERN_INFO "mknod %s c %d 0\n", DEVICE_FILE_NAME, MAJOR_NUM); 
 
	return 0;
}

/*
        This function will be called on cleaning up of kernel module
*/
void cleanup_module(void)
{
	printk(KERN_INFO "Battery module cleanup\n");

	remove_proc_entry(PROCFS_TESTLEVEL, NULL);
	remove_proc_entry(PROCFS_NOTIFYPID, NULL);
	remove_proc_entry(PROCFS_THRESHOLD, NULL);

	/* Unregist character device */
	unregister_chrdev(MAJOR_NUM, DEVICE_FILE_NAME);
}
