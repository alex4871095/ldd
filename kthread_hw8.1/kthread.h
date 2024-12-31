#ifndef _KTHREAD_H_
#define _KTHREAD_H_

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/stat.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/sched/task.h>
#include <linux/sched/signal.h>
#include <linux/proc_fs.h>
#include <linux/string.h>

int radio_open(struct inode*, struct file*);
int radio_release(struct inode*, struct file*);
ssize_t radio_read(struct file*, char*, size_t, loff_t*);
ssize_t radio_write(struct file*, const char*, size_t, loff_t*); 

#endif /*_KTHREAD_H_ */
