/**
 * @file calm.h
 * @brief CALM device driver framework.
 *
 * Passing CALM management requests and indications on the management link
 * between the CDDF and the IME.  Since it is local communication, we do not
 * have to care with byte ordering issues.
 *
 * Reference document: ISO 21218.
 */

#ifndef _LINUX_CALM_H
#define _LINUX_CALM_H

#ifdef __KERNEL__
#include <net/genetlink.h>
#endif

/**
 * @defgroup netlink CALM netlink stuff.
 * @{
 */

/**
 * Generic netlink parameters.
 *
 * @defgroup netlinkparams CALM netlink parameters.
 * @ingroup netlink
 * @{
 */
#define CALM_FAMILY 0x18  /**< Generic netlink family type. */
#define CALM_VERSION 0x01 /**< Generic netlink family version. */
/** @} */

/**
 * Netlink primitives.
 *
 * @defgroup netlinkprimitives CALM netlink primitives.
 * @ingroup netlink
 * @{
 */
enum {
	CALM_C_UNSPEC,
	CALM_C_GET, /**< GET primitive. */
	CALM_C_SET, /**< SET primitive. */
	CALM_C_CMD, /**< CMD primitive. */
	CALM_C_REQ, /**< REQ primitive. */
	__CALM_C_MAX,
};
#define CALM_C_MAX (__CALM_C_MAX - 1)
/** @} */

#define VCI_DEFAULT_INACTIVITY_LIMIT_MS (60 * 1000)
//#define VCI_DEFAULT_INACTIVITY_LIMIT_MS (2 * 1000)

/**
 * Netlink attributes.
 *
 * @defgroup netlinkattrs CALM netlink attributes.
 * @ingroup netlink
 * @{
 */
