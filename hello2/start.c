#include "hello.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("user");

int init_module(void)
{
	int i;

	printk(KERN_ALERT MOD_NAME " started\n");
	for(i=0; i<10; i++)
		printk(KERN_ALERT "%s - %d\n", MOD_NAME, i);
	return 0;
}
