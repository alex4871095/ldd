#include "fpu_mod.h"
#include "fpu_kernel.h" 

MODULE_LICENSE("GPL");
MODULE_AUTHOR("fr487x@gmail.com alex");

int init_module(void)
{
	printk(KERN_ALERT MOD_NAME " started\n");
	fpu_ops();
	return 0;
}
