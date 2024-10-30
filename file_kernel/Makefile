CURRENT = $(shell uname -r)
KERNEL_DIR = /lib/modules/$(CURRENT)/build
PWD = $(shell pwd)

obj-m :=file_kernel.o

file_kernel-objs := start.o stop.o
 
default:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules

