#include "platform.h"



void LEDdev_release(struct device *dev)
{
	pr_info("Device released \n");
}



struct platform_device_private_data  LED_prv_data[] = {
	[0] = {.Direction = OUTPUT, .perm = WRONLY, .OutMode = GPIO_PIN_MODE_OUTPUT_PP, .Value = 0},
	[1] = {.Direction = OUTPUT, .perm = WRONLY, .OutMode = GPIO_PIN_MODE_OUTPUT_PP, .Value = 0},
	[2] = {.Direction = OUTPUT, .perm = WRONLY, .OutMode = GPIO_PIN_MODE_OUTPUT_PP, .Value = 0},
};



struct platform_device platform_LEDdev_1 = {
	.name = "GREEN_LED",
	.id = 0,
	.dev = {
		.platform_data = &LED_prv_data[0],
		.release = LEDdev_release
	}
};


struct platform_device platform_LEDdev_2 = {
	.name = "BLUE_LED",
	.id = 1,
	.dev = {
		.platform_data = &LED_prv_data[1],
		.release = LEDdev_release
	}
};


struct platform_device platform_LEDdev_3 = {
	.name = "RED_LED",
	.id = 2,
	.dev = {
		.platform_data = &LED_prv_data[2],
		.release = LEDdev_release
	}
};


static int __init LED_init(void)
{
	int ret;
	
	ret = platform_device_register(&platform_LEDdev_1);
    if (ret) {
        pr_err("Failed to register platform_LEDdev_1\n");
        return ret;
    }

	ret = platform_device_register(&platform_LEDdev_2);
    if (ret) {
        pr_err("Failed to register platform_LEDdev_1\n");
        return ret;
    }

	ret = platform_device_register(&platform_LEDdev_3);
    if (ret) {
        pr_err("Failed to register platform_LEDdev_1\n");
        return ret;
    }	

	pr_info("Device setup module loaded \n");

	return 0;
}


static void __exit LED_exit(void)
{

	platform_device_unregister(&platform_LEDdev_1);
	platform_device_unregister(&platform_LEDdev_2);
	platform_device_unregister(&platform_LEDdev_3);

	pr_info("Device setup module unloaded \n");
}

module_init(LED_init);
module_exit(LED_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Abdelaziz Maher");
MODULE_DESCRIPTION("A led driver");