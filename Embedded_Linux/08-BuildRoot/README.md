# Buildroot 

## Overview

Buildroot is a simple, efficient, and easy-to-use tool to generate embedded Linux systems through cross-compilation. This guide provides step-by-step instructions to install, build, and configure Buildroot for QEMU.


## Installation

1. **Clone Buildroot Repository:**
    ```bash
    git clone https://gitlab.com/buildroot.org/buildroot.git
    ```

1.1 **Clone Buildroot Repository:**
    ```bash
    wget https://buildroot.org/downloads/buildroot-2024.02.1.tar.gz
    ## extract and decompress
    tar -xzvf buildroot-2022.02.1.tar.gz
    ```
    
2. **Navigate to Buildroot Directory:**
    ```bash
    cd buildroot
    ```
    
3. **List all board configuration supported by Buildroot:**
    ```bash
    make list-defconfigs
    ```    
4. **load the default configuration of ARM Vexpress Cortex A9:**
    ```bash
    make qemu_arm_versatile_defconfig
    ```
    
5. **Configure Buildroot:**
    ```bash
    #  to customize Buildroot configuration. You can add/remove packages, modify kernel settings, etc.	
    make menuconfig
    ```

In the configuration, configure the following **requirement**:

- [x]  Init procecss to **System V** or **System D** or **Busybox init**

`In case of using systemD increase the root file system size from build root configuartion`

- [x]  Change **system host**
- [x] Change **system banner**
- [x]  Appy **root password**

#### Configure SSH

In order to configure SSH and add the executable in rootfs in **buildroot**

- [x]  Enable in **Network application** configure **dropbear**
- [x]  Set **Root password** in **system configuration**

5. **Build Buildroot:**
    ```bash
    make
    ```
    This command will start the build process. It will compile the toolchain, kernel, bootloader, and root filesystem.


## Configuration

- **Customize Configuration:**
    Use `make menuconfig` to customize Buildroot configuration. You can add/remove packages, modify kernel settings, etc.





