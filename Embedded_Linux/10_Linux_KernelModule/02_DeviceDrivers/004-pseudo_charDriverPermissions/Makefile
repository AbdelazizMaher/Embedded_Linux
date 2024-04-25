obj-m = pseudoDriver_Permissions..o

HOST_BDIR = /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

all:
	make -C ${HOST_BDIR} M=${PWD} modules
	
clean:
	make -C ${HOST_BDIR} M=${PWD} clean	