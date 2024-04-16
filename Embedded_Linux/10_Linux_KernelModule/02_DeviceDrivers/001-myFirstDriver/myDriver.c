/* Header Section */

// Required for all kernel modules
#include <linux/module.h>
// Required for __init and __exit macros  
#include <linux/init.h>   

/* Module description Section */

// Module license
MODULE_LICENSE("GPL");
// Module author                   
MODULE_AUTHOR("your name");   
// Module description          
MODULE_DESCRIPTION("print anything");   

/* Code Section */ 

// Initialization function
static int __init myDriver_INIT(void)    
{
	// Print message during initialization
	printk("INIT DRIVER FUNCTION\n");    
	// Return 0 indicates success
	return 0;                             
}

// Exit function
static void __exit myDriver_EXIT(void)   
{
	// Print message during exit
	printk("BYE...BYE!!!\n");             
}


/* Registration Section */

module_init(myDriver_INIT);               // Specify the initialization function
module_exit(myDriver_EXIT);               // Specify the exit function

