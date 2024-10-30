#include <linux/module.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("fr487x@gmail.com alex");

/********************* global variables *********************/

static int value1 = 1;
static int value2 = 1;

/******************** callback function ********/

static int value_set(const char *val, const struct kernel_param *kp)
{
	int ret, res;

	ret = kstrtoint(val, 10, &res);
	if(ret != 0 || res < 0 || res > 100) return -EINVAL;

	param_set_int(val, kp);
	printk(KERN_ALERT "new value = %d\n", value2);

	return 0;
}

static const struct kernel_param_ops pops =
{
	.set = value_set,
	.get = param_get_int
};
 
/******************* module param description ***************/
module_param(value1, int, 0664);
module_param_cb(value2, &pops, &value2, 0664);

int init_module(void)
{
	printk(KERN_ALERT "value1 = %d    value2 = %d\n", value1, value2);
	return 0;
}

void cleanup_module(void)
{
	return;
}
