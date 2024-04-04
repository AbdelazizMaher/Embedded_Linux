# Workflow of generating QEMU image 


Step 1: Prepare the build environment

```bash
source poky/oe-init-build-env [ build_directory ]
```

The above script will move you in a build folder and create two files `**( local.conf, bblayers.conf )**` inside conf folder


Step 2: Add in local.conf

```bash
```bash
##### Please replace number of cores with your host cores and multiply it by the number next to it #####
BB_NUMBER_THREADS ?= "1.5 * Number of cores"
PARALLEL_MAKE ?= "-j 2 * Number of cores"

```

Step 3: Building Linux Distribution

```bash
#core-image-minimal --->> This is a small image allowing a device to boot, and it is very useful for kernel and boot loader tests and development
bitbake <image_name>
```

## Command to run the generated image in QEMU

Quick Emulator ( QEMU ) is a free and open source software package that performs hardware virtualization.

Poky provides a script 'runqemu' which will allow you to start the QEMU using yocto generated images.

The runqemu script is run as:
   ```bash
   runqemu <machine> <zimage> <filesystem>
   ```
**where:**

   `<machine>` is the machine/architecture to use (qemuarm/qemumips/qemuppc/qemux86/qemux86-64)
   
   `<zimage>` is the path to a kernel (e.g. zimage-qemuarm.bin)
   
   `<filesystem>` is the path to an ext2 image (e.g. filesystem-qemuarm.ext2) or an nfs directory

**Exit QEMU** by either clicking on the shutdown icon or by typing **Ctrl-C** in the QEMU transcript window from which you evoked QEMU.

**Nographic** You can launch QEMU without the graphic window by adding `**nographic**` to the command line



	





