#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif


static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x447ed437, "__class_create" },
	{ 0x18ff729f, "class_destroy" },
	{ 0xc8944ff, "__put_task_struct" },
	{ 0xb7f009aa, "send_sig_info" },
	{ 0xb3f7646e, "kthread_should_stop" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0xf513657, "wake_up_process" },
	{ 0x92997ed8, "_printk" },
	{ 0xd0da656b, "__stack_chk_fail" },
	{ 0x296695f, "refcount_warn_saturate" },
	{ 0x3384bde0, "init_task" },
	{ 0x9db44770, "cdev_add" },
	{ 0x63368355, "device_create" },
	{ 0xc3aaf0a9, "__put_user_1" },
	{ 0x5a921311, "strncmp" },
	{ 0xfe57f790, "kthread_stop" },
	{ 0xfb578fc5, "memset" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0xf558ab2c, "kthread_create_on_node" },
	{ 0x167e7f9d, "__get_user_1" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x48866329, "device_destroy" },
	{ 0x41ed3709, "get_random_bytes" },
	{ 0x754d539c, "strlen" },
	{ 0xf9a482f9, "msleep" },
	{ 0x29c8d1e2, "cdev_init" },
	{ 0xeb233a45, "__kmalloc" },
	{ 0x9b9daf0, "module_layout" },
};

MODULE_INFO(depends, "");

