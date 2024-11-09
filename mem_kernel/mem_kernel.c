#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>
#include "mem_kernel.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("fr487x@gmail.com alex");

/********************* global variables *********************/

static int mem_size = 1;
void *mpointer = NULL;

/******************** callback function ********/

static int value_set(const char *val, const struct kernel_param *kp)
{
	int ret, res;

	ret = kstrtoint(val, 10, &res);
	if(ret != 0 || res < 0 ) return -EINVAL;

	param_set_int(val, kp);
	printk(KERN_ALERT MOD_NAME " new value for %s is %s", kp->name, val);
	printk(KERN_ALERT MOD_NAME " freeing previously allocated memory\n");
	kfree(mpointer);
	mpointer = kmalloc(mem_size, GFP_KERNEL);
	if(mpointer)
	{
		printk(KERN_ALERT MOD_NAME " %zu bytes of memory allocated successfully\n", ksize(mpointer));
		return 0;
	}
	else
	{
		printk(KERN_ALERT MOD_NAME " memory allocation failed\n");
		return -1;
	}
}

static const struct kernel_param_ops pops =
{
	.set = value_set,
	.get = param_get_int
};
 
/******************* module param description ***************/
module_param_cb(mem_size, &pops, &mem_size, 0664);

int init_module(void)
{
	printk(KERN_ALERT MOD_NAME " started\n");
	printk(KERN_ALERT MOD_NAME " mem_size param = %d\n", mem_size);
	mpointer = kmalloc(mem_size, GFP_KERNEL);
	if(mpointer)
	{
		printk(KERN_ALERT MOD_NAME " %zu bytes of memory allocated successfully\n", ksize(mpointer));
		return 0;
	}
	else
	{
		printk(KERN_ALERT MOD_NAME " memory allocation failed\n");
		return -1;
	}
}

void cleanup_module(void)
{
	kfree(mpointer);
	printk(KERN_ALERT MOD_NAME " exited and memory freed\n");
	return;
}
