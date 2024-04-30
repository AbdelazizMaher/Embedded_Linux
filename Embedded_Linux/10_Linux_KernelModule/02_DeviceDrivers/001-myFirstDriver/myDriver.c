#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("your name");
MODULE_DESCRIPTION("print anything");

static int __init myDriver_INIT(void)
{
    printk("INIT DRIVER FUNCTION\n");

    return 0;
}

static void __exit myDriver_EXIT(void)
{
    printk("BYE...BYE!!!\n");
}

module_init(myDriver_INIT);
module_exit(myDriver_EXIT);

