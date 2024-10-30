#include "radio.h"
#include <linux/uaccess.h>

static char *array_msg[] = 
{
	"this is radio0 speaking",
	"this is radio1 speaking"
};

ssize_t radio_read(struct file *file, char *buffer, size_t length, loff_t *offset)
{
	char *msg;
	int msg_length; 
	int ofs = *offset;
	char *p;
	ssize_t len;

	int minor = iminor(file->f_inode);
 
	if(minor < 0) return -EIO;
	if(minor > 1) return -EINVAL;

	if(strlen(r_buffer) > 0) msg = r_buffer;
	else msg = array_msg[minor];
	msg_length = strlen(msg);

	if(ofs >= msg_length) 
	{
		*r_buffer = 0;
		return 0;
	}

	if(ofs+length > msg_length) length = msg_length - ofs;

	for(p = msg+ofs, len = length; len >0; len--, p++, buffer++) put_user(*p, buffer); /* *buffer = *p; */

	*offset += length;	

	return length;
}

