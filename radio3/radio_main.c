#include "radio.h"
#include <linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("fr487x@gmail.com alex");

/********************* global data *********************/

static int radio_major;

/******************** module params declaration ********/

module_param(radio_major, int, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
MODULE_PARM_DESC(radio_major, "device major number");

static struct file_operations fops;
static int ret;

int init_module(void)
{
	/****************** operations *********************/
	memset(&fops, 0, sizeof(fops));
	fops.owner = THIS_MODULE;
	fops.open = radio_open;
	fops.release = radio_release;
	/**************************************************/
	if((ret = register_chrdev(radio_major, DEV_NAME, &fops)) <0)
	{
		printk(KERN_ALERT "Cannot register new device!\n");
		return ret;
	}

	printk(KERN_ALERT DEV_NAME " module and device ready, major number = %d\n", radio_major);
	return 0;

}

void cleanup_module(void)
{
	unregister_chrdev(radio_major, DEV_NAME);
	printk(KERN_ALERT DEV_NAME " exited\n");

	return; 
}


