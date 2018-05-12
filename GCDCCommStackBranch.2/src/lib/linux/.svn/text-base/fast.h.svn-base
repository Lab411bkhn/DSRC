/**
 * @file include/linux/fast.h
 * @brief FAST network layer
 *
 * It defines the socket details, and the user sap types.
 *
 * (C) 2008, Ramsys Zrt, Hungary
 *
 * Author: Andras Takacs <andras.takacs@ramsys.hu>
 */

#ifndef __FAST_H__
#define __FAST_H__		1

#ifndef __KERNEL__
#include <inttypes.h>
#include <linux/socket.h>
#include <sys/socket.h>
#include <errno.h>
#include <linux/types.h>
#include <linux/calm.h>
#endif	/* not __KERNEl__ */

#ifdef __KERNEL__
#include <net/sock.h>
#include <asm-generic/errno.h>
#include <net/netlink.h>
#endif /* __KERNEL__ */

#ifndef __KERNEL__
/** @brief CALM FAST protocol family */
#define PF_FAST         34
/** @brief CALM FAST address family */
#define AF_FAST         PF_FAST
#endif

/**
 * FAST network protocol for BSD socket
 */
#define FAST_FASTPROTO	1

/**
 * @brief FAST Socket option layer for get/set -sockopt
 * 
 * Defined the same in include/linux/socket.h
 */
#define SOL_FAST		111

/**
 * Generic Netlink family identifier
 */
#define FFWT_FAMILY 0x17

/**
 * Generic Netlink version
 */
#define FFWT_VERSION 2

/**
 * Generic netlink commands in FAST
 */
enum {
	FFWT_C_UNSPEC,			/**< Unspecified */
	FFWT_C_GET,				/**< Get */
	FFWT_C_ADD,				/**< Add */
	FFWT_C_DEL,				/**< Delete */
	__FFWT_C_MAX,
};

/**
 * The highest avaiable Generic netlink command in FAST
 */
#define FFWT_C_MAX (__FFWT_C_MAX - 1)

/**
 * Generic netlink attributes in FAST
 */
enum {
	FFWT_A_UNSPEC,			/**< Unspecified */
	
	FFWT_A_ENTRY,			/**< It contains table entries */
	FFWT_A_CISTUB,			/**< It contatins CI stub etries */
	FFWT_A_LNWRSTUB,		/**< It contains local NW ref stub entries */
	
	FFWT_A_RNWREF,			/**< Remote NW ref */	
	FFWT_A_CIID,			/**< CI - ID */
	FFWT_A_CICCK,			/**< CCK-ID part of the extended CI-ID */
	FFWT_A_LNWREF,			/**< Link NW ref */
    FFWT_A_HNWREF,          /**< Host NW ref */
	FFWT_A_CCKID,			/**< CCK - ID */
	FFWT_A_TIMEOUT_EXP,		/**< Expiration of timeout */
	FFWT_A_TIMEOUT_PERIOD,	/**< Periodicity of timeout */

	FFWT_A_DELETED,			/**< Number of the deleted entries */

	FFWT_A_ERR,				/**< It contains error details */
	FFWT_A_ERR_ATTR,		/**< Attribute which cause the error */
	FFWT_A_ERR_CODE,		/**< Error code */
	__FFWT_A_MAX,
};

/**
 * The highest aviable Generic netlink attribute in FASt
 */
#define FFWT_A_MAX (__FFWT_A_MAX - 1)

/**
 * Generic netlink error codes in FAST 
 */
enum {
	FFWT_ERR_SUCCESS,		/**< Success. */
	FFWT_ERR_UNSPEC,		/**< Unspecified failure. */
	FFWT_ERR_PARAM,			/**< Invalid parameter. */
	FFWT_ERR_PARAMVAL,		/**< Invalid parameter value. */
    FFWT_ERR_NOMEM,         /**< No memory for entry allocation. */
    FFWT_ERR_TABLE,			/**< Error in table. */
	__FFWT_ERR_MAX,
};

/**
 * The highjest aviable Generic netlink error code in FAST
 */
#define FFWT_ERR_MAX (__FFWT_ERR_MAX - 1)

/**
 * sockaddr's size
 */
#define __SOCK_SIZE__		(sizeof(struct sockaddr))

