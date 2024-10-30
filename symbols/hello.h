#ifndef _HELLO_H_
#define _HELLO_H_

#include <linux/module.h>

#define MOD_NAME "hello"

extern int my_alert(const char*, const char*);

#endif /* _HELLO_H_ */
