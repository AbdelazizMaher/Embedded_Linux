#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>

#define DEV_MEM_SIZE  512

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

static char *pcd_devnode(struct device *dev, umode_t *mode)
{
        if (!mode)
                return NULL;

        *mode = 0222;

        return NULL;
}
static int pcd_open(struct inode *inode, struct file *filp)
{
    // Check if the process is opening the device for writing
    if ((filp->f_flags & O_ACCMODE) == O_WRONLY || (filp->f_flags & O_ACCMODE) == O_RDWR) {
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
    
    // Check if the process is opening the device for writing
    if ((filp->f_flags & O_ACCMODE) == O_WRONLY || (filp->f_flags & O_ACCMODE) == O_RDWR) {
        return -1;        
    }    
    /* 1. Adjust the count */
    if( (count + *f_pos) > DEV_MEM_SIZE)
        count = DEV_MEM_SIZE - *f_pos;

    /* 2. Return error if no data to write */
    if( !count )
        return -ENOMEM;    

    /* 3. Copy data from user ( returns --> (0 on success) */
    if( copy_from_user(&device_buffer[*f_pos],buff,count) )
        return -EFAULT;

    /* 4. Update the current file position */
    *f_pos += count;

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
    /* 1. Dynamically allocate device number region */
    alloc_chrdev_region(&device_number,0,1,"pcd_regions");

    /* 2. Initialize cdev structure with its file operations */
    cdev_init(&pcd_cdev,&pcd_fops);

    /* 3. Register cdev structure with VFS */
    pcd_cdev.owner = THIS_MODULE;
    cdev_add(&pcd_cdev,device_number,1);    

    /* 4. Create device class under sys/class/<class name> */
    pcd_class = class_create(THIS_MODULE,"pcd_class");
    pcd_class->devnode = pcd_devnode;

    /* 5. Create device under sys/class/<class name>/<device name> and populate it with device info */
    pcd_device = device_create(pcd_class,NULL,device_number,NULL,"pcd");

    return 0;
}

static void __exit pcdDriver_EXIT(void)
{
    device_destroy(pcd_class,device_number);
    class_destroy(pcd_class);
    cdev_del(&pcd_cdev);

    /* 4. unregister a range of device numbers */
    unregister_chrdev_region(device_number,1);
    
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Abdelaziz Maher");
MODULE_DESCRIPTION("A pseudo character driver");

module_init(pcdDriver_INIT);
module_exit(pcdDriver_EXIT);