enum {
	CALM_A_UNSPEC,
	CALM_A_CILIST,          /**< CILIST attribute. */
	CALM_A_CILIST_CI,       /**< CILIST_CI attribute. */
	CALM_A_VCILIST,         /**< VCILIST attribute. */
	CALM_A_VCILIST_VCI,     /**< VCILIST_VCI attribute. */
	CALM_A_AUXCH,           /**< AUXCH attribute. */
	CALM_A_CTRLCH,          /**< CTRLCH attribute. */
	CALM_A_SERVCH,          /**< SERVCH attribute. */
	CALM_A_RXSENS,          /**< RXSENS attribute. */
	CALM_A_TXPWR,           /**< TXPWR attribute. */
	CALM_A_DATARATE,        /**< DATARATE attribute. */
	CALM_A_DIR,             /**< DIR attribute. */
	CALM_A_DIR_MODE,        /**< DIR_MODE attribute. */
	CALM_A_DIR_PREDEF,      /**< DIR_PREDEF attribute. */
	CALM_A_DIR_BSAZIMUTH,   /**< DIR_BSAZIMUTH attribute. */
	CALM_A_DIR_BSELEVATION, /**< DIR_BSELEVATION attribute. */
	CALM_A_DIR_OPENHORIZ,   /**< DIR_OPENHORIZ attribute. */
	CALM_A_DIR_OPENVERT,    /**< DIR_OPENVERT attribute. */
    CALM_A_RELIABILITY,     /**< RELIABILITY attribute */    
	CALM_A_BLOCKLEN,        /**< BLOCKLEN attribute. */
	CALM_A_MINPRIO,         /**< MINPRIO attribute. */
	CALM_A_LASTRX,          /**< LASTRX attribute. */
	CALM_A_LASTRX_SEC,      /**< LASTRX_SEC attribute. */
	CALM_A_LASTRX_USEC,     /**< LASTRX_USEC attribute. */
	CALM_A_MAXINACT,        /**< MAXINACT attribute. */
	CALM_A_PEERDIST,        /**< PEERDIST attribute. */
	CALM_A_CICLASS,         /**< CICLASS attribute. */
	CALM_A_COMMRANGEREF,    /**< COMMRANGEREF attribute. */
	CALM_A_MINSUSPPRIO,     /**< MINSUSPPRIO attribute. */
	CALM_A_MEDTYPE,         /**< MEDTYPE attribute. */
	CALM_A_COMMODES,        /**< COMMODES attribute. */
	CALM_A_CIACCESSCLASS,   /**< CIACCESSCLASS attribute. */
	CALM_A_REGINFO,         /**< REGINFO attribute. */
	CALM_A_REGINFO_STATE,   /**< REGINFO_STATE attribute. */
	CALM_A_REGINFO_LIMITS,  /**< REGINFO_LIMITS attribute. */
	CALM_A_FREEAIRTIME,     /**< FREEAIRTIME attribute. */
	CALM_A_MEDUSAGE,        /**< MEDUSAGE attribute. */
	CALM_A_MEDUSAGE_RX,     /**< MEDUSAGE_RX attribute. */
	CALM_A_MEDUSAGE_TX,     /**< MEDUSAGE_TX attribute. */
	CALM_A_MEDUSEOBSTIME,   /**< MEDUSEOBSTIME attribute. */
	CALM_A_SUSPSUPPORTED,   /**< SUSPSUPPORTED attribute. */
	CALM_A_QUEUETHR,        /**< QUEUETHR attribute. */
	CALM_A_QUEUETHR_LOW,    /**< QUEUETHR_LOW attribute. */
	CALM_A_QUEUETHR_HIGH,   /**< QUEUETHR_HIGH attribute. */
	CALM_A_QUEUE,           /**< QUEUE attribute. */
	CALM_A_QUEUE_PRIO,      /**< QUEUE_PRIO attribute. */
	CALM_A_QUEUE_LEVEL,     /**< QUEUE_LEVEL attribute. */
	CALM_A_MACADDR,         /**< MACADDR attribute. */
	CALM_A_MAXFRAMELEN,     /**< MAXFRAMELEN attribute. */
	CALM_A_CISTATE,         /**< CISTATE attribute. */
	CALM_A_NOTIFY,          /**< NOTIFY attribute. */
	CALM_A_NOTIFY_PARAM,    /**< NOTIFY_PARAM attribute. */
	CALM_A_MINPRIOCROSSCI,  /**< MINPRIOCROSSCI attribute. */
	CALM_A_CCKID,			/**< CCKID attribute */
	CALM_A_PEERMAC,         /**< PEERMAC attribute. */
	CALM_A_PEERMAC_ADDR,    /**< PEERMAC_ADDR attribute. */
	CALM_A_PEERMAC_LEN,     /**< PEERMAC_LEN attribute. */
	CALM_A_IFINDEX,         /**< IFINDEX attribute. */
	CALM_A_ERR,             /**< ERR attribute. */
	CALM_A_ERR_ATTR,        /**< ERR_ATTR attribute. */
	CALM_A_ERR_CODE,        /**< ERR_CODE attribute. */
	CALM_A_CISTATECMD,      /**< CISTATECMD attribute. */
	CALM_A_WAKEUP,          /**< WAKEUP attribute. */
	CALM_A_VENDOR,          /**< VENDOR attribute. */
	CALM_A_VCI,             /**< VCI attribute. */
	CALM_A_MONITOR,         /**< MONITOR attribute. */
	CALM_A_MONITOR_PARAM,   /**< MONITOR_PARAM attribute. */
	CALM_A_MONITOR_ACTIVE,  /**< MONITOR_ACTIVE attribute. */
	CALM_A_UNITDATA,        /**< UNITDATA attribute. */
	CALM_A_UNITDATA_SSAP,   /**< UNITDATA_SSAP attribute. */
	CALM_A_UNITDATA_SRCCCK, /**< UNITDATA_SRCCCK attribute (CCK-ID). */
	CALM_A_UNITDATA_SRCCIID,/**< UNITDATA_SRCCIID attribute (CI-ID w/o CCK-ID). */
	CALM_A_UNITDATA_DSAP,   /**< UNITDATA_DSAP attribute. */
	CALM_A_UNITDATA_DSTCCK, /**< UNITDATA_DSTCCK attribute (CCK-ID). */
	CALM_A_UNITDATA_DSTCIID,/**< UNITDATA_DSTCIID attribute (CI-ID w/o CCK-ID). */
	CALM_A_UNITDATA_PRIO,   /**< UNITDATA_PRIO attribute. */
	CALM_A_UNITDATA_DATA,   /**< UNITDATA_DATA attribute. */
	CALM_A_UNITDATA_PARAM,  /**< UNITDATA_PARAM attribute. */
	CALM_A_EVENT,           /**< EVENT attribute. */
	CALM_A_EVENT_TYPE,      /**< EVENT_TYPE attribute. */
	CALM_A_EVENT_VAL,       /**< EVENT_VAL attribute. */
	__CALM_A_MAX,
};
#define CALM_A_MAX (__CALM_A_MAX - 1)
/** @} */

/**
 * CI-ID.  Mostly it is used without the CCK-ID to refer to locally available
 * CIs.
 */
struct ci_id {
	__u8 ctrlci;  /**< CtrlCI. */
	__u16 serial; /**< Serial number. */
	__u8 medid;   /**< Medium identifier. */
	__u8 cckid;   /**< CCK identifier. */
};

/**
 * DL-SAP address.
 */
struct dl_sap_address {
	__u8 c_sap_address;
	struct ci_id ci_id;
};

/**
 * @defgroup netlinkhdr CALM netlink header.
 * @ingroup netlink
 * @{
 */

/**
 * Family-specific generic netlink header.
 */
struct calm_head {
	__u32 ci_id; /**< Virtual Communication Interface identifier. */
};

/**
 * Length of CALM family-specific netlink header.
 */
#define CALM_HDRLEN NLMSG_ALIGN(sizeof(struct calm_head))

