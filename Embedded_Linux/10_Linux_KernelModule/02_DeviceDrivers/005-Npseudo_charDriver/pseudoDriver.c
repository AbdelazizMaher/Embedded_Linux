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

/*Driver private data structure */
struct platform_driver_private_data
{
	int total_devices;
	dev_t device_number;
	struct class *pcd_class;
	struct device *pcd_device;
	struct pcdev_private_data  pcdev_data[NO_OF_DEVICES];
};

struct platform_driver_private_data plat_data;

/* Check permission for opening the device */
int check_permission(int dev_perm, int acc_mode)
{

	if(dev_perm == RDWR)
		return 0;
	
	/* Ensures readonly access */
	if( (dev_perm == RDONLY) && ( (acc_mode & FMODE_READ) && !(acc_mode & FMODE_WRITE) ) )
		return 0;
	
	/* Ensures writeonly access */
	if( (dev_perm == WRONLY) && ( (acc_mode & FMODE_WRITE) && !(acc_mode & FMODE_READ) ) )
		return 0;

	return -EPERM;

}

static int pcd_open(struct inode *inode, struct file *filp)
{   
	int ret;

	int minor_n;
	
	struct pcdev_private_data *pcdev_data;

	/* 1. find out on which device file open was attempted by the user space */
	minor_n = MINOR(inode->i_rdev);

	/* 2. Get device's private data structure */
	pcdev_data = container_of(inode->i_cdev,struct pcdev_private_data,cdev);

	/* 3. To supply device private data to other methods of the driver */
	filp->private_data = pcdev_data;
		
	/* 4. check permission */
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

    uint8_t state = 0;

    count = 1;
    if( copy_to_user(buff, &state, count) > 0)
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

    }
    else if (rec_buf[0]=='0')
    {

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

	/* 1. Dynamically allocate  device numbers */
	alloc_chrdev_region(&plat_data.device_number,0,NO_OF_DEVICES,"gpios");

	/* 2. Create device class under /sys/class/ */
	plat_data.pcd_class = class_create(THIS_MODULE,"GPIO");

	for(i=0;i<NO_OF_DEVICES;i++)
    {
		/* 3. Initialize the cdev structure with fops*/
		cdev_init(&plat_data.pcdev_data[i].cdev,&pcd_fops);

		/* 4. Register a device (cdev structure) with VFS */
		plat_data.pcdev_data[i].cdev.owner = THIS_MODULE;
		cdev_add(&plat_data.pcdev_data[i].cdev,plat_data.device_number+i,1);

		/* 5. populate the sysfs with device information */
		plat_data.pcd_device = device_create(plat_data.pcd_class,NULL,plat_data.device_number+i,NULL,"GPIO-%d",i+22);
	}

    return 0;
}

static void __exit pcdDriver_EXIT(void)
{
	int i;

	for(i=0;i<NO_OF_DEVICES;i++)
    {
		device_destroy(plat_data.pcd_class,plat_data.device_number+i);
		cdev_del(&plat_data.pcdev_data[i].cdev);
	}
	class_destroy(plat_data.pcd_class);

	unregister_chrdev_region(plat_data.device_number,NO_OF_DEVICES);
    
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Abdelaziz Maher");
MODULE_DESCRIPTION("A pseudo character driver");

module_init(pcdDriver_INIT);
module_exit(pcdDriver_EXIT);

