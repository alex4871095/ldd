#include "time_kernel.h"
#include <linux/timekeeping.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("fr487x@gmail.com alex");

int init_module(void)
{
	struct timespec64 i;
	printk(KERN_ALERT MOD_NAME " started\n");
	ktime_get_real_ts64(&i);
	long int y=i.tv_sec;
	int year=1970 + y/31536000;
	int month=(y%31536000+13*86400)/2628000;
	int day=((y%31536000+13*86400)%2628000)/86400;
	int hour=(((y%31536000+13*86400)%2628000)%8640)/3600;
	int minute=((((y%31536000+13*86400)%2628000)%8640)%3600)/60;
	printk(KERN_ALERT "Current time in seconds - %ld\n", y);
	printk(KERN_ALERT "%d %d %d %d %d\n", year, month, day, hour, minute); 
	return 0;
}
