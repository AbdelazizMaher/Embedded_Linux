#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>


#define NO_OF_DEVICES   2

/*permission codes */
#define RDONLY          0x01
#define WRONLY          0X10
#define RDWR            0x11

/*Device private data structure */

struct pcdev_private_data
{
	unsigned int GPIO_Number;
	int perm;
	struct cdev cdev;
};


struct platform_driver_private_data
{
	int total_devices;
	dev_t device_number;
	struct class *pcd_class;
	struct device *pcd_device;
	struct pcdev_private_data  pcdev_data[NO_OF_DEVICES];
};

struct platform_driver_private_data platform_data;


static char *pcd_devnode(struct device *dev, umode_t *mode)
{
        if (!mode)
                return NULL;

        *mode = 0777;

        return NULL;
}


int check_permission(int dev_perm, int acc_mode)
{

	if(dev_perm == RDWR)
		return 0;
	
	//ensures readonly access
	if( (dev_perm == RDONLY) && ( (acc_mode & FMODE_READ) && !(acc_mode & FMODE_WRITE) ) )
		return 0;
	
	//ensures writeonly access
	if( (dev_perm == WRONLY) && ( (acc_mode & FMODE_WRITE) && !(acc_mode & FMODE_READ) ) )
		return 0;

	return -EPERM;

}

static int pcd_open(struct inode *inode, struct file *filp)
{   
	int ret;

	int minor_n;
	
	struct pcdev_private_data *pcdev_data;

	/*find out on which device file open was attempted by the user space */
	minor_n = MINOR(inode->i_rdev);

	/*get device's private data structure */
	pcdev_data = container_of(inode->i_cdev,struct pcdev_private_data,cdev);

	/*to supply device private data to other methods of the driver */
	filp->private_data = pcdev_data;
		
	/*check permission */
	ret = check_permission(pcdev_data->perm,filp->f_mode);

	return ret;  
}

static int pcd_release(struct inode *device_file, struct file *instance)
{
    
    return 0;
}

ssize_t pcd_read(struct file *filp, char __user *buff, size_t count, loff_t *f_pos)
{
    struct pcdev_private_data *pcdev_data = (struct pcdev_private_data*)filp->private_data;

    uint8_t gpio_state = 0;

    gpio_state = gpio_get_value(GPIO_22);

    count = 1;
    if( copy_to_user(buff, &gpio_state, count) > 0)
    {
        return -EFAULT;
    }

    return 0;  
}

ssize_t pcd_write(struct file *filp, const char __user *buff, size_t count, loff_t *f_pos)
{   
    uint8_t rec_buf[10] = {0};

    if( copy_from_user( rec_buf, buff, count ) > 0)
    {
        return -EFAULT;
    }

    if (rec_buf[0]=='1')
    {
        //set the GPIO value to HIGH
        gpio_set_value(GPIO_23, 1);
    }
    else if (rec_buf[0]=='0')
    {
        //set the GPIO value to LOW
        gpio_set_value(GPIO_23, 0);
    } 
    else
    {

    }

    return count; 
}


/* file operations of the pseudo driver */
struct file_operations pcd_fops = 
{
    .owner = THIS_MODULE,
    .open = pcd_open,
    .release = pcd_release,
    .read = pcd_read,
    .write = pcd_write,
};

static int __init pcdDriver_INIT(void)
{
	int ret;
	int i;

	/*Dynamically allocate  device numbers */
	alloc_chrdev_region(&pcdrv_data.device_number,0,NO_OF_DEVICES,"gpios");

	/*create device class under /sys/class/ */
	pcdrv_data.pcd_class = class_create(THIS_MODULE,"GPIO");

	for(i=0;i<NO_OF_DEVICES;i++)
    {
		/*Initialize the cdev structure with fops*/
		cdev_init(&pcdrv_data.pcdev_data[i].cdev,&pcd_fops);

		/*  Register a device (cdev structure) with VFS */
		pcdrv_data.pcdev_data[i].cdev.owner = THIS_MODULE;
		cdev_add(&pcdrv_data.pcdev_data[i].cdev,pcdrv_data.device_number+i,1);

		/*populate the sysfs with device information */
		pcdrv_data.pcd_device = device_create(pcdrv_data.pcd_class,NULL,pcdrv_data.device_number+i,NULL,"GPIO-%d",i+22);
	}

        //Checking the GPIO is valid or not
    if(gpio_is_valid(GPIO_22) == false)
    {
        gpio_free(GPIO_22);
    }

    //Requesting the GPIO
    if(gpio_request(GPIO_22,"GPIO_22") < 0)
    {
        gpio_free(GPIO_22);
    }

       //Checking the GPIO is valid or not
    if(gpio_is_valid(GPIO_23) == false)
    {
        gpio_free(GPIO_23);
    }

    //Requesting the GPIO
    if(gpio_request(GPIO_23,"GPIO_23") < 0)
    {
        gpio_free(GPIO_23);
    }
  
    //configure the GPIO as output
    gpio_direction_output(GPIO_23, 0);

    gpio_direction_input(GPIO_22);

    return 0;
}

static void __exit pcdDriver_EXIT(void)
{
	int i;

	for(i=0;i<NO_OF_DEVICES;i++)
    {
		device_destroy(pcdrv_data.pcd_class,pcdrv_data.device_number+i);
		cdev_del(&pcdrv_data.pcdev_data[i].cdev);
	}
	class_destroy(pcdrv_data.pcd_class);

	unregister_chrdev_region(pcdrv_data.device_number,NO_OF_DEVICES);
    
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Abdelaziz Maher");
MODULE_DESCRIPTION("A pseudo character driver");

module_init(pcdDriver_INIT);
module_exit(pcdDriver_EXIT);

