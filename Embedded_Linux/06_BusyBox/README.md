# BusyBox

BusyBox is a software suite that provides several Unix utilities in a single executable file. It is designed for embedded systems and aims to provide a small, efficient implementation of common command-line utilities.


## BusyBox for QEMU

To use BusyBox for QEMU, you typically need to include it in the root filesystem of the virtual machine or development environment. This can be achieved by:

## Downloading U-Boot

Downloading the BusyBox for QEMU binary suitable for your target architecture. You can often find precompiled binaries on the internet or compile it yourself.

### Clone the Main Repository
```bash
# Clone the BusyBox repository:
git clone https://git.busybox.net/busybox --depth=1
```

### Compilation

To compile BusyBox for QEMU, follow these steps:

```bash
cd busybox

# Configure BusyBox for the desired target architecture. For example, for ARM architecture:
make defconfig ARCH=arm CROSS_COMPILE=<Path To the Compiler>/arm-cortexa9_neon-linux-musleabihf-

# Customize the BusyBox configuration as needed:
make menuconfig ARCH=arm CROSS_COMPILE=<Path To the Compiler>/arm-cortexa9_neon-linux-musleabihf- 

# Compile BusyBox:
#Once compiled, you will find the BusyBox executable in the busybox directory.
make ARCH=arm CROSS_COMPILE=<Path To the Compiler>/arm-cortexa9_neon-linux-musleabihf-

# this will create folder name _install has all binary
make install
```
### Create the Rootfs Integration with QEMU

As BusyBox generates the binaries no the root filesystem, We need to copy the binaries under the folder _install of BusyBox directory.

```bash
# to go out from busybox directory
cd ..

# create directory rootfs
mkdir rootfs

# copy the content inside the _install into rootfs with preserving the specified attributes
cp -rp ./busybox/_install/ ./rootfs

# copy the sysroot directory content from the toolchain generated , to use shared libirares on the target
# using rsync not cp is for syncing the already presented folders and files from the busybox
rsync -a ~/x-tools/arm-cortexa9_neon-linux-musleabihf/arm-cortexa9_neon-linux-musleabihf/sysroot/    ./rootfs

# make sure the owner of files and directories is the root
sudo chown root:root rootfs/

# change directory to rootfs
cd rootfs

# create the rest folder for rootfs
mkdir -p ./dev /etc /run /mnt /sys /proc

#create folder inittab
touch /etc/inittab
```

#### Configure Inittab

We need to setup **inittab** file because it's the first thing that the **init** process look at

```bash
# inittab file 
::sysinit:/etc/init.d/rcS
# Start an "askfirst" shell on the console (whatever that may be)
ttyAMA0::askfirst:-/bin/sh
# Stuff to do when restarting the init process
::restart:/sbin/init
```
# Mount rootfs through Emulated SD Card

```bash
# mount the sd card on the host file system
sudo mount /dev/loop<chosen number>p1 BOOT/
sudo mount /dev/loop<chosen number>p2 ROOTFS/

# copy rootfs into the sd card
cd ROOTFS
sudo cp -rp * ROOTFS/

# unmount the SD card
sudo umount ROOTFS/
```

## Setup Bootargs in U-boot

```bash
setenv bootargs "console=ttyAMA0,38400n8 root=/dev/mmcblk0p2 rootfstype=ext4 rw rootwait init=/sbin/init"
# console is set depends on the machine
```

# Mount rootfs Through NFS

## Install NFS

```bash
# Install an NFS server
sudo apt install nfs-kernel-server

# Add exported directory to `/etc/exports` file, with target ip as follows
/home/abdelaziz/NTI_WS/Linux_Workspace/EmulatedSD/NFS_rootfs  192.168.1.101(rw,no_root_squash,no_subtree_check)

# Ask NFS server to apply this new configuration (reload this file)
sudo exportfs -r
```

## Setup Bootargs in U-Boot

```bash
setenv bootargs "console=ttyAMA0,38400n8 root=/dev/nfs ip=192.168.1.101:::::eth0 nfsroot=192.168.1.99:/home/abdelaziz/NTI_WS/Linux_Workspace/EmulatedSD/NFS_rootfs,nfsvers=3,tcp rw init=/sbin/init"
# make sure the console tty represet the machine you working on
```

# System configuration and startup 

The first user space program that gets executed by the kernel is `/sbin/init` and its configuration
file is `/etc/inittab`. in `inittab` we are executing `::sysinit:/etc/init.d/rcS`but this file doesn't exist.

create `/etc/init.d/rcS` startup script and in this script mount `/proc` `/sys` filesystems:

```sh 
#!/bin/sh
# mount a filesystem of type `proc` to /proc
mount -t proc comment /proc
# mount a filesystem of type `sysfs` to /sys
mount -t sysfs comment /sys
# you can create `/dev` and execute `mount -t devtmpfs comment /dev` if you missed the `devtmpfs` configuration  
```

Note: `can't run '/etc/init.d/rcS': Permission denied` , use 

```sh
#inside `rootfs` folder
chmod +x ./etc/init.d/rcS # to give execution permission for rcS script
#restart
reboot
```





