#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("user");

int my_alert(const char *name, const char *msg)
{
	printk(KERN_ALERT "module %s: alert: %s\n", name, msg);
	return 0;
} 

EXPORT_SYMBOL(my_alert);


