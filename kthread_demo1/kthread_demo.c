#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/delay.h>

#define STEPS 100

static struct task_struct *thread1;

int thread_func(void *arg)
{
	long num = (long)arg;
	int i;

	for(i = 0; i < STEPS; i++)
	{
		if(i%10 == 0) printk(KERN_ALERT "%ld - %d\n", num, i);
		msleep(100);
	}
	return 0;
}

int init_module(void)
{
	char thread_name1[] = "demo_thread";

	thread1 = kthread_run(thread_func, (void*)1, thread_name1);
	if(!thread1)
	{
		printk(KERN_ALERT "thread failed to run\n");
		return -ENOSYS;
	}
	
	printk(KERN_ALERT "kthread demo started\n");
	return 0;
}

void cleanup_module(void)
{
        printk(KERN_ALERT "kthread demo exited\n");
}


MODULE_LICENSE("GPL");
MODULE_AUTHOR("user");

