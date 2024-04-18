# Poky Source Tree



Folder Description
------------------

`bitbake`		-	Holds all Python scripts used by the bitbake command `bitbake/bin` is placed into the PATH environmental variable
			

`documentation`    	-       All documentation sources for the Yocto Project documentation Can be used to generate nice PDFs
			

`meta`			-	Contains the oe-core metadata
			
`meta-poky`		-	Holds the configuration for the Poky reference distribution `local.conf.sample`, `bblayers.conf.sample` are present here
			

`meta-skeleton`	- 	Contains template recipes for BSP and kernel development


`meta-yocto-bsp` 	-	Maintains several BSPs such as the Beaglebone, EdgeRouter, and generic versions of both 32-bit and 64-bit IA machines.
			

`scripts`		-	Contains scripts used to set up the environment, development tools,and tools to flash the generated images on the target.
			

`LICENSE`		-	The license under which Poky is distributed `(a mix of GPLv2 and MIT)`.


conf
-----------

When you run `source poky/oe-init-build-env`, it will create a `"build"` folder in that directory
Inside this build folder, it will create `"conf"` folder which contains two files:

1. local.conf
2. bblayers.conf

local.conf
-------------

Configures almost every aspect of the build system and Contains local user settings


`MACHINE`: The machine the target is built for

```bash
Eg: MACHINE = "qemux86-64"
```
 
`DL_DIR`: Where to place downloads

During a first build the system will download many different source code tarballs,from various 
upstream projects.These are all stored in `DL_DIR`
The default is a downloads directory under `TOPDIR` which is the build directory

`TMP_DIR`:  Where to place the build output

This option specifies where the bulk of the building work should be done and
where BitBake should place its temporary files`(source extraction, compilation)` and output

Important Point:
----------------

`local.conf` file is a very convenient way to override several default configurations over all the Yocto Project's tools.

Essentially, we can change or set any variable, for example, add additional packages to an image file

> Though it is convenient, it should be considered as a temporary change as the `build/conf/local.conf` file is not usually tracked by any source code management system.	


bblayers.conf
------------------

`The bblayers.conf` file tells BitBake what layers you want considered during the build.

By default, the layers listed in this file include layers minimally needed by the build system

> However, you must manually add any custom layers you have created

```bash
BBLAYERS ?= " \
  /home/abdelaziz/NTI_WS/Linux_Workspace/YOCTO/poky/meta \
  /home/abdelaziz/NTI_WS/Linux_Workspace/YOCTO/poky/meta-poky \
  /home/abdelaziz/NTI_WS/Linux_Workspace/YOCTO/poky/meta-yocto-bsp \
  "
```
                               
> This example enables four layers, one of which is a custom user defined layer named "meta-mylayer"

Other directories
-----------------

`downloads`	-	downloaded upstream tarballs/git repositories of the recipes used in the build

`sstate-cache`	-	shared state cache

`tmp`		-	Holds all the build system output, tmp/deploy/images/machine - Images are present here
			
`cache`	-	cache used by the bitbake's parser		
