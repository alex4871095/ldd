KBUILD_EXTRA_SYMBOLS :=/home/alex/work/symbols/Module.symvers
CURRENT = $(shell uname -r)
KERNEL_DIR = /lib/modules/$(CURRENT)/build
PWD = $(shell pwd)

obj-m :=hello.o

default:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules

