CURRENT = $(shell uname -r)
KERNEL_DIR = /lib/modules/$(CURRENT)/build
PWD = $(shell pwd)

obj-m :=symbol2.o arr_sum.o

default:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules

