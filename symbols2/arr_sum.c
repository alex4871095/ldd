#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("fr487x@gmail.com alex");

int arr_sum(int arr[], int count)
{
	int i, sum=0;
	for(i=0; i<count; i++)
	{
		sum+=arr[i];
	}
	return sum;
} 

EXPORT_SYMBOL(arr_sum);


