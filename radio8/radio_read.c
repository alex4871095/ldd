#include "radio.h"

extern struct mbuf* buf;
extern struct queue* q;

ssize_t radio_read(struct file *file, char *buffer, size_t length, loff_t *offset)
{
	ssize_t l;
	char *p;

	int minor = iminor(file->f_inode);
 
	if(minor != 1) return -EIO;

	if(q == NULL)
	{
		printk(KERN_ALERT DEV_NAME " queue is empty, nothing to read\n");
		return 0;
	}
	else 
	{
		printk(KERN_ALERT DEV_NAME " reading %d element from queue\n", q->count);
		buf = q->head;
		if(buf == NULL) return -1;
		while (buf->next != NULL)
		{
			buf = buf->next;
		}
		printk(KERN_ALERT DEV_NAME " buf address = %p", buf);
		if(length > BUF_SIZE) length = BUF_SIZE;
		for(p = buf->text, l = length; l > 0; l--, p++, buffer++) put_user(*p, buffer);
		if(buf->prev != NULL) buf->prev->next = NULL;
		q->count--;
		kfree(buf);
		if(q->count == 0)
		{
			kfree(q);
			q = NULL;
			buf = NULL;
		}
		return length;
	}
}

