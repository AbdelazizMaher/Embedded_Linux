# Device Driver

In this guide, we'll cover the **syntax, building, compiling and various parts** involved in writing a device driver for the Linux kernel, along with detailed explanations for each component.

## 1. Syntax

Writing a device driver for the Linux kernel involves understanding and implementing various parts:
 
1. Module initialization
  
2. Device registration

3. File operations 

4. Module information. 

Each part serves a specific purpose in interacting with the `kernel` and `user-space programs`, ultimately enabling the functionality of the driver.

### Header Files

Include necessary header files:
```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h> // For file operations
```

**Explanation:**

`module.h`: Provides functions and macros for module initialization and cleanup.

`kernel.h`: Contains various kernel-level functions and definitions.

`init.h`: Defines macros for module initialization.

`fs.h`: Includes definitions for file operations such as open, read, write, etc.

### Module Initialization and Cleanup

Declare module initialization and cleanup functions:

```c

static int __init mydriver_init(void) {
    // Initialization code
    return 0; // Success
}

static void __exit mydriver_exit(void) {
    // Cleanup code
}

module_init(mydriver_init);
module_exit(mydriver_exit);
```

Explanation:

`static`: This keyword specifies that the functions mydriver_init and mydriver_exit are **local to this translation unit (file)** and cannot be accessed from outside this file preventing unintended access or conflicts with functions in other parts of the kernel or other modules.

`__init`: Marks a function that is only called during module initialization. It can be discarded once the initialization is done to save memory.

`__exit`: Marks a function that is only called during module cleanup when the module is being unloaded from the kernel.

`module_init()`: Macro that defines the initialization function for the module.

`module_exit()`: Macro that defines the cleanup function for the module.


### Module Information

Define module information:

```c

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Sample Linux driver");
MODULE_VERSION("0.1");
```

Explanation:

`MODULE_LICENSE()`: Specifies the license under which the module is distributed.

`MODULE_AUTHOR()`: Specifies the author(s) of the module.

`MODULE_DESCRIPTION()`: Provides a brief description of the module.

`MODULE_VERSION()`: Specifies the version of the module.

**Note**: It is not strictly necessary, but your module really should specify which license applies to its code.


## 2. Building, Compiling and Loading

### Build

Kernel module can be built in two ways:

- Statically linked against the kernel image
 
- Dynamically loadable kernel

For **Dynamically loadable kernel**:

The command to build external module is:

```bash
make -C <path to linux kernel> M=<path to your module> [target]
```
Now the idea here is, you have to trigger the `top level makefile` of the Linux kernel source tree, we use `-C` switch with the make. make first enters into the Linux kernel source tree and it executes a top level make file.That's how **kernel build system triggers**.Where all the compiler switches, the dependency lists, version string,everything will be utilized to build your kernel module.you then have to direct the top level makefile to your `local makefile,or a local folder where you have kept your Out of tree module source`.And we direct using the variable `M`

The target takes one of these options:

`modules`: If you want to build a module

`modules_install` : If you want to install the module

`clean` : If you want to clean-up all the generated files in the module directory

`help` : if you want to get any help 


#### Creating a local Makefile

In the local makefile you should define a **kbuild** variable:

```bash
obj-<X> := <module_name>.o
```
where `X` takes one of 3 different values:

`X=n` : do not compile the module.

`X=y` : compile the module and link with kernel image ( That means, it's a static module )

`X=m` : compile as dynamically loadable kernel module

**Note:**  you should not mention `module.c` here. `module.c` is  a source, our target needs an object file to generate `module.ko`

### Load the Device Driver

After successful compilation, load the device driver module into the kernel using the following command:

```bash
sudo insmod mydriver.ko
```

### Verify Operation

To verify that the device driver is loaded and functioning correctly, check the kernel log messages using the dmesg command:

```bash
# check the latest 5 kernel messages
dmesg | tail -5
# check the first 10 kernel messages
dmesg | head -10
```

**Note**:You should see log messages indicating the initialization of your device driver.


### Unload the Device Driver

To unload the device driver module from the kernel, use the following command:

```bash
sudo rmmod mydriver
```


#### Debugging with printk
 
In Linux kernel development, `printk` is a fundamental tool used for debugging and logging. It allows developers to output messages to the kernel log, which can be viewed using utilities like `dmesg`. 

When using `printk`, the message goes into the kernel's ring buffer, often referred to as the "Kernel log".

**Note:** `printk` does not support **floating point formats** such as `%e or %f`. Refer to the documentation in the Linux source tree, specifically the document `linux/Documentation/printk-formats.txt`, to understand the format specifiers you can use with kernel data structures.

##### LogLevels

`printk` comes with kernel log levels, allowing you to control the **priority of your messages**. There are `8 log levels`, where a lower number indicates a higher log level or higher priority. The **default printk log level is 4**, which translates into kernel warning. These log levels are defined as C macros in the header file `include/linux/kern_levels.h`.
 
##### Use of log level?

The log level will be used by the kernel to understand the priority of the message. Based on the priority **kernel decides whether the message should be presented to the user immediately, by printing directly onto the console or kernel's ring buffer**.


| **Logging Level**    | **Wrapper**          | **Description**                                |
|----------------------|----------------------|------------------------------------------------|
| KERN_EMERG (0)        | pr_emerg()       	| Emergency messages, often preceding a crash.   |
| KERN_ALERT (1)        | pr_alert()       	| Immediate action required.                     |
| KERN_CRIT (2)         | pr_crit()        	| Critical conditions, often related to failures.|
| KERN_ERR (3)          | pr_err()         	| Error conditions, such as hardware failures.   |
| KERN_WARNING (4)      | pr_warn()        	| Warnings about problematic situations.         |
| KERN_NOTICE (5)       | pr_notice()      	| Normal situations worthy of note.              |
| KERN_INFO (6)         | pr_info()        	| Informational messages.                        |
| KERN_DEBUG (7)        | pr_debug()       	| Debugging messages.                            |


**Note** If you don't mention the log level, then it defaults to `CONFIG_MESSAGE_LOGLEVEL_DEFAULT` whose default value = `KERN_WARNING` .



