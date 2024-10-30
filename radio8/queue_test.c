#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

extern int errno;

int main()
{
	int sz;
	int fd = open("/dev/radio", O_RDWR);
	char* c = (char*)calloc(100, sizeof(char));

	printf("fd for /dev/radio = %d\n", fd);

	printf("\n");

	if (fd == -1)
	{
		printf("Error Number % d\n", errno);
		perror("Program");
	}

	sz = read(fd, c, 100);
	printf("called read for empty queue: % s", c);

	printf("\n\n");

	sz = write(fd, "long message exceeding buffer size\n", strlen("long message exceeding buffer size\n"));
	printf("called write(% d, \"long message exceeding buffer size\\n\", %d)." " Returned value %d\n", fd, strlen("long message exceeding buffer size\n"), sz);

	sz = read(fd, c, 100);
	printf("called read: % s", c);

	printf("\n\n");

	printf("Testing queue size and order of write/read to confirm LIFO queue implementation(stack):\n");
	
	printf("\n");

	sz = write(fd, "message0\n", strlen("message0\n"));
	printf("called write(% d, \"message0\\n\", %d)." " Returned value %d\n", fd, strlen("message0\n"), sz);

        sz = write(fd, "message1\n", strlen("message1\n"));
        printf("called write(% d, \"message1\\n\", %d)." " Returned value %d\n", fd, strlen("message1\n"), sz);

        sz = write(fd, "message2\n", strlen("message2\n"));
        printf("called write(% d, \"message2\\n\", %d)." " Returned value %d\n", fd, strlen("message2\n"), sz);

        sz = write(fd, "message3\n", strlen("message3\n"));
        printf("called write(% d, \"message3\\n\", %d)." " Returned value %d\n", fd, strlen("message3\n"), sz);

        sz = write(fd, "message4\n", strlen("message4\n"));
        printf("called write(% d, \"message4\\n\", %d)." " Returned value %d\n", fd, strlen("message4\n"), sz);

        sz = write(fd, "message5\n", strlen("message5\n"));
        printf("called write(% d, \"message5\\n\", %d)." " Returned value %d\n", fd, strlen("message5\n"), sz);

        sz = write(fd, "message6\n", strlen("message6\n"));
        printf("called write(% d, \"message6\\n\", %d)." " Returned value %d\n", fd, strlen("message6\n"), sz);

        sz = write(fd, "message7\n", strlen("message7\n"));
        printf("called write(% d, \"message0\\n\", %d)." " Returned value %d\n", fd, strlen("message7\n"), sz);

        sz = write(fd, "message8\n", strlen("message8\n"));
        printf("called write(% d, \"message8\\n\", %d)." " Returned value %d\n", fd, strlen("message8\n"), sz);

        sz = write(fd, "message9\n", strlen("message9\n"));
        printf("called write(% d, \"message9\\n\", %d)." " Returned value %d\n", fd, strlen("message9\n"), sz);

        sz = write(fd, "message10\n", strlen("message10\n"));
        printf("called write(% d, \"message10\\n\", %d)." " Returned value %d\n", fd, strlen("message10\n"), sz);

	sz = read(fd, c, 100);
	printf("called read: % s", c);

        sz = read(fd, c, 100);
        printf("called read: % s", c);

        sz = read(fd, c, 100);
        printf("called read: % s", c);

        sz = read(fd, c, 100);
        printf("called read: % s", c);

        sz = read(fd, c, 100);
        printf("called read: % s", c);

        sz = read(fd, c, 100);
        printf("called read: % s", c);

        sz = read(fd, c, 100);
        printf("called read: % s", c);

        sz = read(fd, c, 100);
        printf("called read: % s", c);

        sz = read(fd, c, 100);
        printf("called read: % s", c);

        sz = read(fd, c, 100);
        printf("called read: % s", c);

	return 0;
}

