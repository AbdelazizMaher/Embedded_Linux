#include "platform.h"

#define NO_OF_DEVICES   3

struct platform_device_id GPIO_devicesIDs[] =
{
    [GREEN_LED] = {
        .name = "GREEN_LED",
		.driver_data = GREEN_LED,
    },
    [BLUE_LED] = {
        .name = "BLUE_LED",
		.driver_data = BLUE_LED, 
    },
    [RED_LED] = {
        .name = "RED_LED",
		.driver_data = RED_LED, 
    },
    { }
};

struct platform_driver_private_data GPIO_prvdata;

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


static int GPIO_open(struct inode *inode, struct file *filp)
{
	return 0;
}

ssize_t GPIO_read(struct file *filp, char __user *buff, size_t count, loff_t *f_pos)
{
	return 0;
}

ssize_t GPIO_write(struct file *filp, const char __user *buff, size_t count, loff_t *f_pos)
{   
    uint8_t rec_buf[10] = {0};

    if( copy_from_user( rec_buf, buff, count ) > 0)
    {
        return -EFAULT;
    }

    return count; 
}


struct file_operations GPIO_fops = 
{
    .owner = THIS_MODULE,
    .open  = GPIO_open,
    .read  = GPIO_read,
    .write = GPIO_write,
};

int GPIO_remove(struct platform_device *pdev)
{
	struct platform_device_private_data *pdata;

	pdata = (struct platform_device_private_data*)dev_get_platdata(&pdev->dev);	
	if(!pdata)
	{
		dev_info(&pdev->dev,"No platform data available\n");
		return -EINVAL;
	}	

	/*1. Remove a device that was created with device_create() */
	device_destroy(GPIO_prvdata.GPIO_class,GPIO_prvdata.device_number +  pdev->id);
	
	/*2. Remove a cdev entry from the system*/
	cdev_del(&pdata->cdev);

	pr_info("A device is removed\n");

	return 0;
}


