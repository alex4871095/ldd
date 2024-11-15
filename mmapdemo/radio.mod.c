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
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x92997ed8, "_printk" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x7cd8d75e, "page_offset_base" },
	{ 0x97651e6c, "vmemmap_base" },
	{ 0xbcb36fe4, "hugetlb_optimize_vmemmap_key" },
	{ 0x4c9d28b0, "phys_base" },
	{ 0x767648eb, "kmalloc_caches" },
	{ 0x4c1b64b8, "kmalloc_trace" },
	{ 0xf09b5d9a, "get_zeroed_page" },
	{ 0x4302d0eb, "free_pages" },
	{ 0x37a0cba, "kfree" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x447ed437, "__class_create" },
	{ 0x63368355, "device_create" },
	{ 0x29c8d1e2, "cdev_init" },
	{ 0x9db44770, "cdev_add" },
	{ 0x48866329, "device_destroy" },
	{ 0x18ff729f, "class_destroy" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0xf3005208, "cdev_del" },
	{ 0x9b9daf0, "module_layout" },
};

MODULE_INFO(depends, "");

