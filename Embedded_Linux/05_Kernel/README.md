# Linux Kernel

**The Linux kernel** is the core component of the Linux operating system. It serves as the bridge between the hardware and the software, providing essential functionalities such as process management, memory management, device drivers, and system calls.

# Linux Kernel for QEMU vexpress

- you can clone the **main repo** or use a **repository specifically configured for running QEMU vexpress virtual machines** 

## Clone the Main Repository

### 1. To clone the main Linux kernel repository, use the following command:

```bash
# you can either choose the linux kernel version and download it or clone the last commit
git clone --depth=1 https://github.com/torvalds/linux.git
```
### 2. Use a Repository for QEMU vexpress

**Alternatively,** you can use a repository specifically configured for running QEMU vexpress virtual machines. This repository includes additional configuration and patches optimized for the vexpress platform.

### To clone the repository for QEMU vexpress, use the following command:
```bash
# you can either choose the linux kernel version and download it or clone the last commit
git clone --depth=1 https://github.com/qemu/qemu.git
```

## Building the Kernel
**Note:**This configuration must be checked

- [x] Enable devtmpfs
- [x] Change kernel compression to XZ
- [x] Change your kernel local version to your name and append on it -v1.0

**Once you have cloned the repository,** you can build the Linux kernel for the QEMU vexpress platform using the following commands:
```bash
# To indentify your kernel version 
cd linux[version]

# #configure the kernel to vexpress default configuration
make vexpress_defconfig ARCH=arm CROSS_COMPILE=<Path To the Compiler>/arm-cortexa9_neon-linux-musleabihf-

#configure the kernel with more configuration if needed 
make menuconfig ARCH=arm CROSS_COMPILE=<Path To the Compiler>/arm-cortexa9_neon-linux-musleabihf-

#build the kernel 
make zImage modules dtbs ARCH=arm CROSS_COMPILE=<Path To the Compiler>/arm-cortexa9_neon-linux-musleabihf- -j$(nproc)
```

## Running QEMU

**After building the kernel,** you can run QEMU with the vexpress platform :
```bash
sudo qemu-system-arm -M vexpress-a9 -m 128M -nographic <Path To the u-boot>/u-boot -sd <Path To the sd.img>/sd.img -net tap,script=<Path To the script>/qemu-ifup -net nic
```