#if defined(__LITTLE_ENDIAN) || (__BYTE_ORDER == __LITTLE_ENDIAN)
/** Get medium identifier from ci_id.  */
#define CALM_GET_MEDID(ci_id) (ci_id & 0x000000ff)
/** Get serial number from ci_id. */
#define CALM_GET_SERIAL(ci_id) ((ci_id & 0x00ffff00) >> 8)
/** Get CTRLCI from ci_id. */
#define CALM_GET_CTRLCI(ci_id) ((ci_id & 0xff000000) >> 24)
/** Set medium identifier in ci_id. */
#define CALM_SET_MEDID(ci_id, medid) (ci_id = \
		(ci_id & 0xffffff00) | (medid & 0x000000ff))
/** Set serial number in ci_id. */
#define CALM_SET_SERIAL(ci_id, serial) (ci_id = \
		(ci_id & 0xff0000ff) | ((serial & 0x0000ffff) << 8))
/** Set CTRLCI in ci_id. */
#define CALM_SET_CTRLCI(ci_id, ctrlci) (ci_id = \
		(ci_id & 0x00ffffff) | ((ctrlci & 0x000000ff) << 24))
#else
#if defined(__BIG_ENDIAN) || (__BYTE_ORDER == __BIG_ENDIAN)
/** Get medium identifier from ci_id.  */
#define CALM_GET_MEDID(ci_id) ((ci_id & 0xff000000) >> 24)
/** Get serial number from ci_id. */
#define CALM_GET_SERIAL(ci_id) ((ci_id & 0x00ffff00) >> 8)
/** Get CTRLCI from ci_id. */
#define CALM_GET_CTRLCI(ci_id) (ci_id & 0x000000ff)
/** Set medium identifier in ci_id. */
#define CALM_SET_MEDID(ci_id, medid) (ci_id = \
		(ci_id & 0x00ffffff) | ((medid & 0x000000ff) << 24))
/** Set serial number in ci_id. */
#define CALM_SET_SERIAL(ci_id, serial) (ci_id = \
		(ci_id & 0xff0000ff) | ((serial & 0x0000ffff) << 8))
/** Set CTRLCI in ci_id. */
#define CALM_SET_CTRLCI(ci_id, ctrlci) (ci_id = \
		(ci_id & 0xffffff00) | (ctrlci & 0x000000ff))
#else
#error Unknown byte order.
#endif
#endif

/** True if ci_id belongs to the physical interface itself. */
#define CALM_PHYS(ci_id) ((CALM_GET_SERIAL(ci_id) == 0x0000) ? 1 : 0)
/** True if ci_id belongs to a VCI, not the physical interface. */
#define CALM_VIRT(ci_id) ((CALM_GET_SERIAL(ci_id) == 0x0000) ? 0 : 1)

/** @} CALM netlink header. */

/**
 * CALM error codes.
 *
 * @defgroup netlinkerrcodes CALM netlink error codes.
 * @ingroup netlink
 * @{
 */
enum {
	CALM_ERRCODE_SUCCESS,           /**< Success. */
	CALM_ERRCODE_UNSPEC,            /**< Unspecified failure. */
	CALM_ERRCODE_INVALID_PARAM,     /**< Invalide parameter. */
	CALM_ERRCODE_INVALID_PARAMVAL,  /**< Invalid parameter value. */
	CALM_ERRCODE_RI_VIOLATION,      /**< RI violation. */
	CALM_ERRCODE_INVALID_CMD,       /**< Invalid command or request. */
	CALM_ERRCODE_INVALID_CMDVAL,    /**< Invalid command or request value. */
	CALM_ERRCODE_ACCESS_VIOLATION,  /**< Access violation. */
	CALM_ERRCODE_INVALID_CIID,      /**< Invalid CI-ID. */
	__CALM_ERRCODE_MAX,
};
#define CALM_ERRCODE_MAX (__CALM_ERRCODE_MAX - 1)
/** @} */

/*
 * Attribute rights.
 */
#define CALM_ATTR_GET 0x01
#define CALM_ATTR_SET 0x02
#define CALM_ATTR_GETSET (CALM_ATTR_GET | CALM_ATTR_SET)
#define CALM_ATTR_CMD 0x04
#define CALM_ATTR_REQ 0x08
#define CALM_ATTR_CI 0x10  /* CI-specific attribute. */
#define CALM_ATTR_VCI 0x20 /* VCI-specific attribute. */

/**
 * Netlink multicast groups for CALM.
 *
 * @defgroup netlinkmcgroups CALM netlink multicast groups.
 * @ingroup netlink
 * @{
 */
#define CALM_DEVICE 0x01 /**< Netlink multicast group for notifications. */
/** @} */

/**
 * CALM events from media.
 *
 * @defgroup netlinkevents CALM netlink events.
 * @ingroup netlink
 * @{
 */
