#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/stat.h>
#include "radio.h"
#include <linux/uaccess.h>
#include <linux/slab.h>

#define DEV_RANGE 1
#define DEV_CLASS_MODE ((umode_t)(S_IRUGO|S_IWUGO))
#define SIZE 1000

MODULE_LICENSE("GPL");
MODULE_AUTHOR("fr487x@gmail.com alex");

/* ###################### Global variables ############################################ */

static const int dev_range = 1;
static struct file_operations fops;
static int radio_init;
static dev_t radio_first;
static struct class *radio_class;
static struct cdev radio_dev;
static int radio_count = 0;

char *radiodev_data;

/* ################# Helper function to set access mode to device file ################## */

static char *my_class_devnode(struct device *dev, umode_t *mode)
{
    if (mode != NULL)
        *mode = DEV_CLASS_MODE;
    return NULL;
}

/* ####################### init & cleanup functions ########################################## */

int init_module(void)
{
	/****************** operations *********************/
	memset(&fops, 0, sizeof(fops));
	fops.owner = THIS_MODULE;
	fops.open = radio_open;
	fops.release = radio_release;
        fops.read = radio_read;
        fops.write = radio_write;
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

	radio_class->devnode = my_class_devnode;

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

/* ################################### fops functions ########################### */

int radio_open(struct inode *inode, struct file *file)
{
	if(radio_count > 0) return -EBUSY;
	radio_count++;

	radiodev_data = kmalloc(SIZE, GFP_KERNEL);

	memset(radiodev_data, 0, SIZE);

	file->private_data = radiodev_data;

	return 0;
}

int radio_release(struct inode *inode, struct file *file)
{
	radio_count--;

	kfree(radiodev_data);

	return 0;
}

ssize_t radio_read(struct file *file, char *buffer, size_t length, loff_t *offset)
{
	int ofs = *offset;
	size_t len;
 
	if(ofs >= length) return 0;

	if(ofs+length > length) length = length - ofs;

	for(len = length; len > 0; len--, ofs++, buffer++) put_user(*radiodev_data, buffer);

	*offset += length;	

	return length;
}

ssize_t radio_write(struct file *file, const char *buffer, size_t length, loff_t *offset)
{
	int ofs = *offset;
	size_t len;

	if(ofs >= length) return 0;

	if(ofs+length > length) length = length +ofs;

	for(len = length; len > 0; len--, ofs++, buffer++) get_user(*radiodev_data, buffer); 

	*offset += length;

	return length;
}


