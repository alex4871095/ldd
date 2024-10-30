#include <linux/module.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("fr487x@gmail.com alex");

/********************* global variables *********************/

static int count;
static int arr[5] = {1,2,3,4,5};

/******************* module param description ***************/
module_param_array(arr, int, &count, 0664);

int init_module(void)
{
	int i, sum=0;
	printk(KERN_ALERT "module started\n");
	for(i=0; i<5; i++)
	{
		sum+=arr[i];
	}
	printk(KERN_ALERT "array sum = %d\n", sum);
	return 0;
}

void cleanup_module(void)
{
	return;
}
