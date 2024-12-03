#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/sched/task.h>

#define STEPS 100

MODULE_LICENSE("GPL");
MODULE_AUTHOR("user");

static struct task_struct *thread1;
static struct task_struct *thread2;

static int thread_func(void *data)
{
	long number = (long)data;
	int i;

	for(i = 0; i < STEPS;i++)
	{
		if(i%10 == 0) printk(KERN_ALERT "%ld - %d\n", number, i);
		msleep(100);

		if(kthread_should_stop())
			break;
	}

	return 0;
}

int init_module(void)
{

	char thread1_name[] = "counter1";
	char thread2_name[] = "counter2"; 

	thread1 = kthread_create(thread_func, (void*)1, thread1_name);
	if(!thread1)
	{
		printk(KERN_ALERT "thread1 not created\n");
		return -ENOSYS;
	}
	get_task_struct(thread1);
	wake_up_process(thread1);

        thread2 = kthread_create(thread_func, (void*)2, thread2_name);
        if(!thread1)
        {
                printk(KERN_ALERT "thread2 not created\n");
		kthread_stop(thread1);
		put_task_struct(thread1);
                return -ENOSYS;
        }
	get_task_struct(thread2);
	wake_up_process(thread2);

	printk(KERN_ALERT "kthreads running\n");

	return 0;
}

void cleanup_module(void)
{
	kthread_stop(thread1);
	put_task_struct(thread1);
	kthread_stop(thread2);
	put_task_struct(thread2);
	printk(KERN_ALERT "kthreads demo exited\n");
} 
