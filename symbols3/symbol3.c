#include "symbol3.h"
#include <linux/module.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("fr487x@gmail.com alex");

/********************* global variables *********************/

static int low_border = 1;
static int up_border = 100;

/******************* module param description ***************/
module_param(low_border, int, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
MODULE_PARM_DESC(low_border, "low border");
module_param(up_border, int, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
MODULE_PARM_DESC(up_border, "up border");

int init_module(void)
{
	int ret, random_number=0;

	printk(KERN_ALERT MOD_NAME " started\n");
	printk(KERN_ALERT "module params low_border = %d up_border = %d\n", low_border, up_border);
	ret = param_rand(low_border, up_border, &random_number);
	if (ret == 0) 
	{
		printk(KERN_ALERT "Random number generated successfully, number = %d\n", random_number);
		return 0;
	}
	else
	{
		printk(KERN_ALERT "Error generating random number. Exiting");
		return -1;
	}
}

void cleanup_module(void)
{
        printk(KERN_ALERT MOD_NAME " exited\n");
	return;
}


