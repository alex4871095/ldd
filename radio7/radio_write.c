#include "radio.h"

ssize_t radio_write(struct file *file, const char *buffer, size_t length, loff_t *offset)
{
	int ofs = *offset;
	char *p;
	ssize_t len;

	int minor = iminor(file->f_inode);

	if(minor < 0) return -EIO;
	if(minor != 2) return -EACCES;

	if(ofs >= BUF_SIZE-1) return 0;

	if(ofs+length > BUF_SIZE) length = BUF_SIZE-1-ofs;

	for(p = r_buffer+ofs, len = length; len > 0; len--, p++, buffer++) get_user(*p, buffer);

	*offset += length;

	*p = 0;

	return length;
}
 
