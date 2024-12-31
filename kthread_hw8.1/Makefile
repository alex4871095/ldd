CURRENT = $(shell uname -r)
KERNEL_DIR = /lib/modules/$(CURRENT)/build
PWD = $(shell pwd)

obj-m :=kthread.o

kthread-objs := kthread_main.o radio_or.o radio_rw.o

default:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules

