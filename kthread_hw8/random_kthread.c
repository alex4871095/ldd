#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/sched/task.h>
#include <linux/proc_fs.h>

#define STEPS 100
#define DEV_NAME "randkthread"
#define NODE_NAME "rand_kthread"
#define BUF_SIZE 1024

MODULE_LICENSE("GPL");
MODULE_AUTHOR("alex fr487x@gmail.com");

DECLARE_WAIT_QUEUE_HEAD(WaitQ);
static int already_opened = 0;
char response[BUF_SIZE];

static struct task_struct *thread1;

static int random_number;

int node_open(struct inode*, struct file*);
int node_release(struct inode*, struct file*);

ssize_t node_read(struct file*, char*, size_t, loff_t*);
ssize_t node_write(struct file*, const char*, size_t, loff_t*);

static const struct proc_ops fops = 
{
	.proc_open = node_open, 
	.proc_release = node_release, 
	.proc_read = node_read, 
	.proc_write = node_write
};


static int thread_func(void *data)
{
	int i, j;

	for(i = 0; i < STEPS;i++)
	{
		get_random_bytes(&random_number, sizeof(int));	
		printk(KERN_ALERT "%d Random number %d\n", i, random_number);

		if(random_number < 0) random_number = -random_number; 
		j = 0;
		while (random_number > 0)
		{
        	// Convert integer digit to character and store it in response string
        		response[j++] = random_number % 10 + '0';
      			random_number /= 10;
    		} 
		msleep(1000);

		if(kthread_should_stop())
			break;
	}

	return 0;
}

int init_module(void)
{

	char thread1_name[] = "counter1";

	struct proc_dir_entry *proc_node = 0;
	proc_node = proc_create(NODE_NAME, 0, NULL, &fops);
	if(!proc_node)
	{
		printk(KERN_ALERT DEV_NAME " cannot create /proc node\n");
		return -EIO;
	}

	printk(KERN_ALERT DEV_NAME " started, /proc node createed\n");

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
	remove_proc_entry(NODE_NAME, NULL);
	printk(KERN_ALERT "kthread demo exited\n");
} 

int node_open(struct inode *inode, struct file *file)
{
	int i, is_sig = 0;

	if(already_opened) if(file->f_flags & O_NONBLOCK) return -EAGAIN;

	while(already_opened)
	{
		wait_event_interruptible(WaitQ, !already_opened);
		for(i = 0; i < _NSIG_WORDS && !is_sig; i++)
			is_sig = current->pending.signal.sig[i] & ~current->blocked.sig[i];

		if(is_sig) return -EINTR;
	}

	already_opened = 1;

	return 0;
}

int node_release(struct inode *inode, struct file *file)
{
	already_opened = 0;
	wake_up(&WaitQ);
	
	return 0;
}

ssize_t node_read(struct file *file, char *buffer, size_t length, loff_t *offset)
{
	int i, len = strlen(response) + 1;
	loff_t ofs = *offset;

	if(ofs >= len) return 0;

	if(ofs + length > len) length = len - ofs;

	for(i = ofs; i < len; i++) buffer[i] = (response+ofs)[i];

	*offset += length;

	return length;
}

ssize_t node_write(struct file *file, const char *buffer, size_t length, loff_t *offset)
{
        int i; 
        loff_t ofs = *offset;

        if(ofs >= BUF_SIZE-1) return 0;

        if(ofs + length > BUF_SIZE-1) length = BUF_SIZE - 1 - ofs;

        for(i = ofs; i < length; i++) (response+ofs)[i] = buffer[i];

        *offset += length;

        return length;

}