/**
 * The size of the used bytes from the sockaddr for FAST
 */
#define __SOCKFAST_PAD__	(sizeof(sa_family_t) + sizeof(uint8_t) + sizeof(uint16_t) + sizeof(uint32_t))

/**
 * FAST socketaddress structure
 */
struct sockaddr_fast {
	sa_family_t			family;		/**< Protocol family */

	uint8_t				nwref;      /**< Network reference */
	uint8_t	    		cckid;		/**< CCK-ID */
	uint32_t			ciid;		/**< CI-ID */

	unsigned char		__pad[__SOCK_SIZE__ - __SOCKFAST_PAD__];	/**< Padding */
};

/**
 * The unnused part of the FAST sockaddr
 */
#define fsa_zero	__pad

/**
 * Signs local CCK
 */
#define FAST_CCKID_LO   0

/**
 * Loopback CI-ID
 */
#define FAST_CIID_LO    0

/**
 * Broadcast CCK-ID
 */
#define FAST_CCKID_BC   255

/**
 * Signs local CI
 */
#define FAST_CICCK_LO   0

/**
 * Option definitions for get/set sockopt
 */
enum
{
	FASTOP_TIMEOUT,			/**< Get/Set timeout */
	FASTOP_PRIORITY,		/**< Get/Set priority */
};

/** 
 * Beaconing CIIDs 
 */
#define INIT_FAST_BEACON_CIID(ciid) \
    do { \
        CALM_SET_MEDID(ciid, 0xFF); \
        CALM_SET_SERIAL(ciid, 0xFFFF); \
        CALM_SET_CTRLCI(ciid, 0x00); \
    } while (0);

#define FAST_BEACON_21212(ciid) \
    do { \
        CALM_SET_CTRLCI(ciid, \
                ((CALM_GET_CTRLCI(ciid) & 0xF8) | \
                 CALM_MED_21212)); \
    } while (0);

#define FAST_BEACON_21213(ciid) \
    do { \
        CALM_SET_CTRLCI(ciid, \
               ((CALM_GET_CTRLCI(ciid) & 0xF8) | \
                 CALM_MED_21213)); \
    } while (0);

#define FAST_BEACON_21214(ciid) \
    do { \
        CALM_SET_CTRLCI(ciid, \
               ((CALM_GET_CTRLCI(ciid) & 0xF8) | \
                 CALM_MED_21214)); \
    } while (0);

#define FAST_BEACON_21215(ciid) \
    do { \
        CALM_SET_CTRLCI(ciid, \
               ((CALM_GET_CTRLCI(ciid) & 0xF8) | \
                 CALM_MED_21215)); \
    } while (0);

#define FAST_BEACON_21216(ciid) \
    do { \
        CALM_SET_CTRLCI(ciid, \
               ((CALM_GET_CTRLCI(ciid) & 0xF8) | \
                 CALM_MED_21216)); \
    } while (0);

#define FAST_BEACON_AUX_ID  0x01
#define FAST_BEACON_CTRL_ID  0x02
#define FAST_BEACON_SERV_ID  0x03

#define FAST_BEACON_AUX(ciid) \
    do { \
        CALM_SET_CTRLCI(ciid, \
               ((CALM_GET_CTRLCI(ciid) & 0xE7) | \
                 (FAST_BEACON_AUX_ID << 3))); \
    } while (0);

#define FAST_BEACON_CTRL(ciid) \
    do { \
        CALM_SET_CTRLCI(ciid, \
               ((CALM_GET_CTRLCI(ciid) & 0xE7) | \
                 (FAST_BEACON_CTRL_ID << 3))); \
    } while (0);

#define FAST_BEACON_SERV(ciid) \
    do { \
        CALM_SET_CTRLCI(ciid, \
               ((CALM_GET_CTRLCI(ciid) & 0xE7) | \
                 (FAST_BEACON_SERV_ID << 3))); \
    } while (0);

#define FAST_GET_BEACON_MED(ciid) \
    (CALM_GET_CTRLCI(ciid) & 0x7)

#define FAST_GET_BEACON_CH(ciid) \
    ( (CALM_GET_CTRLCI(ciid) & 0x18) >> 3 )


#endif /* __FAST_H__ */

