# Poky

**Poky** is a reference distribution of Yocto Project. The word **"reference"** is used to mean **"example"** in this context.

Yocto Project uses Poky to build images (kernel, system, and application software) for targeted hardware.

At the technical level it is a combined repository of the components:

-  Bitbake
-  OpenEmbedded Core
-  meta-yocto-bsp
-  Documentation

**Note:** Poky does not contain binary files,it is a working example of how to build your own custom Linux distribution from source.

## Difference between poky and Yocto

Difference between Yocto and Poky is Yocto refers to the organization `( like one would refer to 'canonical', the company behind Ubuntu )`, and Poky refers to the actual bits downloaded` ( analogous to 'Ubuntu' )`

**Poky includes:**

- some OE components(oe-core)
- bitbake
- demo-BSP's
- helper scripts to setup environment
- emulator QEMU to test the image

  
| Poky = Bitbake + Metadata |
| :-----------------------: |

**Metadata is collection of:**

- Configuration files (.conf)
- Recipes (.bb and .bbappend)
- Classes (.bbclass)
- Includes (.inc)	
	

 
### 1- Metadata 

**Yocto World:**

- Metadata refers to the build instructions
- Commands and data used to indicate what versions of software are used
- Where they are obtained from
- Changes or additions to the software itself ( patches ) which are used to fix bugs or customize the software for use in a particular situation

**Metadata is collection of:**

- Configuration files (.conf)
- Recipes (.bb and .bbappend)
- Classes (.bbclass)
- Includes (.inc)

	
### 2- Recipes

A recipe is a set of instructions that is read and processed by the bitbake

**Extension of Recipe: .bb**

A recipe describes:
    where you get source code
    which patches to apply
    Configuration options
    Compile options (library dependencies)
    Install
    License

a software component


### 3- Configuration Files

Files which hold
- global definition of variables
- user defined variables and
- hardware configuration information

They tell the build system what to build and put into the image to support a particular platform

**Extension: .conf**
	
	
### 3- classes

Class files are used to abstract common functionality and share it amongst multiple recipe (.bb) files

To use a class file, you simply make sure the recipe inherits the class

Eg. inherit classname

**Extension: .bbclass**

They are usually placed in classes directory inside the meta* directory

Example of classes
-------------------

cmake.bbclass - Handles cmake in recipes
kernel.bbclass - Handles building kernels. Contains code to build all kernel trees
module.bbclass - Provides support for building out-of-tree Linux Kernel Modules



## 4- Layers

A collection of related recipes **or** Layers are recipe containers (folders)

**Typical naming convention:** meta-<layername>

Poky has the following layers:

`meta`, `meta-poky`, `meta-selftest`, `meta-skeleton`, `meta-yocto-bsp`


Image
-----------

An image is the top level recipe, it has a description, a license and inherits the core-image class

It is used alongside the machine definition

machine describes the hardware used and its capabilities

image is architecture agnostic and defines how the root filesystem is built, with what packages.

By default, several images are provided in Poky

Command to check the list of available image recipes
----------------------------------------------------

$ ls meta*/recipes*/images/*.bb


Packages
-------------

A package is a binary file with name *.rpm, *.deb, or *.ipkg

A single recipe produces many packages. All packages that a recipe generated are listed in the recipe variable



Poky source tree
------------------

`bitbake`		-	Holds all Python scripts used by the bitbake command bitbake/bin is placed into the PATH environmental variable
			

`documentation`    	-       All documentation sources for the Yocto Project documentation Can be used to generate nice PDFs
			

`meta`			-	Contains the oe-core metadata
			
`meta-poky`		-	Holds the configuration for the Poky reference distribution local.conf.sample, bblayers.conf.sample are present here
			

`meta-skeleton`		- 	Contains template recipes for BSP and kernel development


`meta-yocto-bsp` 	-	Maintains several BSPs such as the Beaglebone, EdgeRouter, and generic versions of both 32-bit and 64-bit IA machines.
			

`scripts`		-	Contains scripts used to set up the environment, development tools,and tools to flash the generated images on the target.
			

`LICENSE`		-	The license under which Poky is distributed (a mix of GPLv2 and MIT).


conf
-----------

When you run source poky/oe-init-build-env, it will create a "build" folder in that directory
Inside this build folder, it will create "conf" folder which contains two files:

1. local.conf
2. bblayers.conf

local.conf
-------------

Configures almost every aspect of the build system
Contains local user settings

MACHINE: The machine the target is built for
	Eg: MACHINE = "qemux86-64"

DL_DIR: Where to place downloads
	During a first build the system will download many different source code tarballs,from various 
	upstream projects.These are all stored in DL_DIR
	The default is a downloads directory under TOPDIR which is the build directory

TMP_DIR:  Where to place the build output
	  This option specifies where the bulk of the building work should be done and
	  where BitBake should place its temporary files(source extraction, compilation) and output

Important Point:
----------------

local.conf file is a very convenient way to override several default configurations over all the Yocto Project's tools.

Essentially, we can change or set any variable, for example, add additional packages to an image file

Though it is convenient, it should be considered as a temporary change as the build/conf/local.conf file is not usually tracked by any source code management system.	


bblayers.conf
------------------

The bblayers.conf file tells BitBake what layers you want considered during the build.

By default, the layers listed in this file include layers minimally needed by the build system

However, you must manually add any custom layers you have created

E.g: BBLAYERS = "\
                                  /home/linuxtrainer/poky/meta \
                                 /home/linuxtrainer/poky/meta-poky \
                                 /home/linuxtrainer/poky/meta-yocto-bsp \
                                 /home/linuxtrainer/poky/meta-mylayer \
                                 "
This example enables four layers, one of which is a custom user defined layer named "meta-mylayer"

Other directories
-----------------

`downloads`	-	downloaded upstream tarballs/git repositories of the recipes used in the build

`sstate-cache`	-	shared state cache

`tmp`		-	Holds all the build system output, tmp/deploy/images/machine - Images are present here
			
`cache`		-	cache used by the bitbake's parser		
