#include "kthread.h"

static int radio_count = 0;

int radio_open(struct inode *inode, struct file *file)
{
	if(radio_count > 0) return -EBUSY;
	radio_count++;

	return 0;
}

int radio_release(struct inode *inode, struct file *file)
{
	radio_count--;

	return 0;
}
