#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#define SIZE 4096

int main(int argc, char **argv)
{
	int fd;
	char *msg;

	if((fd = open("/dev/mmap-radio", O_RDWR)) < 0)
	{
		printf("cannot make mmap\n");
		return -1;
	}

	if((msg = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED)
        {
                printf("cannot make mmap\n");
                return -1;
        }

	printf("kernel message: %s\n", msg);

	close(fd);
	return 0;
}
