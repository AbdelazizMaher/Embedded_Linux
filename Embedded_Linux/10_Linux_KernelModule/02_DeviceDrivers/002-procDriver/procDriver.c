#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>


#define DEV_MEM_SIZE  512

/* proc device memory */
char proc_buffer[DEV_MEM_SIZE];

struct proc_dir_entry *proc_dir_entry;

struct proc_dir_entry *proc_file_entry;

ssize_t	read_proc(struct file *filp, char __user *buff, size_t count, loff_t *f_pos)
{
    copy_to_user(buff,"Hello\n",7);  

    return 7;  
}

ssize_t	write_proc(struct file *filp, const char __user *buff, size_t count, loff_t *f_pos)
{
    printk(KERN_INFO "proc file write.....\t");

    //copy_from_user(&proc_buffer[*f_pos],buff,count);
    return count;    
}

struct proc_ops proc_fops = 
{
    .proc_read = read_proc,
    .proc_write = write_proc,
};

static int __init procDriver_INIT(void)
{
    printk("PROC INIT DRIVER FUNCTION\n");

    proc_dir_entry = proc_mkdir("1999_proc", NULL);

    proc_file_entry = proc_create("mydrive",0660,proc_dir_entry,&proc_fops);
    if ( !proc_file_entry )
    {
        printk(KERN_ERR "Failed to create proc entry\n");
        return -ENOMEM;
    }
    return 0;
}

static void __exit procDriver_EXIT(void)
{
    printk("PROC EXIT DRIVER FUNCTION!!!\n");

    if ( proc_file_entry )
        remove_proc_entry("mydrive",NULL);
}



MODULE_LICENSE("GPL");
MODULE_AUTHOR("Abdelaziz");
MODULE_DESCRIPTION("procfs Driver");

module_init(procDriver_INIT);
module_exit(procDriver_EXIT);