#define CALM_EV_TXREJECT 0x00       /**< TX rejected. */
#define CALM_EV_TXQUEUETHRHIGH 0x01 /**< TX queue high threshold reached. */
#define CALM_EV_TXQUEUEFULL 0x02    /**< TX queue full. */
#define CALM_EV_VCICREATE 0x03      /**< VCI created. */
#define CALM_EV_VCIDELETE 0x04      /**< VCI deleted. */
#define CALM_EV_PARAMCHANGE 0x05    /**< Monitored parameter changed. */
#define CALM_EV_TXQUEUETHRLOW 0x06  /**< TX queue low threshold reached. */
#define CALM_EV_VCIRESET 0x07       /**< VCI is reset. */
#define CALM_EV_MEDREG 0x08         /**< Medium registered. */
#define CALM_EV_MEDUNREG 0x09       /**< Medium deregistered. */
/** @} */

/** @} CALM netlink stuff. */

/**
 * Media types.
 *
 * @defgroup medtypes CALM media types.
 * @ingroup calm_ci
 * @{
 */
#define CALM_MED_21212 0x02    /**< 21212. */
#define CALM_MED_21213 0x03    /**< 21213. */
#define CALM_MED_21214 0x04    /**< 21214. */
#define CALM_MED_21215 0x05    /**< 21215. */
#define CALM_MED_21216 0x06    /**< 21216. */
#define CALM_MED_15628 128     /**< ISO 15628, ie. CALM CEN DSRC */
#define CALM_MED_LAN_FAST 0xfe /**< LAN FAST. */
#define CALM_MED_LAN_IP 0xff   /**< LAN IP. */
/** @} */

/**
 * Media classes.
 *
 * @defgroup medclasses CALM media classes.
 * @ingroup calm_ci
 * @{
 */
#define CALM_CIC_WL1 0x00 /**< WL1 class. */
#define CALM_CIC_WL2 0x01 /**< WL2 class. */
#define CALM_CIC_WL3 0x02 /**< WL3 class. */
#define CALM_CIC_WL4 0x03 /**< WL4 class. */
#define CALM_CIC_WL5 0x04 /**< WL5 class. */
#define CALM_CIC_WR1 0x05 /**< WR1 class. */
#define CALM_CIC_WR2 0x06 /**< WR2 class. */
/** @} */

/**
 * Media access classes.
 *
 * @defgroup medacclasses CALM media access classes.
 * @ingroup calm_ci
 * @{
 */
#define CALM_CIAC_1 0x00 /**< Access class 1. */
#define CALM_CIAC_2 0xff /**< Access class 2. */
/* XXX: CIAC_3 */
/** @} */

/**
 * Supported protocols by a medium.
 *
 * @defgroup protossupp CALM supported protocols.
 * @ingroup calm_ci
 * @{
 */
#define CALM_COMM_FAST 0x01 /**< FAST supported. */
#define CALM_COMM_IPV6 0x02 /**< IPv6 supported. */
/** @} */

/**
 * Directivity modes.
 *
 * @defgroup directivity CALM directivity modes.
 * @ingroup calm_ci
 * @{
 */
#define CALM_DIR_MODE_FIXED 0    /**< Fixed directivity. */
#define CALM_DIR_MODE_TRACKING 1 /**< Tracking directivity. */
/** @} */

/**
 * Predefined directivity constants.
 *
 * @defgroup directivity CALM predefined directivities.
 * @ingroup calm_ci
 * @{
 */
#define CALM_DIR_PREDEF_OMNIDIRECTIONAL 1 /**< Omnidirectional directivity. */
#define CALM_DIR_PREDEF_OVERHEAD 2        /**< Over head directivity. */
#define CALM_DIR_PREDEF_FORWARD 3         /**< Forward directivity. */
#define CALM_DIR_PREDEF_BACKWARD 4        /**< Backward directivity. */
#define CALM_DIR_PREDEF_FRONTLEFT 5       /**< Front left directivity. */
#define CALM_DIR_PREDEF_FRONTRIGHT 6      /**< Front right directivity. */
/** @} */

/**
 * @defgroup directinfo CALM directivity info.
 * @ingroup calm_ci
 * @{
 */
/**
 * Directivity info.
 */
struct calm_dir {
	__u8 mode;         /**< Mode, either fixed or tracking. */
	__u8 predef;       /**< Predefined directions. */
	__s16 bsazimuth;   /**< Horizontal angle of the bore sight. */
	__s8 bselevation;  /**< Vertical angle of the bore sight. */
	__u8 openhoriz;    /**< Horizontal opening of the beam. */
	__u8 openvert;     /**< Vertical opening of the beam. */
};
/** @} */

/**
 * Possible medium states.
 *
 * @see calm_cistate
 *
 * @defgroup medstates CALM possible media states.
 * @ingroup calm_ci
 * @{
 */
