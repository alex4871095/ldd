#include "hello.h"

void cleanup_module(void)
{
	my_alert(MOD_NAME, "exited");
	return;
}
