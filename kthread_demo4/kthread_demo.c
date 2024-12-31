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

static struct mutex mtx;

static int counter = 0;

static int thread_func(void *data)
{
	// long number = (long)data;
	int i;

	for(i = 0; i < STEPS;i++)
	{
	        while(!mutex_trylock(&mtx)) schedule();
		counter++;
		mutex_unlock(&mtx);

		if(kthread_should_stop())
			break;
	}

	mutex_unlock(&mtx);

	return 0;
}

int init_module(void)
{

	char thread1_name[] = "counter1";
	char thread2_name[] = "counter2"; 
	mutex_init(&mtx);

	thread1 = kthread_create(thread_func, (void*)1, thread1_name);
	if(!thread1)
	{
		printk(KERN_ALERT "thread1 not created\n");
		mutex_destroy(&mtx);
		return -ENOSYS;
	}

        thread2 = kthread_create(thread_func, (void*)2, thread2_name);
        if(!thread1)
        {
                printk(KERN_ALERT "thread2 not created\n");
		mutex_destroy(&mtx);
                return -ENOSYS;
        }
        get_task_struct(thread1);
        wake_up_process(thread1);
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
	mutex_destroy(&mtx);
	printk(KERN_ALERT "kthreads demo exited, counter = %d\n", counter);
} 
