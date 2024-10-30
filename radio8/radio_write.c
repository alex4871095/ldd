#include "radio.h"

extern struct mbuf* buf;
extern struct queue* q;

ssize_t radio_write(struct file *file, const char *buffer, size_t length, loff_t *offset)
{
	ssize_t l;
	char *p;

	int minor = iminor(file->f_inode);

	if(minor != 1) return -EIO;

	if(q == NULL)
	{
		printk(KERN_ALERT DEV_NAME " queue is empty; setup queue and filling first element\n");

		buf = (struct mbuf*) kmalloc(sizeof(struct mbuf), GFP_KERNEL);
		q = (struct queue*) kmalloc(sizeof(struct queue), GFP_KERNEL);
		buf->next = NULL;
		buf->prev = NULL;
		q->head = NULL;
		q->count = 0;

		printk(KERN_ALERT DEV_NAME " queue and mbuf initialized, %p, %p", q, buf);

		if(length > BUF_SIZE && length > 0) length = BUF_SIZE;
		for(p = buf->text, l = length; l > 0; l--, p++, buffer++) get_user(*p, buffer);
		q->head = buf;
		q->count = 1;	
		printk(KERN_ALERT DEV_NAME " queue size %d", q->count); 
		printk(KERN_ALERT DEV_NAME " buf address = %p\n", buf);
		return length;
	}
	else if(q->count == QUEUE_SIZE)
	{
		printk(KERN_ALERT DEV_NAME " queue is full\n");
		return -EBUSY;
	}
	else
	{
		printk(KERN_ALERT DEV_NAME " adding new element to queue\n");
		while (buf->next != NULL)
		{
			buf = buf->next;
		}
		struct mbuf* new_buf = (struct mbuf*) kmalloc(sizeof(struct mbuf), GFP_KERNEL);
		if(length > BUF_SIZE && length > 0) length = BUF_SIZE;
                for(p = new_buf->text, l = length; l > 0; l--, p++, buffer++) get_user(*p, buffer);
		new_buf->next = NULL;
		buf->next = new_buf;
		new_buf->prev = buf;
		q->count++;
		printk(KERN_ALERT DEV_NAME " queue size %d", q->count);     
		printk(KERN_ALERT DEV_NAME " buf address = %p\n", new_buf);
		return length;
	}

	return -1;
}
 
