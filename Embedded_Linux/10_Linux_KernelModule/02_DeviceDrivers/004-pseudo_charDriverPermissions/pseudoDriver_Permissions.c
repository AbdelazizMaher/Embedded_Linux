#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>

#define DEV_MEM_SIZE  512

/* Global write function's file position  */
loff_t f_pos_g;

/* pseudo device memory */
char device_buffer[DEV_MEM_SIZE];

/* uint32 holds the driver device number(major + minor) */
dev_t device_number;

/* character device structure */
struct cdev pcd_cdev;

/* pointer to class (higher-level view of a device that abstracts out low-level implementation details) structure */
struct class *pcd_class;

/* pointer to device (contains the informations that the device model core needs to model the system) structure */
struct device *pcd_device;

/* Function to set device node permissions */
static char *pcd_devnode(struct device *dev, umode_t *mode)
{
        if (!mode)
                return NULL;

        *mode = 0777;

        return NULL;
}

static int pcd_open(struct inode *inode, struct file *filp)
{
    /* Check if the process is opening the device for writing */
    if ((filp->f_flags & O_ACCMODE) == O_WRONLY || (filp->f_flags & O_ACCMODE) == O_RDWR)
    {
        return -1;       
    }

    return 0;   
}

static int pcd_release(struct inode *device_file, struct file *instance)
{   
    return 0;
}

ssize_t pcd_read(struct file *filp, char __user *buff, size_t count, loff_t *f_pos)
{
    /* 1. Adjust the count */
    if( (count + *f_pos) > DEV_MEM_SIZE)
        count = DEV_MEM_SIZE - *f_pos;

    /* 2. Copy data to user ( returns --> (0 on success) or (number of bytes that couldn't be read) */
    if( copy_to_user(buff,&device_buffer[*f_pos],count) )
        return -EFAULT;

    /* 3. Update the current file position */
    *f_pos += count;

    /* 4. return number of bytes read */
    return count;  
}

ssize_t pcd_write(struct file *filp, const char __user *buff, size_t count, loff_t *f_pos)
{
    /* 1. Adjust the count */
    if( (count + *f_pos) > DEV_MEM_SIZE)
        count = DEV_MEM_SIZE - *f_pos;

    /* 2. Return error if no data to write */
    if( !count )
        return -ENOMEM;    

    /* 3. If appending, move the file pointer to the end else reset the device for new write */
    if (filp->f_flags & O_APPEND)
        *f_pos = f_pos_g;
    else
        memset(device_buffer,0,DEV_MEM_SIZE);    

    /* 4. Copy data from user ( returns --> (0 on success) */
    if( copy_from_user(&device_buffer[*f_pos],buff,count) )
        return -EFAULT;

    /* 5. Update the current file position */  
    *f_pos += count;
    f_pos_g = *f_pos;

    /* 5. return number of bytes wriiten */
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

    /* 1. Dynamically allocate device number region */
    ret = alloc_chrdev_region(&device_number,0,1,"pcd_regions");
	if(ret < 0)
    {
		pr_err("Alloc chrdev numbers failed\n");
		goto alloc_fail;
	}

    /* 2. Initialize cdev structure with its file operations */
    cdev_init(&pcd_cdev,&pcd_fops);

    /* 3. Register cdev structure with VFS */
    pcd_cdev.owner = THIS_MODULE;
    ret = cdev_add(&pcd_cdev,device_number,1);  
	if(ret < 0)
    {
		pr_err("Cdev addition failed\n");
		goto cdev_fail;
	}      

    /* 4. Create device class under sys/class/<class name> */
    pcd_class = class_create(THIS_MODULE,"pcd_class");
	if(IS_ERR(pcd_class)) /*ERR_PTR() on error*/
    {
		pr_err("Class creation failed\n");
        /* Convert pointer to error code(int)*/
		ret = PTR_ERR(pcd_class);
		goto class_fail;
	} 

    /* Set device node permissions */
    pcd_class->devnode = pcd_devnode;
   
    /* 5. Create device under sys/class/<class name>/<device name> and populate it with device info */
    pcd_device = device_create(pcd_class,NULL,device_number,NULL,"pcd");
	if(IS_ERR(pcd_device)) /*ERR_PTR() on error*/
    {
		pr_err("Device creation failed\n");
        /* Convert pointer to error code(int)*/
		ret = PTR_ERR(pcd_device);
		goto device_fail;
	}

    return 0;

device_fail:
	class_destroy(pcd_class);
class_fail:
	cdev_del(&pcd_cdev);	
cdev_fail:
	unregister_chrdev_region(device_number,1);
alloc_fail:
	printk("Module insertion failed\n");

	return ret;
}

static void __exit pcdDriver_EXIT(void)
{
    /* 1. Remove device */
    device_destroy(pcd_class,device_number);

    /* 2. Destroy class */
    class_destroy(pcd_class);

    /* 3. Delete cdev */
    cdev_del(&pcd_cdev);

    /* 4. unregister a range of device numbers */
    unregister_chrdev_region(device_number,1);       
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Abdelaziz Maher");
MODULE_DESCRIPTION("A pseudo character driver");

module_init(pcdDriver_INIT);
module_exit(pcdDriver_EXIT);

