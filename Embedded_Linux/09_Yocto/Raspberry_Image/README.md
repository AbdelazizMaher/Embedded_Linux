# Steps to generate an Yocto Image for Raspberry Pi4

**Note** Poky has no support for Broadcom BCM SoC.

Step1: Download the BSP Layer for Raspberry Pi4

```bash
# Make sure to check out to the same branch of poky
git clone git://git.yoctoproject.org/meta-raspberrypi
```

Step2: vim on README.md in meta-raspberrypi to see the dependencies

This layer depends on:

* URI: git://git.yoctoproject.org/poky
  * branch: master
  * revision: HEAD

* URI: git://git.openembedded.org/meta-openembedded
  * layers: meta-oe, meta-multimedia, meta-networking, meta-python
  * branch: master
  * revision: HEAD
    
Step3: Download the meta-openembedded dependency
```bash
# Make sure to check out to the same branch of poky
git clone git://git.openembedded.org/meta-openembedded
```

Step4: vim on README.md in meta-openembedded to see the dependencies
```
meta-oe, meta-multimedia, meta-networking, meta-python are included in the meta-openembedded directory
```

Step5: Run the environment script to setup the Yocto Environment and create build directory
```bash
source poky/oe-init-build-env [ build_directory ]
```

Step6: Add meta-openembedded layers ( meta-oe, meta-multimedia, meta-networking, meta-python) and meta-raspberrypi layer to bblayers.conf
```bash
bitbake-layers add-layer <path to directory>/meta-raspberrypi
bitbake-layers add-layer <path to directory>/meta-openembedded/meta-oe 
bitbake-layers add-layer <path to directory>/meta-openembedded/meta-python
bitbake-layers add-layer <path to directory>/meta-openembedded/meta-multimedia
bitbake-layers add-layer <path to directory>/meta-openembedded/meta-networking
```

Step7: Set the MACHINE in local.conf to "raspberrypi4-64".
```bash
echo 'MACHINE = "raspberrypi4-64"' >> conf/local.conf
```

Step7: Final step is to build the image. To find out the available images:
```bash
ls ../meta-raspberrypi/recipes-*/images/
```

## Images

**`rpi-hwup-image.bb`**: This is an image based on core-image-minimal

**`rpi-basic-image.bb`**: This is an image based on rpi-hwup-image.bb, with some added features (a splash screen)

**`rpi-test-image.bb`**: This is an image based on rpi-basic-image.bb, which includes some packages present in meta-raspberrypi

### Enabling UART

RaspberryPi 4 does not have the UART enabled by default because this needs a fixed core frequency and enable_uart wil set it to the minimum

To enable it, set the following in local.conf

```bash
ENABLE_UART = "1"
```


### Flashing images on SD Card

Images are present in tmp/deploy/images/raspberrypi4-64

```bash
lsblk

sudo dd if=rpi-hwup-image-raspberrypi4-64.rpi-sdimg of=/dev/sdb bs=4096 && sync
```

### Remotely access raspberry pi4

**dropbear** is a SSH 2 server designed to be small enough to be used in small memory environments

1. Use basic or test images
```bash
# basic image supports dropbear unlike hwup image
bitbake rpi-basic-image
```

2. Append the package in local.conf
```bash
# adds dropbear to the packages installed on the image.
IMAGE_INSTALL:append = " dropbear"
```