enum {
	CALM_CISTATE_NOTEXISTS,  /**< Medium not exists. */
	CALM_CISTATE_EXISTS,     /**< Medium exists. */
	CALM_CISTATE_REGISTERED, /**< Medium registered. */
	CALM_CISTATE_ACTIVE,     /**< Active state, communications are enabled. */
	CALM_CISTATE_CONNECTED,  /**< Connected to communication network. */
	CALM_CISTATE_SUSPENDED,  /**< Suspended, all communications are on hold. */
	CALM_CISTATE_INACTIVE,   /**< CI is reset, communications are disabled. */
};
/** @} */

/**
 * Commands changing medium state.
 *
 * @see calm_cistate
 *
 * @defgroup medstatecmds CALM possible media state commands.
 * @ingroup calm_ci
 * @{
 */
enum {
	CALM_CI_DEREGISTER, /**< Deregister CI. */
	CALM_CI_ACTIVATE,   /**< Activate CI. */
	CALM_CI_REACTIVATE, /**< Reactivate after suspension. */
	CALM_CI_CONNECT,    /**< Connect to the communication network. */
	CALM_CI_DISCONNECT, /**< Disconnect from the communication network. */
	CALM_CI_SUSPEND,    /**< Suspend CI. */
	CALM_CI_INACTIVATE, /**< Inactivate CI. */

	/*
	 * These are not in 21218.
	 */
	CALM_CI_REGISTER,       /**< Register CI. */
	CALM_CI_CREATEFIRSTVCI, /**< First VCI is created. */
	CALM_CI_DELETELASTVCI,  /**< Last existing VCI is deleted. */
};
/** @} */

static inline uint32_t calm_datarate_from_bps(uint32_t datarate)
{
  return datarate / 100;
}

static inline uint32_t calm_datarate_from_kbps(uint32_t datarate)
{
  return datarate * 10;
}

/*! This function returns datarate in KB/sec, rounded up to closest KB
 */
static inline uint32_t calm_datarate_to_kbps(uint32_t datarate)
{
  return datarate / 10;
} 

/*! This function returns datarate in bytes/sec, rounded up to the closest KB
 */
static inline uint32_t calm_datarate_to_bps(uint32_t datarate)
{
  return datarate * 100;
}

#ifdef __KERNEL__
#include <linux/list.h>
#include <linux/skbuff.h>
#include <linux/netdevice.h>

#define CALM_DBG(args...) \
	do { \
		if (calm_debug) \
			printk(KERN_INFO "CALM: " args); \
	} while (0)
#define CALM_LOG(args...) \
	do { \
		printk(KERN_INFO "CALM: " args); \
	} while (0)

/* sysctls */
extern int sysctl_vci_gc_period;
extern int sysctl_cckid;

struct calm_ci;
struct calm_vci;

#define CALM_VCI_UNSPEC 0x00
#define CALM_VCI_UC 0x01
#define CALM_VCI_BC 0x02
#define CALM_VCI_MC 0x04
#define CALM_VCI_GC (CALM_VCI_BC | CALM_VCI_MC)

// Unit of datarate in kbytes/sec
#define CALM_UNIT_DATARATE_KBPS (CALM_UNIT_DATARATE_BPS/1000)

/**
 * @defgroup calm_ops CALM callbacks in device drivers.
 * @ingroup calm_ci
 * @{
 */
/**
 * Callbacks in device drivers.
 *
 * A CALM-aware device driver can implement any one of them, but it's not
 * necessary.  If a command is sent from user-space and the necessary callback
 * is not set, the framework sends back CALM_ERRCODE_INVALID_PARAM.
 *
 * All the callbacks return zero on success, or a positive CALM errcode, or a
 * negative errno.
 */
struct calm_ops {
	/**
	 * Called to get auxiliary channel.
	 */
	int (*get_auxch)(struct calm_vci *, u8 *);

	/**
	 * Called to set auxiliary channel.
	 */
	int (*set_auxch)(struct calm_vci *, u8);

	/**
	 * Called to get control channel.
	 */
	int (*get_ctrlch)(struct calm_vci *, u8 *);

	/**
	 * Called to set control channel.
	 */
	int (*set_ctrlch)(struct calm_vci *, u8);

	/**
	 * Called to get service channel.
	 */
	int (*get_servch)(struct calm_vci *, u8 *);

	/**
	 * Called to set service channel.
	 */
	int (*set_servch)(struct calm_vci *, u8);

	/**
	 * Called to get RX sensitivity.
	 */
	int (*get_rxsens)(struct calm_vci *, u8 *);

	/**
	 * Called to set RX sensitivity.
	 */
	int (*set_rxsens)(struct calm_vci *, u8);

	/**
	 * Called to get TX power.
	 */
	int (*get_txpwr)(struct calm_vci *, u8 *);

	/**
	 * Called to set TX power.
	 */
	int (*set_txpwr)(struct calm_vci *, u8);

	/**
	 * Called to get datarate.
	 */
	int (*get_datarate)(struct calm_vci *, u32 *);

	/**
	 * Called to set datarate.
	 */
	int (*set_datarate)(struct calm_vci *, u32);

