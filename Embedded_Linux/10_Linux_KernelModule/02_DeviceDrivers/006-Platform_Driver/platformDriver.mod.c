#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
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
	{ 0xcd6bb128, "module_layout" },
	{ 0xb97ac27d, "class_destroy" },
	{ 0xebbf5644, "platform_driver_unregister" },
	{ 0xa73cd956, "__platform_driver_register" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0xda8ecfb, "__class_create" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x6d8c728f, "device_create" },
	{ 0xf5e9fff1, "_dev_err" },
	{ 0xa357695, "cdev_add" },
	{ 0xea471331, "cdev_init" },
	{ 0xe6a3016c, "sysfs_create_file_ns" },
	{ 0xd0da656b, "__stack_chk_fail" },
	{ 0x56470118, "__warn_printk" },
	{ 0x13c49cc2, "_copy_from_user" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0x3246abc4, "_dev_info" },
	{ 0x92997ed8, "_printk" },
	{ 0x2ac0ee24, "cdev_del" },
	{ 0xd21b20af, "device_destroy" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "53692AD77B38317A4A770BA");
