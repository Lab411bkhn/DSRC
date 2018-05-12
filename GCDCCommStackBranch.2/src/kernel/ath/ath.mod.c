#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xd27f8d03, "module_layout" },
	{ 0xa704ee6f, "freq_reg_info" },
	{ 0xb72397d5, "printk" },
	{ 0x16305289, "warn_slowpath_null" },
	{ 0xab7e9369, "wiphy_apply_custom_regulatory" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=cfg80211";


MODULE_INFO(srcversion, "F3D4ABEB3B6B1AC2000A799");
