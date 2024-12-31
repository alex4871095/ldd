#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/sched/task.h>
#include <linux/list.h>
#include <linux/fs.h>
#include <linux/stat.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/string.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("alex fr487x@gmail.com");

static struct task_struct *worker;
static struct task_struct *manager;
static struct task_struct *task, *task_child;

static char task_name[] = ""; 

struct list_head *list;

static struct mutex mtx;

static int res, workers = 0;

static long id = 0;
static int job = 0;

module_param(workers, int, 0664);

static int worker_func(void *data)
{
	long worker_id = (long)data;

	while(true)
	{
		if (id != worker_id)
		{
	                while(!mutex_trylock(&mtx)) schedule();
			printk(KERN_ALERT "This is worker %ld running\n", worker_id);
			id = worker_id;
			job++;
                	mutex_unlock(&mtx);
		}
		msleep(100);
		if(kthread_should_stop())
			break;
	}
	return 0;
}

static int manager_func(void *data)
{
	int i = 0;
        mutex_init(&mtx);

	while(true)
	{
		if(job == 0)
		{
			for(i=0; i< workers; i++)
			{
				char thread_name[] = "";
				snprintf(thread_name, sizeof(thread_name), "%d", i);
        			worker = kthread_create(worker_func, (void*)i, thread_name);
        			if(!worker)
        			{
                			printk(KERN_ALERT "worker %d not created\n", i);
                			mutex_destroy(&mtx);
                			return -ENOSYS;
				}
        			get_task_struct(worker);
        			wake_up_process(worker);
			}
		}
		msleep(1000);

		if(job > workers)
		{
                        for(i=0; i< workers; i++)
                        {
				snprintf(task_name, sizeof(task_name), "%d", i);
				for_each_process( task )
				{
					res = strncmp(task->comm, task_name, sizeof(task_name));
        				if(res == 0) break;

					list_for_each(list, &task->children)
					{
						task_child = list_entry(list, struct task_struct, sibling);
	                			res = strncmp(task->comm, task_name, sizeof(task_name));
       						if(res == 0) break;
					}
				}

		        	kthread_stop(task);
        			put_task_struct(task);
			}
			job = 0;
		        printk(KERN_ALERT "worker kthreads exited\n");
		}
		msleep(1000);
                if(kthread_should_stop())
                        break;
	}

        return 0;
}


int init_module(void)
{

	char thread_name[] = "manager";

	manager = kthread_create(manager_func, (void*)1, thread_name);
	if(!manager)
	{
		printk(KERN_ALERT "manager not created\n");
		mutex_destroy(&mtx);
		return -ENOSYS;
	}

        get_task_struct(manager);
        wake_up_process(manager);

	printk(KERN_ALERT "manager kthread running\n");

	return 0;
}

void cleanup_module(void)
{
	kthread_stop(manager);
	put_task_struct(manager);
	//kthread_stop(worker);
	//put_task_struct(worker);
	mutex_destroy(&mtx);
	printk(KERN_ALERT "kthreads demo exited\n");
} 
