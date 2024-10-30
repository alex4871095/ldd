#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("fr487x@gmail.com alex");

int param_rand(int low_border, int up_border, int *random_number)
{
	int range;

	range = up_border - low_border;
	get_random_bytes(random_number, sizeof(int));
	*random_number = *random_number % range;
	if (*random_number > low_border && *random_number < up_border)
	{
		return 0;
	}
	else
	{
		return -1; 
	}
} 

EXPORT_SYMBOL(param_rand);


