#include <asm/fpu/api.h>
#include "fpu_kernel.h"

int fpu_ops(void)
{
	kernel_fpu_begin();
	double a=0.25, b=0.25, c, x;
	c = a+b;
	int int_c = (int) c;
	x = c-int_c;
	int frac_c = (int) (x*10);
	printk(KERN_ALERT "%d.%d\n", int_c, frac_c);
	kernel_fpu_end();
	return 0;
}
