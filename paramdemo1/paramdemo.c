#include <linux/module.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("fr487x@gmail.com alex");

/********************* global data *********************/

static int m_count = 1;
static char *m_char = "empty";

/******************** module params declaration ********/

module_param(m_count, int, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
MODULE_PARM_DESC(m_count, "module counter");

module_param(m_char, charp, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
MODULE_PARM_DESC(m_char, "module string");

int init_module(void)
{
	if(m_count == 1) 
	{
		printk(KERN_ALERT "default counter used, %s\n", m_char);
	}
	else
	{
               printk(KERN_ALERT "paramdemo data: %.*s\n", m_count, m_char);
	} 
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_ALERT "paramdemo exited\n");
	return;
}
