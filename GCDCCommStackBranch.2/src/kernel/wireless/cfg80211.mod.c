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
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x405c1144, "get_seconds" },
	{ 0x3ed3274d, "rfkill_set_sw_state" },
	{ 0xcff53400, "kref_put" },
	{ 0x528c709d, "simple_read_from_buffer" },
	{ 0x61ec53b4, "debugfs_create_dir" },
	{ 0xb279da12, "pv_lock_ops" },
	{ 0xd0d8621b, "strlen" },
	{ 0x44961a, "genl_sock" },
	{ 0xea6fcdaa, "genl_unregister_family" },
	{ 0xdabc058f, "platform_device_register_simple" },
	{ 0xc7a4fbed, "rtnl_lock" },
	{ 0x973873ab, "_spin_lock" },
	{ 0xc633495b, "schedule_work" },
	{ 0x4661e311, "__tracepoint_kmalloc" },
	{ 0x63ecad53, "register_netdevice_notifier" },
	{ 0x23869dc7, "cancel_work_sync" },
	{ 0x4033a043, "mutex_unlock" },
	{ 0x3ac8a26, "rfkill_register" },
	{ 0x4eb8e170, "debugfs_create_file" },
	{ 0x5f120978, "debugfs_rename" },
	{ 0x3c2c5af5, "sprintf" },
	{ 0x7d11c268, "jiffies" },
	{ 0xfe769456, "unregister_netdevice_notifier" },
	{ 0x9fb4c618, "skb_trim" },
	{ 0xe2d5255a, "strcmp" },
	{ 0x41344088, "param_get_charp" },
	{ 0xd5c893e6, "device_del" },
	{ 0x37befc70, "jiffies_to_msecs" },
	{ 0xe5abda8b, "rfkill_alloc" },
	{ 0xf78faa22, "__mutex_init" },
	{ 0xb72397d5, "printk" },
	{ 0x42224298, "sscanf" },
	{ 0xafe79e22, "class_unregister" },
	{ 0x7a539869, "rfkill_set_hw_state" },
	{ 0xc0580937, "rb_erase" },
	{ 0x598c4f03, "nla_put" },
	{ 0x3ccbfa04, "wireless_send_event" },
	{ 0x5f3ec7af, "debugfs_remove" },
	{ 0x16305289, "warn_slowpath_null" },
	{ 0x8d9943d0, "skb_push" },
	{ 0x4a82e46c, "mutex_lock" },
	{ 0x48305264, "dev_close" },
	{ 0xdd3ec25, "dev_get_by_index" },
	{ 0x59f9cd62, "netlink_unicast" },
	{ 0x5a37ed92, "platform_device_unregister" },
	{ 0x856d31f1, "rfkill_pause_polling" },
	{ 0x44ef0b1f, "genl_register_family_with_ops" },
	{ 0x1d8e504a, "sysfs_remove_link" },
	{ 0x46bddbda, "device_add" },
	{ 0x210a4718, "skb_pull" },
	{ 0x4f0fde49, "init_net" },
	{ 0x15774d0a, "__class_register" },
	{ 0x542fc2d7, "__dev_get_by_index" },
	{ 0x9b6eb137, "ksize" },
	{ 0x833c69a4, "kobject_uevent_env" },
	{ 0x61651be, "strcat" },
	{ 0xd3039376, "rfkill_resume_polling" },
	{ 0x872c003, "sysfs_create_link" },
	{ 0x6ceb1647, "kmem_cache_alloc" },
	{ 0x5a9c3930, "__alloc_skb" },
	{ 0xdeb976d2, "netlink_broadcast" },
	{ 0xef63d4df, "put_device" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0xa58b6804, "nla_parse" },
	{ 0x3bd1b1f6, "msecs_to_jiffies" },
	{ 0x8c982707, "kfree_skb" },
	{ 0xaf882103, "pskb_expand_head" },
	{ 0xf8edda6c, "device_rename" },
	{ 0xa6dcc773, "rb_insert_color" },
	{ 0x6ad065f4, "param_set_charp" },
	{ 0x3aa1dbcf, "_spin_unlock_bh" },
	{ 0x3ae831b6, "kref_init" },
	{ 0x37a0cba, "kfree" },
	{ 0x63ec9a33, "rfkill_destroy" },
	{ 0x801678, "flush_scheduled_work" },
	{ 0x8a1203a9, "kref_get" },
	{ 0x5f8ba128, "device_initialize" },
	{ 0x1544aad4, "genl_register_mc_group" },
	{ 0x74024c41, "rfkill_blocked" },
	{ 0x374ed073, "scnprintf" },
	{ 0x701d0ebd, "snprintf" },
	{ 0x5c57c2a6, "dev_set_name" },
	{ 0x93cbd1ec, "_spin_lock_bh" },
	{ 0x77e98d91, "skb_put" },
	{ 0x80eb9c11, "rfkill_unregister" },
	{ 0x6e720ff2, "rtnl_unlock" },
	{ 0xc2d711e1, "krealloc" },
	{ 0xe914e41e, "strcpy" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "2703616A581EFFFB58981DF");
