#include "hello.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("user");

int init_module(void)
{
	int i;
	char str[32];

	my_alert(MOD_NAME, "started");
	for(i=0; i<10; i++) {
		sprintf(str, "%d", i);
		my_alert(MOD_NAME, str);
	}
	return 0;
}
