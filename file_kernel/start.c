#include "file_kernel.h"
#include <linux/timekeeping.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("fr487x@gmail.com alex");

int init_module(void)
{
	printk(KERN_ALERT MOD_NAME " started\n");

	char message[]="message from kernel module\n";
	char file_path[]="/home/alex/work/file_kernel/notes";
	ssize_t ret_code=0;
	struct file* fd;

	printk(KERN_ALERT "Opening file");
	fd = filp_open(file_path, O_WRONLY|O_CREAT, 0644);

	if (fd == NULL) {
		printk(KERN_ALERT "Error opening file\n");
		return 1;
	}

	ret_code = kernel_write(fd, message, sizeof(message), &fd->f_pos);
	printk(KERN_ALERT "ret_code = %ld\n", ret_code);
	printk(KERN_ALERT "Closing file\n");
	filp_close(fd, NULL);
	return 0;
}