	/**
	 * Called to get directivity of VCI.
	 */
	int (*get_directivity)(struct calm_vci *, struct calm_dir *);

	/**
	 * Called to set directivity of VCI.
	 */
	int (*set_directivity)(struct calm_vci *, struct calm_dir *);

    /**
	 * Called to get reliability.
	 */
	int (*get_reliability)(struct calm_vci *, u8 *);

	/**
	 * Called to get maximum length of LPDU.
	 */
	int (*get_blocklen)(struct calm_vci *, u16 *);

	/**
	 * Called to set maximum length of LPDU.
	 */
	int (*set_blocklen)(struct calm_vci *, u16);

	/**
	 * Called to get distance in 1/10 m to peer station measured by the CI.
	 */
	int (*get_peerdist)(struct calm_vci *, u16 *);

	/**
	 * Called to get communication distance to a reference peer station in 1/10
	 * meter.
	 */
	int (*get_commrangeref)(struct calm_vci *, u16 *);

	/**
	 * Called to get RI state of CI.
	 */
	int (*get_reginfo)(struct calm_ci *, u8 *);

	/**
	 * Called to set RI info.
	 */
	int (*set_reginfo)(struct calm_ci *, u8 *, int);

	/**
	 * Called to get gap between subsequent TDMA frames in ms.
	 */
	int (*get_freeairtime)(struct calm_vci *, u8 *);

	/**
	 * Called to set gap between subsequent TDMA frames in ms.
	 */
	int (*set_freeairtime)(struct calm_vci *, u8);

	/**
	 * Called to get medium usage.
	 */
	int (*get_medusage)(struct calm_ci *, u8 *, u8 *);

	/**
	 * Called to get medium usage observation time.
	 */
	int (*get_meduseobs)(struct calm_ci *, u16 *);

	/**
	 * Called to set medium usage observation time.
	 */
	int (*set_meduseobs)(struct calm_ci *, u16);

	/**
	 * Called to get queue threshold.
	 */
	int (*get_queuethr)(struct calm_ci *, u8 *, u8 *);

	/**
	 * Called to set queue threshold.
	 */
	int (*set_queuethr)(struct calm_ci *, u8, u8);

	/**
	 * Called to get maximal length of a TDMA frame in ms.
	 */
	int (*get_maxframelen)(struct calm_vci *, u8 *);

	/**
	 * Called to set maximal length of a TDMA frame in ms.
	 */
	int (*set_maxframelen)(struct calm_vci *, u8);

	/**
	 * Called to deregister CI.  The driver should clean up everything.  CDDF
	 * will remove all existing VCIs.
	 */
	int (*deregister)(struct calm_ci *);

	/**
	 * Called to activate an inactive CI.  This must trigger the creation of
	 * default VCIs.
	 */
	int (*activate)(struct calm_ci *);

	/**
	 * Called to reactivate a previously suspended CI.  If it's possible,
	 * pending packets should be processed.
	 */
	int (*reactivate)(struct calm_ci *);

	/**
	 * Called to make CI connect.  This is applicable for CIAC_2, which must
	 * establish a connection to the network after receiving this command.  In
	 * case of CIAC_1, the state of CALM_CISTATE_CONNECTED is an indication
	 * that the medium is connected to at least one peer station.
	 */
	int (*connect)(struct calm_ci *);

	/**
	 * Called to disconnect CI.  For CIAC_2, this means that the connection
	 * should be terminated.
	 */
	int (*disconnect)(struct calm_ci *);

	/**
	 * Called to suspend CI.  This disables any communication, but all VCIs,
	 * pending packets and state variables must remain intact.
	 */
	int (*suspend)(struct calm_ci *);

	/**
	 * Called to inactivate CI by disabling all communications.  This will
	 * result in a reset in the CI, after which no more pending packets may
	 * exist in the CI.  All VCIs will be deleted by CDDF.
	 */
	int (*inactivate)(struct calm_ci *);

	/**
	 * Called to set wake-up behaviour.
	 */
	int (*wakeup)(struct calm_ci *, u8);

	/**
	 * Called to send vendor-specific command.
	 */
	int (*vendor)(struct calm_ci *, u8 *, int);

	/**
	 * Called when a VCI is created either by the respective device driver or
	 * after the corresponding command is received by CDDF.
	 */
	void (*vci_setup)(struct calm_vci *, void *);

	/**
	 * Called when a VCI is deleted to release all resources allocated
	 * dynamically for this VCI.
	 */
	void (*vci_release)(struct calm_vci *);

	/**
	 * Called to send management packet via the VCI.
	 *
	 * @param vci VCI
	 * @param src source_address (full CI-ID plus SSAP)
	 * @param dst destination_address (full CI-ID plus DSAP)
	 * @param prio priority
	 * @param data data
	 * @param data_len length of data
	 * @param param medium-specific additional parameter(s)
	 * @param param_len length of param
	 *
	 * @return 0 on success, non-zero on error
	 */
	int (*unitdata)(struct calm_vci *vci,
			        struct dl_sap_address *src,
					struct dl_sap_address *dst,
					u8 prio,
					u8 *data,
					int data_len,
					u8 *param,
					int param_len);
};
/** @} CALM callbacks in device drivers. */

