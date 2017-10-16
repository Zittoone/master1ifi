#ifndef __KERNEL__
#define __KERNEL__
#endif

#define MODULE
#include <linux/kernel.h>
#include <linux/module.h>

int init_module(void)
{
	printk(KERN_INFO "Hello, world\n");
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "Goodbye cruel world\n");
}

MODULE_LICENSE("GPL");
