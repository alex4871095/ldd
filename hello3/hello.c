#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("alex fr487x@gmail.com");

extern int my_alert(const char*, const char*);

static int __init hello_init(void)
{
    my_alert("hello", "started");
    return 0;
}

static void __exit hello_exit(void)
{
    my_alert("hello", "exited");
    return;
}

module_init(hello_init);
module_exit(hello_exit);


