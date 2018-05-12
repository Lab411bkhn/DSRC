#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xd27f8d03, "module_layout" },
	{ 0x3d06d196, "kmalloc_caches" },
	{ 0x4661e311, "__tracepoint_kmalloc" },
	{ 0xee421be0, "init_timer_key" },
	{ 0x712aa29b, "_spin_lock_irqsave" },
	{ 0x7d11c268, "jiffies" },
	{ 0xe2d5255a, "strcmp" },
	{ 0xe910b532, "del_timer_sync" },
	{ 0x8d3894f2, "_ctype" },
	{ 0xb72397d5, "printk" },
	{ 0x4b07e779, "_spin_unlock_irqrestore" },
	{ 0x5702a4ae, "add_timer" },
	{ 0x785a5e3e, "module_put" },
	{ 0x6ceb1647, "kmem_cache_alloc" },
	{ 0x37a0cba, "kfree" },
	{ 0x701d0ebd, "snprintf" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "41681A4220CE115180A4DCD");
