#include "time_kernel.h"

void cleanup_module(void)
{
	printk(KERN_ALERT MOD_NAME " exited\n");
	return;
}
