#include "procdemo.h"
#include <linux/proc_fs.h>

MODULE_AUTHOR("alex fr487x@gmail.com");
MODULE_LICENSE("GPL");

static const struct proc_ops fops = 
{
	.proc_open = node_open, 
	.proc_release = node_release, 
	.proc_read = node_read, 
	.proc_write = node_write
};

char response[BUF_SIZE] = "default response";

int init_module(void)
{
	struct proc_dir_entry *proc_node = 0;
	proc_node = proc_create(NODE_NAME, 0, NULL, &fops);
	if(!proc_node)
	{
		printk(KERN_ALERT DEV_NAME " cannot create /proc node\n");
		return -EIO;
	}

	printk(KERN_ALERT DEV_NAME " started, /proc node createed\n");

	return 0;
}

void cleanup_module(void)
{
	remove_proc_entry(NODE_NAME, NULL);
	printk(KERN_ALERT DEV_NAME " exited\n");

	return;
}
