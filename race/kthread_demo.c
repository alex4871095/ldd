#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/sched/task.h>

#define COUNT 5

MODULE_LICENSE("GPL");
MODULE_AUTHOR("alex fr487x@gmail.com");

static struct task_struct **thread1;

static struct mutex *sticks;

static int *food;

static int thread_func(void *data)
{
	long num = (long)data;
	struct mutex *lstick = sticks + num;
	struct mutex *rstick = sticks + (num+1) % COUNT;

	while(food[num] > 0)
	{
		schedule();

		food[num]--;

	}

	return 0;
}

int init_module(void)
{
	mutex_init(&mtx[i]);

	thread1[i] = kthread_create(thread_func, (void*)i, thread1_name);
	if(!thread1[i])
	{
		printk(KERN_ALERT "thread1 not created\n");
		mutex_destroy(&mtx);
		return -ENOSYS;
	}

        get_task_struct(thread1[i]);
        wake_up_process(thread1[i]);

	printk(KERN_ALERT "kthreads running\n");

	return 0;
}

void cleanup_module(void)
{
	kthread_stop(thread1[i]);
	put_task_struct(thread1[i]);
	mutex_destroy(&mtx);
	printk(KERN_ALERT "kthreads demo exited, counter = %d\n", counter);
} 
