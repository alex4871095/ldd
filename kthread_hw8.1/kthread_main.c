#include "kthread.h"

#define DEV_RANGE 1
#define DEV_CLASS_MODE ((umode_t)(S_IRUGO|S_IWUGO))
#define DEV_NAME "kthread_radio"
#define STEPS 100
#define BUF_SIZE 1024

DECLARE_WAIT_QUEUE_HEAD(WaitQ);

static const int dev_range = 1;
static struct file_operations fops;
static int radio_init;
static dev_t radio_first;
static struct class *radio_class;
static struct cdev radio_dev;

static char *my_class_devnode(struct device *dev, umode_t *mode)
{
    if (mode != NULL)
        *mode = DEV_CLASS_MODE;
    return NULL;
}

struct task_struct *task, *thread1;
struct task_struct *task_child;
struct list_head *list;
static int random_number;
static char u_comm[20] = "ssh-agent";
char *msg = "default response";
char *str = "";

static int thread_func(void *data)
{
	int i, j;
	int signum = SIGKILL, sig_ret = 0;
	struct kernel_siginfo info;
	// char *str = "";

	memset(&info, '\0', sizeof(struct kernel_siginfo));
	info.si_signo = signum;

	for(i = 0; i < STEPS;i++)
	{
		get_random_bytes(&random_number, sizeof(int));	
		printk(KERN_ALERT DEV_NAME " %d Random number %d\n", i, random_number);

		if(random_number < 0) random_number = -random_number; 
		j = 0;
		while (random_number > 0)
		{
        		// Convert integer digit to character and store it in device file default response msg
        		str[j++] = random_number % 10 + '0';
      			random_number /= 10;
    		} 
		
		msg = str;
		printk(KERN_ALERT DEV_NAME " msg formed from random number %s\n", msg);

		// Sending signal to user process
		sig_ret = send_sig_info(signum, &info, task);
		if (sig_ret < 0)
		{
			printk(KERN_ALERT DEV_NAME " Error sending signal\n");
		}

		msleep(1000);

		if(kthread_should_stop())
			break;
	}

	return 0;
}

int init_module(void)
{
	int res = 0;

        /****************** operations *********************/
        memset(&fops, 0, sizeof(fops));
        fops.owner = THIS_MODULE;
        fops.open = radio_open;
        fops.release = radio_release;
        fops.read = radio_read;
        fops.write = radio_write;
        /**************************************************/
        radio_init = alloc_chrdev_region(&radio_first, 0, dev_range, DEV_NAME);
        if(radio_init < 0)
        {
                printk(KERN_ALERT DEV_NAME " device region not allocated\n");
                return radio_init;
        }

        if((radio_class = class_create(THIS_MODULE, "chardev")) == NULL)
        {
                unregister_chrdev_region(radio_first, dev_range);
                printk(KERN_ALERT "couldn't create new character device\n");
                return -ENODEV;
        }

        radio_class->devnode = my_class_devnode;

        if((device_create(radio_class, NULL, radio_first, NULL, DEV_NAME) == NULL))
        {
                class_destroy(radio_class);
                unregister_chrdev_region(radio_first, dev_range);
                printk(KERN_ALERT DEV_NAME " was not created\n");
                return -ENODEV;
        }

        cdev_init(&radio_dev, &fops);

        if((cdev_add(&radio_dev, radio_first, dev_range)) == -1)
        {
                device_destroy(radio_class, radio_first);
                class_destroy(radio_class);
                unregister_chrdev_region(radio_first, dev_range);
                printk(KERN_ALERT DEV_NAME " files were not created\n");
                return -EPERM;

        }
        printk(KERN_ALERT DEV_NAME " module and device ready, major number = %d\n", MAJOR(radio_first));


	// Obtain needed user-space process task struct
	for_each_process( task )
	{
		// printk(KERN_INFO "\nPARENT PID: %d PROCESS: %s",task->pid, task->comm);

		res = strncmp(task->comm, u_comm, sizeof(u_comm));
        	if(res == 0) break;

		list_for_each(list, &task->children)
		{
			task_child = list_entry( list, struct task_struct, sibling );
			// printk(KERN_INFO "\nCHILD OF %s[%d] PID: %d PROCESS: %s",task->comm, task->pid, task_child->pid, task_child->comm);

	                res = strncmp(task->comm, u_comm, sizeof(u_comm));
       			if(res == 0) break;
		}
	}

	// printk(KERN_ALERT DEV_NAME " task->comm struct field: %s\n", task->comm);

	char thread1_name[] = "counter1";

	thread1 = kthread_create(thread_func, (void*)1, thread1_name);
	if(!thread1)
	{
		printk(KERN_ALERT "thread1 not created\n");
		return -ENOSYS;
	}
	get_task_struct(thread1);
	wake_up_process(thread1);

	printk(KERN_ALERT "kthread running\n");

	return 0;
}

void cleanup_module(void)
{
	kthread_stop(thread1);
	put_task_struct(thread1);
	device_destroy(radio_class, radio_first);
	class_destroy(radio_class);
	unregister_chrdev_region(radio_first, dev_range);
	printk(KERN_ALERT "kthread demo exited\n");
} 

MODULE_LICENSE("GPL");
MODULE_AUTHOR("alex fr487x@gmail.com");