ssize_t show_direction(struct device *dev, struct device_attribute *attr,char *buf)
{
	struct platform_device_private_data *pdata = (struct platform_device_private_data*)dev_get_platdata(dev->parent);
<<<<<<< HEAD
    if (!pdata)
	{
=======
        if (!pdata) {
>>>>>>> 1f41b054863ca71b51c813e000e4712909d09fae
        pr_err("Platform data is NULL\n");
        return -EINVAL;
        }

    return sprintf(buf, "%d\n", pdata->Direction);
}

ssize_t show_outmode(struct device *dev, struct device_attribute *attr,char *buf)
{
	struct platform_device_private_data *pdata = (struct platform_device_private_data*)dev_get_platdata(dev->parent);
    if (!pdata)
	{
        pr_err("Platform data is NULL\n");
        return -EINVAL;
    }

	return sprintf(buf,"%d\n",pdata->OutMode);
}

ssize_t store_outmode(struct device *dev, struct device_attribute *attr,const char *buf, size_t count)
{
	return 0;
}

ssize_t show_value(struct device *dev, struct device_attribute *attr,char *buf)
{
	struct platform_device_private_data *pdata = (struct platform_device_private_data*)dev_get_platdata(dev->parent);
<<<<<<< HEAD
    if (!pdata)
	{
=======
        if (!pdata) {
>>>>>>> 1f41b054863ca71b51c813e000e4712909d09fae
        pr_err("Platform data is NULL\n");
        return -EINVAL;
        }

    pdata->Value = gpio_get_value(pdata->PinNumber);

	return sprintf(buf,"%d\n",pdata->Value);
}

ssize_t store_value(struct device *dev, struct device_attribute *attr,const char *buf, size_t count)
{		
	int ret;

	struct platform_device_private_data *pdata = (struct platform_device_private_data*)dev_get_platdata(dev->parent);
    if (!pdata) 
	{
        pr_err("Platform data is NULL\n");
        return -EINVAL;
    }

	ret = kstrtol(buf,0,(long *)&pdata->Value);
	if(ret)
		return ret;
	
	gpio_set_value(pdata->PinNumber,pdata->Value);

	return count;
}

static DEVICE_ATTR(Direction,S_IRUGO,show_direction,NULL);
static DEVICE_ATTR(OutMode,S_IRUGO|S_IWUSR,show_outmode,store_outmode);
static DEVICE_ATTR(Value,S_IRUGO|S_IWUSR,show_value,store_value);


int GPIO_sysfs_create_files(struct device *GPIO_device)
{
	int ret;

	ret = sysfs_create_file(&GPIO_device->kobj,&dev_attr_Direction.attr);
	if(ret)
		return ret;

	ret = sysfs_create_file(&GPIO_device->kobj,&dev_attr_OutMode.attr);
	if(ret)
		return ret;	

	ret = sysfs_create_file(&GPIO_device->kobj,&dev_attr_Value.attr);
	if(ret)
		return ret;

	return ret;
}

int GPIO_probe(struct platform_device *pdev)
{ 
	int ret;

	struct platform_device_private_data *pdata;

	pr_info("A device is detected\n");

	pdata = (struct platform_device_private_data*)dev_get_platdata(&pdev->dev);	
	if(!pdata)
	{
		dev_info(&pdev->dev,"No platform data available\n");
		return -EINVAL;
	}


	dev_set_drvdata(&pdev->dev,pdata);

    cdev_init(&pdata->cdev,&GPIO_fops);

    pdata->cdev.owner = THIS_MODULE;
    ret = cdev_add(&pdata->cdev,GPIO_prvdata.device_number + pdev->id,1);
	if(ret < 0)
	{
		dev_err(&pdev->dev,"Cdev add failed\n");
		return ret;
	}  

    GPIO_prvdata.GPIO_device = device_create(GPIO_prvdata.GPIO_class,&pdev->dev,GPIO_prvdata.device_number +  pdev->id,NULL,"LED-%d",pdev->id); 
	if(IS_ERR(GPIO_prvdata.GPIO_device))
	{
		dev_err(&pdev->dev,"Device create failed\n");
		ret = PTR_ERR(GPIO_prvdata.GPIO_device);
		cdev_del(&pdata->cdev);
		return ret;
		
	}
	
	ret = GPIO_sysfs_create_files(GPIO_prvdata.GPIO_device);
	if(ret)
	{
		device_destroy(GPIO_prvdata.GPIO_class,GPIO_prvdata.device_number +  pdev->id);
		return ret;
	}			       

	switch(pdev->id)
	{
	case GREEN_LED:
        {
		/* Checking the GPIO is valid or not*/
		if(gpio_is_valid(GPIO_22) == false)
		{
			gpio_free(GPIO_22);
		}
	
		/*Requesting the GPIO*/
		if(gpio_request(GPIO_22,"GPIO_22") < 0)
		{
			gpio_free(GPIO_22);
		} 
		/*configure the GPIO as output*/
    	        gpio_direction_output(GPIO_22, 0);

		pdata->PinNumber = GPIO_22;

		break;
	}
	case BLUE_LED:
       {
		/* Checking the GPIO is valid or not*/
		if(gpio_is_valid(GPIO_23) == false)
		{
			gpio_free(GPIO_23);
		}
	
		/*Requesting the GPIO*/
		if(gpio_request(GPIO_23,"GPIO_23") < 0)
		{
			gpio_free(GPIO_23);
		} 
		/*configure the GPIO as output*/
    	        gpio_direction_output(GPIO_23, 0);

		pdata->PinNumber = GPIO_23;

		break;
	}
	case RED_LED:
        {
		/* Checking the GPIO is valid or not*/
		if(gpio_is_valid(GPIO_25) == false)
		{
			gpio_free(GPIO_25);
		}
	
		/*Requesting the GPIO*/
		if(gpio_request(GPIO_25,"GPIO_25") < 0)
		{
			gpio_free(GPIO_25);
		} 
		/*configure the GPIO as output*/
    	        gpio_direction_output(GPIO_25, 0);

		pdata->PinNumber = GPIO_25;

		break;		
	}	
	}
	pr_info("Probe was successful\n");	

    return 0;
}

struct platform_driver GPIO_driver =
{
	.probe = GPIO_probe,
	.remove = GPIO_remove,
	.id_table = GPIO_devicesIDs,
	.driver = {
		.name = "GPIO_driver"
	},    
};

static int __init GPIOdriver_INIT(void)
{
	int ret;

	ret = alloc_chrdev_region(&GPIO_prvdata.device_number,0,NO_OF_DEVICES,"GPIOdevices_region");
	if(ret < 0)
	{
		pr_err("Alloc chrdev failed\n");
		return ret;
	}

	GPIO_prvdata.GPIO_class = class_create(THIS_MODULE,"GPIO_class");
	if(IS_ERR(GPIO_prvdata.GPIO_class))
	{
		pr_err("Class creation failed\n");
		ret = PTR_ERR(GPIO_prvdata.GPIO_class);
		unregister_chrdev_region(GPIO_prvdata.device_number,NO_OF_DEVICES);
		return ret;
	}

    platform_driver_register(&GPIO_driver);
	
	pr_info("GPIO platform driver loaded\n");

    return 0;
}

static void __exit GPIOdriver_EXIT(void)
{
	platform_driver_unregister(&GPIO_driver);

	class_destroy(GPIO_prvdata.GPIO_class);

	unregister_chrdev_region(GPIO_prvdata.device_number,NO_OF_DEVICES);
    
	pr_info("pcd platform driver unloaded\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Abdelaziz Maher");
MODULE_DESCRIPTION("A gpio driver");

module_init(GPIOdriver_INIT);
module_exit(GPIOdriver_EXIT);

