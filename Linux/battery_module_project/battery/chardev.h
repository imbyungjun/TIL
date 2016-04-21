/*
 * chardev.h 
 *
 * Header file for device
 */
#ifndef CHARDEV_H
#define CHARDEV_H
#include <linux/ioctl.h>

/* The major device number */
#define MAJOR_NUM 100

/* Get the message of the device driver */
#define IOCTL_GET_MSG _IOR(MAJOR_NUM, 1, char *) 

/* Name of the device file */
#define DEVICE_FILE_NAME "/dev/char_dev"
#endif
