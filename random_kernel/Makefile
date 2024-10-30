CURRENT = $(shell uname -r)
KERNEL_DIR = /lib/modules/$(CURRENT)/build
PWD = $(shell pwd)

obj-m :=rand_kernel.o

rand_kernel-objs := start.o stop.o
 
default:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules

