#include <linux/module.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("fr487x@gmail.com alex");

/********************* global variables *********************/

static int arr[5] = {1,2,3,4,5};

/******************** callback function ********/

static int value_set(const char *val, const struct kernel_param *kp)
{
	int i, sum=0;
	
	param_array_ops.set(val, kp);
        for(i=0; i<5; i++)
        {
                sum+=arr[i];
        }
	printk(KERN_ALERT "array values updated\n");
	printk(KERN_ALERT "array sum = %d\n", sum);

	return 0;
}

const struct kernel_param_ops pops =
{
	.set = value_set,
	.get = param_array_ops.get
};
 
/******************* module param description ***************/
module_param_cb(arr, &pops, &arr, 0664);

int init_module(void)
{
	int i, sum=0;
	printk(KERN_ALERT "module started. arr:\n");
	for(i=0; i<5; i++)
	{
		printk(KERN_ALERT "%d\n", arr[i]);
		sum+=arr[i];
	}
	printk(KERN_ALERT "array sum = %d\n", sum);
	return 0;
}

void cleanup_module(void)
{
	return;
}
