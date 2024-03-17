# U-Boot (Das U-Boot)

**U-Boot,** short for Universal Bootloader, is an **open-source bootloader** widely used in embedded systems. It supports a wide range of architectures and platforms, making it a versatile choice for bootstrapping embedded Linux systems and other operating systems.

## Building U-Boot

## 1. Clone the U-Boot repository from the official Git repository and branch to a stable release:
```bash
https://github.com/u-boot/u-boot.git
cd u-boot/
git checkout v2022.07
```
## 2. Configure U-Boot for your target platform ( Vexpress Cortex A9 (Qemu) ):
### 2.1. Grep the machine wanted by using U-Boot configs file( supported machines )
```bash
ls configs/ | grep vexpress
```
### 2.2. Default configured U-Boot for supproted architecture:
```bash
make vexpress_ca9x4_defconfig ARCH=arm CROSS_COMPILE=~/x-tools/arm-cortexa9_neon-linux-musleabihf/bin/arm-cortexa9_neon-linux-musleabihf-
```
**Notes**
### Varibles used by the u-boot makefile
```bash
CROSS_COMPILE=<Path To the Compiler>/arm-cortexa9_neon-linux-musleabihf-
ARCH=arm
```
### 2.3. Modify default-configured U-Boot for supproted architecture:
```bash
make menuconfig ARCH=arm CROSS_COMPILE=~/x-tools/arm-cortexa9_neon-linux-musleabihf/bin/arm-cortexa9_neon-linux-musleabihf-
```
### 2.4. Build U-Boot:
```bash
make ARCH=arm CROSS_COMPILE=~/x-tools/arm-cortexa9_neon-linux-musleabihf/bin/arm-cortexa9_neon-linux-musleabihf- -j 6
```
## 3. Run Qemu:
```bash
qemu-system-arm -M vexpress-a9 -m 128M -nographic -kernel <Path To the u-boot>/u-boot -sd <Path To the sd.img>/sd.img
```












  
