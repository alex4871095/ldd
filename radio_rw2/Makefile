CURRENT = $(shell uname -r)
KERNEL_DIR = /lib/modules/$(CURRENT)/build
PWD = $(shell pwd)

obj-m := radio.o

radio-objs := radio_main.o
 
default:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules

