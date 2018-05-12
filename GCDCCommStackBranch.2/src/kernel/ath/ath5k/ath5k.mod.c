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
	{ 0x5534c2ab, "ieee80211_rts_duration" },
	{ 0x3d06d196, "kmalloc_caches" },
	{ 0x822c8595, "pci_bus_read_config_byte" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x935865f7, "pci_release_region" },
	{ 0xab71b8af, "mem_map" },
	{ 0xb279da12, "pv_lock_ops" },
	{ 0x91eb9b4, "round_jiffies" },
	{ 0x486ac7c9, "led_classdev_register" },
	{ 0x9c64fbd, "ieee80211_frequency_to_channel" },
	{ 0x7c7da1, "ieee80211_beacon_get" },
	{ 0xa415bfa0, "pci_match_id" },
	{ 0x987dfcd, "pci_disable_device" },
	{ 0x267fc65b, "__tasklet_hi_schedule" },
	{ 0x8c35d732, "ieee80211_hdrlen" },
	{ 0x973873ab, "_spin_lock" },
	{ 0x4661e311, "__tracepoint_kmalloc" },
	{ 0x7bcd5eea, "ath_regd_init" },
	{ 0x6ba5b1fa, "ieee80211_unregister_hw" },
	{ 0xe13e9304, "x86_dma_fallback_dev" },
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0xee421be0, "init_timer_key" },
	{ 0x4033a043, "mutex_unlock" },
	{ 0x712aa29b, "_spin_lock_irqsave" },
	{ 0x7d11c268, "jiffies" },
	{ 0x80af08cf, "ieee80211_stop_queues" },
	{ 0xdbc8b479, "ieee80211_stop_queue" },
	{ 0x4f455fbd, "ieee80211_tx_status" },
	{ 0xc7e4befa, "pci_set_master" },
	{ 0xe910b532, "del_timer_sync" },
	{ 0x65c2ac01, "__ieee80211_rx" },
	{ 0x5bb63e06, "pci_set_dma_mask" },
	{ 0xd40b6af1, "dev_alloc_skb" },
	{ 0x935d5665, "pci_restore_state" },
	{ 0xebddcefb, "pci_iounmap" },
	{ 0xf78faa22, "__mutex_init" },
	{ 0xb72397d5, "printk" },
	{ 0xce7428eb, "ieee80211_wake_queues" },
	{ 0x9f2d613e, "param_set_bool" },
	{ 0xf397b9aa, "__tasklet_schedule" },
	{ 0xb6ed1e53, "strncpy" },
	{ 0x31219afb, "ath_is_world_regd" },
	{ 0x16305289, "warn_slowpath_null" },
	{ 0x8d9943d0, "skb_push" },
	{ 0x4a82e46c, "mutex_lock" },
	{ 0x4b07e779, "_spin_unlock_irqrestore" },
	{ 0xa5808bbf, "tasklet_init" },
	{ 0x6bafbced, "mod_timer" },
	{ 0x29625e53, "dma_release_from_coherent" },
	{ 0xfda85a7d, "request_threaded_irq" },
	{ 0x210a4718, "skb_pull" },
	{ 0x2f9b2ab0, "dev_kfree_skb_any" },
	{ 0x3b820abe, "dma_alloc_from_coherent" },
	{ 0xe523ad75, "synchronize_irq" },
	{ 0x5237a962, "ath_reg_notifier_apply" },
	{ 0x4293e8b, "wiphy_to_ieee80211_hw" },
	{ 0x79ad224b, "tasklet_kill" },
	{ 0x6ceb1647, "kmem_cache_alloc" },
	{ 0xc946787f, "pv_irq_ops" },
	{ 0xbe25b39d, "ath_regd_get_band_ctl" },
	{ 0xfe4d813a, "__ieee80211_get_rx_led_name" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0xdfaff0d5, "wiphy_rfkill_set_hw_state" },
	{ 0x3bd1b1f6, "msecs_to_jiffies" },
	{ 0xd18a9194, "dev_driver_string" },
	{ 0xd185f3a3, "__ieee80211_get_tx_led_name" },
	{ 0x150832b, "pci_unregister_driver" },
	{ 0xa0c4efd0, "ieee80211_generic_frame_duration" },
	{ 0x3e7af3dc, "ieee80211_get_hdrlen_from_skb" },
	{ 0xf6ebc03b, "net_ratelimit" },
	{ 0xcd0e0615, "pci_set_power_state" },
	{ 0xbce8cac3, "ieee80211_ctstoself_duration" },
	{ 0x5819290b, "pci_bus_write_config_byte" },
	{ 0x3bcaecbf, "ieee80211_register_hw" },
	{ 0x86451974, "led_classdev_unregister" },
	{ 0x8d66a3a, "warn_slowpath_fmt" },
	{ 0x3aa1dbcf, "_spin_unlock_bh" },
	{ 0x37a0cba, "kfree" },
	{ 0xe60fca89, "regulatory_hint" },
	{ 0x833103b9, "ieee80211_alloc_hw" },
	{ 0x9e1f48b9, "__pci_register_driver" },
	{ 0xa8c8accc, "ieee80211_free_hw" },
	{ 0x9214ed8a, "param_get_bool" },
	{ 0x76b0f8f8, "bad_dma_address" },
	{ 0x701d0ebd, "snprintf" },
	{ 0x8235805b, "memmove" },
	{ 0xfcc02974, "pci_iomap" },
	{ 0xcb357c21, "consume_skb" },
	{ 0x436c2179, "iowrite32" },
	{ 0x93cbd1ec, "_spin_lock_bh" },
	{ 0x77e98d91, "skb_put" },
	{ 0xcb99951a, "pci_enable_device" },
	{ 0x8f638a89, "pci_request_region" },
	{ 0x9e7d6bd0, "__udelay" },
	{ 0x1d541bd3, "dma_ops" },
	{ 0xe484e35f, "ioread32" },
	{ 0xf20dabd8, "free_irq" },
	{ 0xd802ee66, "pci_save_state" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=mac80211,led-class,cfg80211,ath";

MODULE_ALIAS("pci:v0000168Cd00000207sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000007sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000011sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000012sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000013sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000A727d00000013sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010B7d00000013sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00001014sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000014sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000015sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000016sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000017sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000018sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000019sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd0000001Asv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd0000001Bsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd0000001Csv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd0000001Dsv*sd*bc*sc*i*");

MODULE_INFO(srcversion, "16919058478AFC08AD305D9");
