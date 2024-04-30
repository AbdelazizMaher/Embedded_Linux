#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("your name");
MODULE_DESCRIPTION("print anything");

/* This function is called when the module is loaded */
static int __init myDriver_INIT(void)
{
    /* Print a message to the kernel log */
    printk("INIT DRIVER FUNCTION\n");

    /* Return 0 to indicate success */
    return 0;
}

static void __exit myDriver_EXIT(void)
{
    printk("BYE...BYE!!!\n");
}

/* Register the module initialization and exit functions */
module_init(myDriver_INIT);
module_exit(myDriver_EXIT);

