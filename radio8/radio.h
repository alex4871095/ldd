#ifndef _RADIO_H_
#define _RADIO_H_

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/msg.h>
#include <linux/ipc.h>
#include <linux/uaccess.h>

#define DEV_NAME "radio"
#define BUF_SIZE 20
#define QUEUE_SIZE 10

struct mbuf {
        struct mbuf *next;
        struct mbuf *prev;
        char text[BUF_SIZE];
};

struct queue {
        struct mbuf *head;
        int count;
};

int radio_open(struct inode*, struct file*);
int radio_release(struct inode*, struct file*);

ssize_t radio_read(struct file*, char*, size_t, loff_t*);
ssize_t radio_write(struct file*, const char*, size_t, loff_t*);

#endif /*_RADIO_H_*/
