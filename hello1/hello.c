#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("alex fr487x@gmail.com");

static int __init hello_init(void)
{
    printk(KERN_ALERT "'hello' module started\n");
    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_ALERT "'hello' module exited\n");
    return;
}

module_init(hello_init);
module_exit(hello_exit);


