obj-m = myDriver.o

BDIR = /lib/modules/5.15.0-101-generic/build
PWD := $(shell pwd)

all:
	make -C ${BDIR} M=${PWD} modules
	
clean:
	make -C ${BDIR} M=${PWD} clean	
