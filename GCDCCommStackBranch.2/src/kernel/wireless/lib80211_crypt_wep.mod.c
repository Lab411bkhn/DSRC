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
	{ 0xb72397d5, "printk" },
	{ 0x79aa04a2, "get_random_bytes" },
	{ 0xff1ff7cd, "crypto_alloc_base" },
	{ 0x4661e311, "__tracepoint_kmalloc" },
	{ 0x6ceb1647, "kmem_cache_alloc" },
	{ 0x3d06d196, "kmalloc_caches" },
	{ 0x4871de03, "lib80211_register_crypto_ops" },
	{ 0x37a0cba, "kfree" },
	{ 0x5418ef70, "crypto_destroy_tfm" },
	{ 0x77e98d91, "skb_put" },
	{ 0x8d9943d0, "skb_push" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x9fb4c618, "skb_trim" },
	{ 0x210a4718, "skb_pull" },
	{ 0x8235805b, "memmove" },
	{ 0xa34f1ef5, "crc32_le" },
	{ 0x5c265cba, "sg_init_one" },
	{ 0x5152e605, "memcmp" },
	{ 0x3c2c5af5, "sprintf" },
	{ 0xed5a0aed, "lib80211_unregister_crypto_ops" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=lib80211";


MODULE_INFO(srcversion, "B592278D88109496B8C289F");
