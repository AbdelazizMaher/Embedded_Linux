# Create Your Own Emulated SDcard

## SDcard 
![](Sdcard.png)

## 1. In a new folder, create a new file
```bash
mkdir EmulatedSD
touch sd.img
cd EmulatedSD/
```

## 2. Create file size with 1 GB or (wanted size) filled with zeros
```bash
dd if=/dev/zero of=sd.img bs=1M count=1024
```

## 3. Add partition table and partition the file 
```bash
cfdisk sd.img
```
**Notes:** 

  a) Choose partion table ==> DOS/MBR
  
  b) Create Two pwrtitions ==> boot (FAT 16) , rootfs (Linux/ext4)
  
  c) Make boot partition bootable

 ## 4. Attach the sdcard file to a virtual storage device( /dev/loop )
```bash
 sudo losetup -f --show --partscan sd.img
```
**Notes:** 

  a) `-f, --find :` Find  the first unused loop device.
  
  b) `--show:` Display the name of the assigned loop device
  
  c) `-P, --partscan:` Force the kernel to scan the partition table on a newly created loop device.

## 5. Create folders(number of partitions) and then Add file-system data structure to the partitions
```bash
sudo mkfs.vfat -F 16 -n boot /dev/loop13p1
sudo mkfs.ext4 -L rootfs /dev/loop13p2
```
## 6. Mount the file-system data structure to the partitions as every partition acts as a device
```bash
sudo mount /dev/loop13p1 BOOT/
sudo mount /dev/loop13p2 ROOTFS/
```
## 7. list block devices
```bash
lsblk 
```












  
