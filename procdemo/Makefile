CURRENT = $(shell uname -r)
KERNEL_DIR = /lib/modules/$(CURRENT)/build
PWD = $(shell pwd)

obj-m := procdemo.o

procdemo-objs := proc_main.o proc_or.o proc_rw.o
 
default:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules

