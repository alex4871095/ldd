CURRENT = $(shell uname -r)
KERNEL_DIR = /lib/modules/$(CURRENT)/build
PWD = $(shell pwd)
CC_FLAGS_FPU := mhard-float

CFAGS_fpu_kernel.o += $(CC_FLAGS_FPU)

obj-m := fpu_mod.o

fpu_mod-objs := start.o stop.o fpu_kernel.o
 
default:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules

