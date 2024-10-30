#include "radio.h"
#include <linux/fs.h>
#include <linux/cdev.h>
#define DEV_RANGE 1

MODULE_LICENSE("GPL");
MODULE_AUTHOR("fr487x@gmail.com alex");

static const int dev_range = 1;

static struct file_operations fops;
static int radio_init;
static dev_t radio_first;
static struct class *radio_class;
static struct cdev radio_dev;

int init_module(void)
{
	/****************** operations *********************/
	memset(&fops, 0, sizeof(fops));
	fops.owner = THIS_MODULE;
	fops.open = radio_open;
	fops.release = radio_release;
	/**************************************************/
	radio_init = alloc_chrdev_region(&radio_first, 0, dev_range, DEV_NAME);
	if(radio_init < 0)
	{
		printk(KERN_ALERT DEV_NAME " device region not allocated\n");
		return radio_init;
	}

	if((radio_class = class_create(THIS_MODULE, "chardev")) == NULL)
	{
		unregister_chrdev_region(radio_first, dev_range);
		printk(KERN_ALERT "couldn't create new character device\n");
		return -ENODEV;
	}

	if((device_create(radio_class, NULL, radio_first, NULL, DEV_NAME) == NULL))
	{
		class_destroy(radio_class);
		unregister_chrdev_region(radio_first, dev_range);
		printk(KERN_ALERT DEV_NAME " was not created\n");
		return -ENODEV;
	}

	cdev_init(&radio_dev, &fops);
	
	if((cdev_add(&radio_dev, radio_first, dev_range)) == -1)
	{
		device_destroy(radio_class, radio_first);
                class_destroy(radio_class);
                unregister_chrdev_region(radio_first, dev_range);
                printk(KERN_ALERT DEV_NAME " files were not created\n");
                return -EPERM;

	}
	printk(KERN_ALERT DEV_NAME " module and device ready, major number = %d\n", MAJOR(radio_first));
	return 0;

}

void cleanup_module(void)
{
	cdev_del(&radio_dev);
        device_destroy(radio_class, radio_first);
        class_destroy(radio_class);
        unregister_chrdev_region(radio_first, dev_range);
	printk(KERN_ALERT DEV_NAME " exited\n");

	return; 
}


