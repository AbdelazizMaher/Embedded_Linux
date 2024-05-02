obj-m = platformDriver.o  LED.o

CROSS_COMPILE = aarch64-rpi4-linux-gnu-

ARCH = arm64

TARGET_BDIR = /home/abdelaziz/NTI_WS/Linux_Workspace/DeviceDrivers/rpi-linux-headers/linux

HOST_BDIR = /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

all:
	make -C ${HOST_BDIR} M=${PWD} modules

target:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(TARGET_BDIR) M=$(PWD) modules
	
clean:
	make -C ${HOST_BDIR} M=${PWD} clean	

clean_target:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(TARGET_BDIR) M=$(PWD) clean	