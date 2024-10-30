#ifndef _RADIO_H_
#define _RADIO_H_

#include <linux/module.h>

#define DEV_NAME "radio"

int radio_open(struct inode*, struct file*);
int radio_release(struct inode*, struct file*);

ssize_t radio_read(struct file*, char*, size_t, loff_t*);

#endif /*_RADIO_H_*/
