obj-m = pseudoDriver.o

ARCH=arm

CROSS_COMPILE=arm-linux-gnueabihf-

TARGET_BDIR =

HOST_BDIR = /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

all:
	make -C ${HOST_BDIR} M=${PWD} modules
	
clean:
	make -C ${HOST_BDIR} M=${PWD} clean	