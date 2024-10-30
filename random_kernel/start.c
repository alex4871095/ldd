#include "rand_kernel.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("user");

int init_module(void)
{
	int i;
	printk(KERN_ALERT MOD_NAME " started\n");
	get_random_bytes(&i, sizeof(int));	
	printk(KERN_ALERT "Random number - %d\n", i);
	return 0;
}
