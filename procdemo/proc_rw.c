#include "procdemo.h"

ssize_t node_read(struct file *file, char *buffer, size_t length, loff_t *offset)
{
	int i, len = strlen(response) + 1;
	loff_t ofs = *offset;

	if(ofs >= len) return 0;

	if(ofs + length > len) length = len - ofs;

	for(i = ofs; i < len; i++) buffer[i] = (response+ofs)[i];

	*offset += length;

	return length;
}

ssize_t node_write(struct file *file, const char *buffer, size_t length, loff_t *offset)
{
        int i; 
        loff_t ofs = *offset;

        if(ofs >= BUF_SIZE-1) return 0;

        if(ofs + length > BUF_SIZE-1) length = BUF_SIZE - 1 - ofs;

        for(i = ofs; i < length; i++) (response+ofs)[i] = buffer[i];

        *offset += length;

        return length;

}





