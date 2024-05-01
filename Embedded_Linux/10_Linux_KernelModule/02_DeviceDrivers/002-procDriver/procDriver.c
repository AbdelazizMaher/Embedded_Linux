#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>


#define DEV_MEM_SIZE  512

/* proc device memory */
char proc_buffer[DEV_MEM_SIZE];

/* Pointer to the proc directory entry */
struct proc_dir_entry *proc_dir_entry;

/* Pointer to the proc file entry */
struct proc_dir_entry *proc_file_entry;

/* Read function for the proc file */
ssize_t	read_proc(struct file *filp, char __user *buff, size_t count, loff_t *f_pos)
{
    /* 1. Copy the string "Hello\n" to user space */
    copy_to_user(buff,"Hello\n",7);  

    /* 2. Return the number of bytes written */
    return 7;  
}

ssize_t	write_proc(struct file *filp, const char __user *buff, size_t count, loff_t *f_pos)
{
    /* Print a message to the kernel log */
    printk(KERN_INFO "proc file write.....\t");

    /*copy_from_user(&proc_buffer[*f_pos],buff,count);*/

    /* Return the number of bytes written */
    return count;    
}

/* Proc file operations structure */
struct proc_ops proc_fops = 
{
    .proc_read = read_proc,
    .proc_write = write_proc,
};

/* Module initialization function */
static int __init procDriver_INIT(void)
{
    printk("PROC INIT DRIVER FUNCTION\n");

    /* 1. Create a proc directory */
    proc_dir_entry = proc_mkdir("1999_proc", NULL);

    /* 2. Create a proc file */
    proc_file_entry = proc_create("mydrive",0660,proc_dir_entry,&proc_fops);
    if ( !proc_file_entry )
    {
        printk(KERN_ERR "Failed to create proc entry\n");
        return -ENOMEM;
    }
    return 0;
}

/* Module exit function */
static void __exit procDriver_EXIT(void)
{
    printk("PROC EXIT DRIVER FUNCTION!!!\n");

    /* Remove the proc file entry */
    if ( proc_file_entry )
        remove_proc_entry("mydrive",NULL);
}


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Abdelaziz");
MODULE_DESCRIPTION("procfs Driver");

/* Register the module initialization and exit functions */
module_init(procDriver_INIT);
module_exit(procDriver_EXIT);

