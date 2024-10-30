#include "radio.h"
#include <linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("fr487x@gmail.com alex");

static struct file_operations fops;
static int radio_major;

int init_module(void)
{
	/****************** operations *********************/
	memset(&fops, 0, sizeof(fops));
	fops.owner = THIS_MODULE;
	fops.open = radio_open;
	fops.release = radio_release;
	/**************************************************/
	if((radio_major = register_chrdev(0, DEV_NAME, &fops)) <0)
	{
		printk(KERN_ALERT "Cannot register new device!\n");
		return radio_major;
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

