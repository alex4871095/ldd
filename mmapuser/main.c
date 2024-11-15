#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

#define FILEPATH "/dev/mmap-radio"
#define FILESIZE 4096

int main(int argc, char *argv[])
{
    int i, fd;
    char *map;

    printf("Main started\n");

    fd = open(FILEPATH, O_RDWR);
    if (fd == -1) {
	printf("Error opening file for reading\n");
	return -1;
    }

    printf("File opened sucessfully\n");

    map = (char*)mmap(0, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
	close(fd);
	printf("Error mmapping the file\n");
	return -1;
    }
    
    printf("File mapped successfully\n");

    printf("Initial content: %s\n", map);

    printf("Writing to mapped memory\n");

    memcpy (map + 28, "message from userspace", 22);

    printf("Changed content: %s\n", map);

    if (munmap(map, FILESIZE) == -1) {
	printf("Error un-mmapping the file\n");
	return -1;
    }
    close(fd);
    return 0;
}
