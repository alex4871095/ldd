CURRENT = $(shell uname -r)
KERNEL_DIR = /lib/modules/$(CURRENT)/build
PWD = $(shell pwd)

obj-m :=symbol3.o param_rand.o

default:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules

