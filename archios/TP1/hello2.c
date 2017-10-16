#ifndef __KERNEL__
#define __KERNEL__
#endif

#define MODULE
#include <linux/kernel.h>
#include <linux/module.h>

#include <linux/init.h>

int __init init_hello(void)
{
	printk(KERN_INFO "Hello, world\n");
	return 0;
}

void __exit cleanup_hello(void)
{
	printk(KERN_INFO "Goodbye cruel world\n");
}

module_init(init_hello);
module_exit(cleanup_hello);

MODULE_LICENSE("GPL");
