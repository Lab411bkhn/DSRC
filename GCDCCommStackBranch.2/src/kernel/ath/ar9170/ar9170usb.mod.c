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
	{ 0xd1895253, "ieee80211_rx_irqsafe" },
	{ 0x3d06d196, "kmalloc_caches" },
	{ 0xf9a482f9, "msleep" },
	{ 0x97b85c21, "usb_buffer_alloc" },
	{ 0xb0eedea9, "usb_wait_anchor_empty_timeout" },
	{ 0x486ac7c9, "led_classdev_register" },
	{ 0x7c7da1, "ieee80211_beacon_get" },
	{ 0x222eab29, "usb_driver_set_configuration" },
	{ 0x65d7d5ef, "usb_get_from_anchor" },
	{ 0x4661e311, "__tracepoint_kmalloc" },
	{ 0x7bcd5eea, "ath_regd_init" },
	{ 0xbdbb615d, "usb_buffer_free" },
	{ 0x23869dc7, "cancel_work_sync" },
	{ 0x2486b6e, "queue_work" },
	{ 0x6ba5b1fa, "ieee80211_unregister_hw" },
	{ 0xee421be0, "init_timer_key" },
	{ 0x381c4bb1, "cancel_delayed_work_sync" },
	{ 0x4033a043, "mutex_unlock" },
	{ 0x712aa29b, "_spin_lock_irqsave" },
	{ 0xbe67a2d, "__ieee80211_get_assoc_led_name" },
	{ 0x7d11c268, "jiffies" },
	{ 0x9fb4c618, "skb_trim" },
	{ 0x1bea8cb9, "usb_unanchor_urb" },
	{ 0xdbc8b479, "ieee80211_stop_queue" },
	{ 0xffc7c184, "__init_waitqueue_head" },
	{ 0x69864295, "skb_queue_purge" },
	{ 0xd40b6af1, "dev_alloc_skb" },
	{ 0x13b5c170, "usb_lock_device_for_reset" },
	{ 0x6a4450fc, "usb_deregister" },
	{ 0x34908c14, "print_hex_dump_bytes" },
	{ 0xf78faa22, "__mutex_init" },
	{ 0xb72397d5, "printk" },
	{ 0x9f2d613e, "param_set_bool" },
	{ 0xaadbf11a, "usb_control_msg" },
	{ 0x31219afb, "ath_is_world_regd" },
	{ 0x16305289, "warn_slowpath_null" },
	{ 0x8d9943d0, "skb_push" },
	{ 0x4a82e46c, "mutex_lock" },
	{ 0x4b07e779, "_spin_unlock_irqrestore" },
	{ 0x210a4718, "skb_pull" },
	{ 0x4c759827, "byte_rev_table" },
	{ 0x21b1401d, "flush_workqueue" },
	{ 0x2f9b2ab0, "dev_kfree_skb_any" },
	{ 0x5237a962, "ath_reg_notifier_apply" },
	{ 0x4293e8b, "wiphy_to_ieee80211_hw" },
	{ 0xf3f86d0d, "dev_kfree_skb_irq" },
	{ 0xe0395440, "skb_queue_tail" },
	{ 0xadbea9f9, "usb_submit_urb" },
	{ 0x6ceb1647, "kmem_cache_alloc" },
	{ 0x5a9c3930, "__alloc_skb" },
	{ 0x1055c6fd, "usb_get_dev" },
	{ 0x100c13c6, "usb_kill_anchored_urbs" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x6c3a2a82, "usb_reset_device" },
	{ 0x3bd1b1f6, "msecs_to_jiffies" },
	{ 0x6cdb7c00, "usb_put_dev" },
	{ 0x6615da6a, "ieee80211_tx_status_irqsafe" },
	{ 0x8c982707, "kfree_skb" },
	{ 0x6b2dc060, "dump_stack" },
	{ 0xe348b5e6, "ieee80211_get_buffered_bc" },
	{ 0xd18a9194, "dev_driver_string" },
	{ 0xd185f3a3, "__ieee80211_get_tx_led_name" },
	{ 0xa28d8527, "usb_poison_anchored_urbs" },
	{ 0xa09d2ad9, "ieee80211_wake_queue" },
	{ 0xf6ebc03b, "net_ratelimit" },
	{ 0x3bcaecbf, "ieee80211_register_hw" },
	{ 0x86451974, "led_classdev_unregister" },
	{ 0x3aa1dbcf, "_spin_unlock_bh" },
	{ 0x37a0cba, "kfree" },
	{ 0xe60fca89, "regulatory_hint" },
	{ 0x833103b9, "ieee80211_alloc_hw" },
	{ 0x3f1899f1, "up" },
	{ 0x9c02eb51, "usb_register_driver" },
	{ 0x424751e5, "request_firmware" },
	{ 0xa8c8accc, "ieee80211_free_hw" },
	{ 0x7be44742, "skb_dequeue" },
	{ 0x9214ed8a, "param_get_bool" },
	{ 0x7055c315, "usb_ifnum_to_if" },
	{ 0xe456bd3a, "complete" },
	{ 0x701d0ebd, "snprintf" },
	{ 0xcb357c21, "consume_skb" },
	{ 0x9984c858, "usb_unpoison_anchored_urbs" },
	{ 0x93cbd1ec, "_spin_lock_bh" },
	{ 0x77e98d91, "skb_put" },
	{ 0x3e1f073d, "wait_for_completion_timeout" },
	{ 0x9c26bccc, "usb_free_urb" },
	{ 0xb703911e, "release_firmware" },
	{ 0x7d008222, "queue_delayed_work" },
	{ 0xa02fa422, "usb_anchor_urb" },
	{ 0x36cb4adf, "usb_alloc_urb" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=mac80211,led-class,ath,cfg80211";

MODULE_ALIAS("usb:v0CF3p9170d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0CF3p1001d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0CF3p1002d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:vCACEp0300d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v07D1p3C10d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0846p9010d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0846p9001d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0ACEp1221d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0586p3417d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0CDEp0023d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0CDEp0026d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v083ApF522d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v2019p5304d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v04BBp093Fd*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v057Cp8401d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v057Cp8402d*dc*dsc*dp*ic*isc*ip*");

MODULE_INFO(srcversion, "CEE1E12CC6F32A66DC7B4AE");
