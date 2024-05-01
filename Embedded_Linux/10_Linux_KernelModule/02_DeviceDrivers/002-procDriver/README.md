# Procfs Driver

This is a simple Linux kernel module that creates a procfs (proc filesystem) entry named `mydrive`. The procfs entry allows reading from and writing to the kernel module.


## Introduction
The `operating system segregates virtual memory` into `kernel` space and `userspace`.`Kernel space` is strictly reserved for running the `kernel, kernel extensions, and most device drivers`.In contrast, `user space` is the memory area where all `user-mode applications work`, and this memory can be swapped out when necessary. 
> :exclamation: There are many ways to Communicate between the Userspace and Kernel Space, one of them is `Procfs`:

On the root, there is a folder titled `“proc”`.This folder is a mount point for the `procfs (Process Filesystem)` which is a `filesystem in memory`.
> Many processes store information about themselves on this virtual filesystem.
>> :exclamation: `ProcFS` also stores other system information.
>>> It can act as a `bridge connecting the user space and the kernel space`. Userspace programs can use proc files to `read the information exported by the kernel`. Every `entry` in the proc file system provides some information from the kernel.

## Description

The procfs driver creates a virtual file named `mydrive` in the `/proc/1999_proc/` directory. This file supports reading operation.

### Features

- **`Read Operation`**: Reading from the `mydrive` file returns the string "Hello\n".

## Implementation

The driver is implemented using the following components:

- **Module Initialization**: The `procDriver_INIT` function initializes the driver. It creates a directory named `1999_proc` in the procfs filesystem and then creates a file named `mydrive` within that directory.
- **Read Operation**: The `read_proc` function handles reading from the `mydrive` file. It copies the string `"Hello\n"` to the user space buffer.
- **Module Exit**: The `procDriver_EXIT` function is called when the module is unloaded. It removes the `mydrive` file entry from the procfs filesystem.

## Usage

1. **Module Loading**:

```bash
sudo insmod procDriver.ko
```

2. **Read from mydrive**:

```bash
# Output: Hello
cat /proc/1999_proc/mydrive
```

3. **Module Unloading**:

```bash
sudo rmmod procDriver
```


