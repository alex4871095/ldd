#include "symbol2.h"
#include <linux/module.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("fr487x@gmail.com alex");

/********************* global variables *********************/

static int count;
static int arr[100];

/******************* module param description ***************/
module_param_array(arr, int, &count, 0664);

int init_module(void)
{
	printk(KERN_ALERT MOD_NAME " started\n");
	printk(KERN_ALERT "array sum = %d\n", arr_sum(arr, count));
	return 0;
}

void cleanup_module(void)
{
        printk(KERN_ALERT MOD_NAME " exited\n");
	return;
}
