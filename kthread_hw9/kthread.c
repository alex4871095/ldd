#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/sched/task.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("alex fr487x@gmail.com");

static struct task_struct *thread1;
static struct task_struct *thread2;
static struct task_struct *thread3;

static struct mutex mtx;

static int flag = 0;

static int thread_func_1(void *data)
{
	while(true)
	{
		if (flag == 0)
		{
	                while(!mutex_trylock(&mtx)) schedule();
			printk(KERN_ALERT "This is thread1 running\n");
			flag = 1;
                	mutex_unlock(&mtx);
		}
		msleep(100);
		if(kthread_should_stop())
			break;
	}
	return 0;
}

static int thread_func_2(void *data)
{
	while(true)
	{
		if(flag == 1)
		{
	                while(!mutex_trylock(&mtx)) schedule();
			printk(KERN_ALERT "This is thread2 running\n");
			flag = 2;
                	mutex_unlock(&mtx);
		}
		msleep(100);
                if(kthread_should_stop())
                        break;
        }
        return 0;
}

static int thread_func_3(void *data)
{
        while(true)
        {
                if(flag == 2)
                {
	                while(!mutex_trylock(&mtx)) schedule();
                        printk(KERN_ALERT "This is thread3 running\n");
                        flag = 0;
	                mutex_unlock(&mtx);
                }
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
	char thread3_name[] = "counter3";

	mutex_init(&mtx);

	thread1 = kthread_create(thread_func_1, (void*)1, thread1_name);
	if(!thread1)
	{
		printk(KERN_ALERT "thread1 not created\n");
		mutex_destroy(&mtx);
		return -ENOSYS;
	}

        thread2 = kthread_create(thread_func_2, (void*)2, thread2_name);
        if(!thread1)
        {
                printk(KERN_ALERT "thread2 not created\n");
		mutex_destroy(&mtx);
                return -ENOSYS;
        }

        thread3 = kthread_create(thread_func_3, (void*)3, thread3_name);
        if(!thread1)
        {
                printk(KERN_ALERT "thread3 not created\n");
                mutex_destroy(&mtx);
                return -ENOSYS;
        }

        get_task_struct(thread1);
        wake_up_process(thread1);
	get_task_struct(thread2);
	wake_up_process(thread2);
        get_task_struct(thread3);
        wake_up_process(thread3);

	printk(KERN_ALERT "kthreads running\n");

	return 0;
}

void cleanup_module(void)
{
	kthread_stop(thread1);
	put_task_struct(thread1);
	kthread_stop(thread2);
	put_task_struct(thread2);
        kthread_stop(thread3);
        put_task_struct(thread3);
	mutex_destroy(&mtx);
	printk(KERN_ALERT "kthreads demo exited\n");
} 