struct calm_notify {
	struct list_head list;
	u32 ci_id;
	u32 nl_peer;
	u32 nl_seq;
	u8 attr;
};

/**
 * @defgroup calm_ci calm_ci
 * @{
 */
/**
 * Structure representing a physical medium.
 *
 * A CALM-aware device driver should first allocate a calm_ci, then register it
 * in CDDF using calm_register_ci().  To unregister, the driver first should
 * free the struct allocated, and then call calm_unregister_ci().
 *
 * At least three things should be set in calm_ci before the driver can
 * register it:
 *   - med_type (which tells one the type of the interface)
 *   - the corresponding net_device
 *   - implemented calm_ops callbacks.
 *
 * @see
 *   - calm_vci
 *   - calm_init_ci
 *   - calm_alloc_ci
 *   - calm_free_ci
 *   - calm_register_ci
 *   - calm_unregister_ci
 *   - calm_lookup_ci
 *   - calm_cistate
 */
struct calm_ci {
	struct list_head list; /**< List of CIs. */
	struct list_head notify_head; /**< List head of monitored parameters. */
	struct list_head vci_head; /**< List head of VCIs of this CI. */

	struct class_device	class_dev;

	atomic_t vci_counter;
	spinlock_t ci_lock;

	struct timer_list vci_gc_timer; /* Timer for VCI garbage collecting. */

	struct net_device *dev; /* Corresponding struct net_device. */

	/**
	 * VCI TX function.
	 */
	int (*calm_tx)(struct sk_buff *, struct net_device *, struct calm_vci *);

	struct calm_ops *calm_ops;

	u8 med_id;
	unsigned int med_type;

	unsigned char state;
	enum {
		CALM_CI_UNKNOWN = 0,
		CALM_CI_REGISTERING,
		CALM_CI_REGISTERED,
		CALM_CI_UNREGISTERING,
		CALM_CI_UNREGISTERED,
	} reg_state;

	unsigned int ci_class;
	unsigned int ci_access_class;
	unsigned int comm_modes;

	unsigned int queue_thr_low;
	unsigned int queue_thr_high;

	unsigned char min_susp_prio;
	unsigned char min_cross_prio;

	void *priv;
};
/** @} */

/**
 * @defgroup calm_vci calm_vci
 * @{
 */
/**
 * Structure representing a virtual communication profile of a physical
 * interface.
 *
 * VCIs make it possible to quickly switch between the various peer-specific
 * MIBs, even on a packet-by-packet base.
 *
 * When creating a VCI, the caller should pass the MAC address also as a
 * parameter, and the type of the MAC address (unicast, broadcast or
 * multicast), although these are not necessary.
 *
 * VCIs are identified by a unique number, called CI-ID.  One can look up VCIs
 * using either
 * - the peer's MAC address, or
 * - the VCI's CI-ID.
 *
 * @see
 *   - calm_ci
 *   - calm_create_vci
 *   - calm_put_vci
 *   - calm_lookup_vci
 *   - calm_lookup_peer
 */
struct calm_vci {
	struct list_head list; /* List of VCIs. */
	struct list_head remove_list; /* List of VCIs to be removed. */
	struct list_head create_list; /* List for creating netdevs. */

	atomic_t use;
#define VCI_HOLD(_vci) atomic_inc(&_vci->use)
#define VCI_PUT(_vci) atomic_dec_and_test(&_vci->use)

	struct class_device	class_dev;

	struct calm_ci *ci; /* Pointer to our CI struct. */

	u32 ci_id;

	atomic_t min_prio; /* Minimum priority to access VCI. */

	/*
	 * Net_device management support.
	 */
	struct net_device *dev; /* Corresponding virtual netdevice. */
	struct net_device_stats stats; /* Netdevice stats. */

	struct list_head chstate_list; /* List for changing netdev state. */
	struct list_head chflags_list; /* List for changing netdev flags. */

	int old_promiscuity;
	int old_allmulti;
	struct dev_mc_list *old_mc_list;

	unsigned short dev_flags;

	unsigned char peer[MAX_ADDR_LEN];
	int peer_len;

	unsigned long inact_limit; /* Lifetime limit in milliseconds. */

	void *priv;
};
#define CALM_DEV_VCI(_dev) ((struct calm_vci *)_dev->priv)
#define CALM_DEV_REAL(_dev) (((struct calm_vci *)_dev->priv)->ci->dev)
/** @} */

