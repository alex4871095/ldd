CURRENT = $(shell uname -r)
KERNEL_DIR = /lib/modules/$(CURRENT)/build
PWD = $(shell pwd)

obj-m :=hello.o my_alert.o

hello-objs := start.o stop.o
 
default:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules

