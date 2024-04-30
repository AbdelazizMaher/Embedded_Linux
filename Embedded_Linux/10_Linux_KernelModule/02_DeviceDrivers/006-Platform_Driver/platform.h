#ifndef PLATFORM_H
#define PLATFORM_H

#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/platform_device.h>
#include <linux/sysfs.h>
#include <linux/gpio.h>

#undef pr_fmt
#define pr_fmt(fmt) "%s : " fmt,__func__

/*permission codes */
#define RDONLY          0x01
#define WRONLY          0X10
#define RDWR            0x11

enum platform_dev_names
{
	GREEN_LED = 0,
	BLUE_LED,
	RED_LED
};

enum GPIO_Direction
{
	OUTPUT = 0,
	INPUT,
};

enum GPIO_OutMode
{
	GPIO_PIN_MODE_OUTPUT_PP = 0,
	GPIO_PIN_MODE_OUTPUT_OD,
};

struct platform_device_private_data
{
	char* Direction;
    char* OutMode;
	int Value;
	int perm;
	struct cdev cdev;
};


struct platform_driver_private_data
{
	int total_devices;
	dev_t device_number;
	struct class *GPIO_class;
	struct device *GPIO_device;
};

struct GPIO_attr
{

};

#endif