void calm_init_ci(struct calm_ci *);
struct calm_ci *calm_alloc_ci(void *, void (*)(struct calm_ci *, void *));
void calm_free_ci(struct calm_ci *);
int calm_register_ci(struct calm_ci *);
int calm_unregister_ci(struct calm_ci *);
void calm_put_vci(struct calm_vci *);
int calm_notify(struct calm_notify *);
u32 calm_create_vci(struct calm_ci *, char *, int, int, void *);
struct calm_ci *calm_lookup_ci(u8);
struct calm_vci *calm_lookup_vci(u32);
struct calm_vci *calm_lookup_peer(struct calm_ci *, char *, int);
int calm_update_peer(struct calm_vci *, char *, int);
int calm_unitdata(struct calm_vci *, struct dl_sap_address *,
		struct dl_sap_address *, u8, u8 *, int, u8 *, int);
int calm_cistate(struct calm_ci *, u8);
void calm_remove_vcis(struct calm_ci *);

/**
 * Bump a VCI's refcount.
 *
 * @param vci VCI
 */
static inline void calm_hold_vci(struct calm_vci *vci)
{
	VCI_HOLD(vci);
}

static inline struct calm_notify *__lookup_notify(struct calm_ci *ci, u32 ci_id, u8 param)
{
	struct list_head *entry;
	struct calm_notify *cn = NULL;

	if(!ci)
		return NULL;

	list_for_each(entry, &ci->notify_head) {
		cn = list_entry(entry, struct calm_notify, list);
		if ((cn->ci_id == ci_id) && (cn->attr == param))
			break;
		else
			cn = NULL;
	}

	return cn;
}

/**
 * Send notification if a parameter changes its value.
 *
 * @param ci calm_ci
 * @param attr attribute possibly changed
 */
static inline void calm_attr_change(struct calm_ci *ci, u32 ci_id, int attr)
{
	struct calm_notify *cn;

	spin_lock_bh(&ci->ci_lock);
	cn = __lookup_notify(ci, ci_id, attr);
	if (unlikely(cn)) {
		list_del(&cn->list);
		spin_unlock_bh(&ci->ci_lock); /* calm_notify() may sleep */
		if (calm_notify(cn) == 0) {
			spin_lock_bh(&ci->ci_lock);
			list_add(&cn->list, &ci->notify_head);
			spin_unlock_bh(&ci->ci_lock);
		}
	} else {
		spin_unlock_bh(&ci->ci_lock);
	}
}

/**
 * Retrieve VCI refcount.
 *
 * @param vci VCI
 */
static inline int calm_get_vci_refcnt(struct calm_vci *_vci)
{
	return atomic_read(&_vci->use);
}

/**
 * Get VCI net_device stats.
 *
 * @param dev net_device
 *
 * @return pointer to struct net_device_stats
 */
static inline struct net_device_stats *calm_dev_get_stats(struct net_device *dev)
{
	return &(CALM_DEV_VCI(dev)->stats);
}

/**
 * Get VCI expiration time.
 *
 * @param vci VCI
 *
 * @return time in jiffies when this VCI expires
 */
static inline unsigned long calm_get_lifetime(struct calm_vci *vci)
{
	if (vci->inact_limit == 0)
		return (jiffies + 60 * HZ); /* just some random time in the future */
	else if ((vci->dev == NULL) || (vci->dev->last_rx == 0))
		return (jiffies + vci->inact_limit * HZ / 1000); /* no netdevice yet */
	else
		return (vci->dev->last_rx + vci->inact_limit * HZ / 1000);
}

/**
 * CCKID notification chain attribute
 */
enum {
	CALM_CCKID_CHANGED = 1,
	CALM_CISTATE_CHANGED = 2,
};

/**
 * CCKID notification chain register and unregister
 */
int calm_register_notifier(struct notifier_block *nb);
int calm_unregister_notifier(struct notifier_block *nb);

/** 
 * Get CIID from CISTATE_CHANGED notification attribute
 */
#define CALM_GET_CISCH_ID(a) ((a & 0xff00) >> 8)

/**
 * Get CISTATUS from CISTATE_CHANGED notification attribute
 */
#define CALM_GET_CISCH_ST(a) (a & 0x00ff)

/** 
 * Set CIID in CISTATE_CHANGED notification attribute
 */
#define CALM_SET_CISCH_ID(a, id) (a = (a & 0x00ff) | ((id & 0x00ff) << 8))

/** 
 * Set CISTATUS in CISTATE_CHANGED notification attribute
 */
#define CALM_SET_CISCH_ST(a, st) (a = (a & 0xff00) | (st & 0x00ff))

/** Query a VCI for whether it is a broadcast VCI or not.
 */
static inline int calm_vci_is_broadcast(struct calm_vci *vci)
{
  return CALM_GET_SERIAL(vci->ci_id) == 0xffff;
}

static inline int calm_ci_get_no_vcis_attached(struct calm_ci *ci)
{
  return atomic_read(&ci->vci_counter);
}

#endif /* __KERNEL__ */

#endif /* _LINUX_CALM_H */
