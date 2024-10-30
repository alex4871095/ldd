#include "radio.h"
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/fs.h>

ssize_t radio_read(struct file *file, char *buffer, size_t length, loff_t *offset)
{
	int ofs = *offset;
	char *p;
	size_t len;
 
	if(ofs >= length) return 0;

	if(ofs+length > length) length = length - ofs;

	for(p = buffer+ofs, len = length; len > 0; len--, p++, buffer++) put_user(*p, buffer); /* *buffer = *p; */

	*offset += length;	

	return length;
}

ssize_t radio_write(struct file *file, const char *buffer, size_t length, loff_t *offset)
{
	int ofs = *offset;
	char *p;
	size_t len;

	if(ofs >= length) return 0;

	if(ofs+length > length) length = length +ofs;

	p = kmalloc(length * sizeof(char *), GFP_KERNEL);

	memset(p, 0, length * sizeof(char *));

	for(p = buffer+ofs, len = length; len > 0; len--, p++, buffer++) get_user(*p, buffer); 

	*offset += length;

	/* Is it possible to update size of our character device, so it would be possible to store our written data somewhere? */

	return length;
}


