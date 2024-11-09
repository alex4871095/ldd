CURRENT = $(shell uname -r)
KERNEL_DIR = /lib/modules/$(CURRENT)/build
PWD = $(shell pwd)

obj-m :=mem_kernel.o

default:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules

