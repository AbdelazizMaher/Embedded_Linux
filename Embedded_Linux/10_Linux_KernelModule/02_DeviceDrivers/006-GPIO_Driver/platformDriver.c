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
	int ret;

	int minor_n;
	
	struct platform_device_private_data *plat_data;

	/* 1. find out on which device file open was attempted by the user space */
	minor_n = MINOR(inode->i_rdev);

	/* 2. Get device's private data structure */
	plat_data = container_of(inode->i_cdev,struct platform_device_private_data,cdev);

	/* 3. To supply device private data to other methods of the driver */
	filp->private_data = plat_data;
		
	/* 4. check permission */
	ret = check_permission(plat_data->perm,filp->f_mode);
		
	return ret;
}

ssize_t GPIO_read(struct file *filp, char __user *buff, size_t count, loff_t *f_pos)
{
	return 0;
}

ssize_t GPIO_write(struct file *filp, const char __user *buff, size_t count, loff_t *f_pos)
{  
	struct platform_device_private_data *plat_data = (struct platform_device_private_data*)filp->private_data;

    uint8_t rec_buf[10] = {0};

    if( copy_from_user( rec_buf, buff, count ) > 0)
    {
        return -EFAULT;
    }

	if (rec_buf[0]=='1') 
	{
		/* set the GPIO value to HIGH */
		gpio_set_value(plat_data->PinNumber, 1);
	}
	else if (rec_buf[0]=='0')
	{
		/*set the GPIO value to LOW */
		gpio_set_value(plat_data->PinNumber, 0);
	}
	else 
	{
		pr_err("Unknown command : Please provide either 1 or 0 \n");
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

