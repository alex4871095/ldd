#include "radio.h"
#include <linux/uaccess.h>

static char *msg = "this is radio speaking";

ssize_t radio_read(struct file *file, char *buffer, size_t length, loff_t *offset)
{
	int msg_length = strlen(msg) + 1; 
	int ofs = *offset;
	char *p;
	ssize_t len;
 
	if(ofs >= msg_length) return 0;

	if(ofs+length > msg_length) length = msg_length - ofs;

	for(p = msg+ofs, len = length; len >0; len--, p++, buffer++) put_user(*p, buffer); /* *buffer = *p; */

	*offset += length;	

	return length;
}

