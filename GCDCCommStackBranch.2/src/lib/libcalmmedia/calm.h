/*
 * $Id: calm.h $
 *
 * This file is part of the Low-layer CALM Management (CDDF) Library.
 * 
 * Author: Andras Takacs <andras.takacs@ramsys.hu>
 * Author: Laszlo Virag <laszlo.virag@ramsys.hu>
 *
 * Copyright 2006-2009 Ramsys Zrt
 *
 * Low-layer CALM Management (CDDF) Library is free software; you can redistribute
 * it and/or modify it under the terms of the GNU LEsser General Public
 * License as published by the Free Software Foundation; version 3 of
 * the License.
 *
 * Low-layer CALM Management (CDDF) Library is distributed in the hope that it will
 * be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Low-layer CALM Management (CDDF) Library; if not, write to the Free
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307 USA.
 */

/**
 * @file calm.h
 * @brief CALM netlink interface header for CALM management daemon
 */

#ifndef __LIBCALMMEDIA_CALM_H_
#define __LIBCALMMEDIA_CALM_H_

#include <net/if.h>

#include "mininl.h"
#include <linux/calm.h>

/**
 * Number of max. interface.
 */
#define CALM_MAX_INTF 5

/**
 * Number of messages with bad sequence number before rturn
 */
#define CALM_BADSEQ_MAX	10

/**
 * IPv6 address array.
 */
typedef char calm_addr_arr_t[CALM_MAX_INTF][INET6_ADDRSTRLEN];

/**
 * Error codes
 */
#define CALM_ERR_OK		 0
#define CALM_ERR_LOW	-1
#define CALM_ERR_NOTIMP	-2
#define CALM_ERR_NOCI   -3
#define CALM_ERR_VALUE  -4
#define CALM_ERR_PARSE	-5
#define CALM_ERR_OTHER	-6
#define CALM_ERR_COMM	-7
#define CALM_ERR_FAMILY	-8
#define CALM_ERR_SEQ	-9
#define CALM_ERR_CREATE	-10

/**
 * CALM device descriptor structure.
 */
typedef struct calmvci {
        uint32_t ci_id; /**< CI ID */
        uint8_t cck_id; /**< CCK ID */

        int if_index; /**< Network interface index. */
        char if_name[IF_NAMESIZE]; /**< Network interface name. */
        int nr_ipv6addr; /**< Number of assigned IPv6 addresses. */
        struct in6_addr ipv6addr[CALM_MAX_INTF]; /**< Assigned IPv6 addresses. */

		unsigned char hwaddr[6]; /**< Hardware (MAC) address of interface */

        struct calm_dir dir;

		int is_bc; /**< Is a broadcast interface? */
} calm_dev_t;

/**
 * CI descriptor struct
 */
typedef struct calmci {
	uint32_t ci_id; /**< CI id */
	
	int if_index; /**< Network interface index. */
	char if_name[IF_NAMESIZE]; /**< Network interface name. */

	uint8_t med_type; /**< Media type. */

	int nr_vci; /**< number of assigned VCI */
	calm_dev_t *vci_list; /**< list of the all VCI */
} calm_ci_t;

/*
 * Send a CALM mesage and wit / check the response
 *
 * @nl NL handle
 * @ci_id CI-ID
 * @msg CALM message to send
 * @mlen Messge len
 * @buff Pointer for the reply buffer
 * @blen Ponter for the buffer's length
 *
 * @return error code
 */
int calm_sndrcv(struct nl_handle * nl, uint32_t ci_id, unsigned char * msg, int mlen, unsigned char ** buf, int * blen);

extern int calm_get(struct nl_handle *nl, int attr, uint32_t ci_id, unsigned char **buf, int *len);
extern int calm_set(struct nl_handle *nl, int attr, void *val, uint32_t ci_id, unsigned char **buf, int *len);

/**
 * Get CCK ID
 *
 * @return CCK ID
 */
int calm_get_cckid();

/**
 * Set CCK ID
 *
 * @param cckid CCK-ID
 *
 * @return 0 if OK, or -1
 */
int calm_set_cckid(uint8_t cckid);


/**
 * Get all IPv6 addresses from interace.
 *
 * @param if_index index of inerface
 * @param addrs array of IPv6 addresses
 * @param size number of element in addrs array
 *
 * @return Error code (0: ok)
 */
extern int calm_get_addrs(uint32_t if_index, struct in6_addr *addrs, int size);

/**
 * Get all VCI interface description from CI.
 *
 * @param nl netlink handle for the communication
 * @param ci_id requested CI's id
 * @param list VCI's list
 * @param nr number of VCI
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_get_vcis(struct nl_handle *nl, uint32_t ci_id, calm_dev_t **list, int *nr);

/**
 * Get CI list form the CALM device.
 *
 * @param nl netlink handle for the communication
 * @param list CI's list
 * @param nr number of CI
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_get_cis(struct nl_handle *nl, calm_ci_t **list, int *nr);

/**
 * Free the list.
 *
 * @param list CI's list
 * @param nr number of CI
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_free(calm_ci_t **list, int nr);


/* Prototypes of DEFNIED GET FUNCTIONS */

/**
 * Send command to a CALM device.
 *
 * @param nl netlink handle for the communication
 * @param attr CALM attribute
 * @param val command attr value
 * @param ci_id requested CI's id
 * @param buf communication buffer
 * @param len size of the buffer
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_cmd(struct nl_handle *nl, int attr, void *val, uint32_t ci_id, unsigned char **buf, int *len);

/**
 * GET - Information on auxiliary channels in addition to control channel and service channel.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested VCI's id
 * @param Value of VCI's auxiliary channel
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_get_AUXCH(struct nl_handle *nl, uint32_t vci_id, uint8_t *retval);

/**
 * GET - Reference number for control channel.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested VCI's id
 * @param retval Value of VCI's control channel
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_get_CTRLCH(struct nl_handle *nl, uint32_t vci_id, uint8_t *retval);

/**
 * GET - Reference number for service channel.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested VCI's id
 * @param retval Value of VCI's service channel
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_get_SERVCH(struct nl_handle *nl, uint32_t vci_id, uint8_t *retval);

/**
 * GET - Medium specific reference number of RX sensitivity.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested VCI's id
 * @param retval Value of VCI's RX sensitivity
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_get_RXSENS(struct nl_handle *nl, uint32_t vci_id, uint8_t *retval);

/**
 * GET - Medium specific reference number of TX power.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested VCI's id
 * @param retval Value of VCI's TX power
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_get_TXPWR(struct nl_handle *nl, uint32_t vci_id, uint8_t *retval);

/**
 * GET - Data rate in the air in kbit/s.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested VCI's id
 * @param retval Value of VCI's Data rate
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_get_DATARATE(struct nl_handle *nl, uint32_t vci_id, uint32_t *retval);

/**
 * GET - Maximum length of LPDU
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested VCI's id
 * @param retval Value of VCI's Block length
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_get_BLOCKLEN(struct nl_handle *nl, uint32_t vci_id, uint16_t *retval);

/**
 * GET - Information on reliability
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested VCI's id
 * @param Value of VCI's reliability
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_get_RELIABILITY(struct nl_handle *nl, uint32_t vci_id, uint8_t *retval);

/**
 * GET - Minimum value of user priority needed to use the VCI
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested VCI's id
 * @param retval Value of VCI's Minimum priority
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_get_MINPRIO(struct nl_handle *nl, uint32_t vci_id, uint8_t *retval);

/**
 * GET - Time when last frame was properly received.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested CI's id
 * @param sec last RX time seconds from epoch
 * @param usec last RX time useconds
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_get_LASTRX(struct nl_handle *nl, uint32_t vci_id, uint32_t *sec, uint32_t *usec);

/**
 * GET - Maximum allowed idle time for a RX-VCI, i.e. maximum allowed time without proper reception of a frame.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested VCI's id
 * @param retval Value of VCI's maximum allowed idle time
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_get_MAXINACT(struct nl_handle *nl, uint32_t vci_id, uint16_t *retval);

/**
 * GET - Distance in 1/10 m to peer station measured by the CI
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested VCI's id
 * @param retval Value of VCI's peer distance
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_get_PEERDIST(struct nl_handle *nl, uint32_t vci_id, uint16_t *retval);

/**
 * GET - CI Class
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested CI's id
 * @param retval Value of CI Class
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_get_CICLASS(struct nl_handle *nl, uint32_t vci_id, uint8_t *retval);

/**
 * GET - Size of communication zone to a reference station in 1/10 meter.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested VCI's id
 * @param retval Value of VCI's size of communication zone
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_get_COMMRANGEREF(struct nl_handle *nl, uint32_t vci_id, uint16_t *retval);

 /**
 * GET - Minimum user priority needed to suspend a current frame with lower priority from transmission. Default value: 255 (highest priority).
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested CI's id
 * @param retval Value of CI's minimum suspend priority
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_get_MINSUSPPRIO(struct nl_handle *nl, uint32_t vci_id, uint8_t *retval);

/**
 * GET - Enumerator indicating type of medium.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested CI's id
 * @param retval Value of CI's medium type
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_get_MEDTYPE(struct nl_handle *nl, uint32_t vci_id, uint8_t *retval);

/**
 * GET - Indication of supported communication modes, e.g. CALM FAST, IPv6, …
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested CI's id
 * @param retval Value of CI's communicaton mode
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_get_COMMODES(struct nl_handle *nl, uint32_t vci_id, uint8_t *retval);

/**
 * GET - CI access class.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested CI's id
 * @param retval Value of CI access class
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_get_CIACCESSCLASS(struct nl_handle *nl, uint32_t vci_id, uint8_t *retval);

/**
 * GET - Gap between subsequent TDMA frames in ms
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested VCI's id
 * @param retval Value of VCI's free air time
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_get_FREEAIRTIME(struct nl_handle *nl, uint32_t vci_id, uint8_t *retval);

/**
 * GET - Observation time to calculate MediumUsage.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested CI's id
 * @param retval Value of CI's meduim usage ibservation time
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_get_MEDUSEOBSTIME(struct nl_handle *nl, uint32_t vci_id, uint16_t *retval);

/**
 * GET - Flag indicating whether the CI supports the suspend procedure based on parameter 21.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested CI's id
 * @param retval Value of CI's susped support flag
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_get_SUSPSUPPORTED(struct nl_handle *nl, uint32_t vci_id, uint8_t *retval);

/**
 * GET - Maximum length of a TDMA frame in ms.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested VCI's id
 * @param retval Value of VCI's maximum frame length
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_get_MAXFRAMELEN(struct nl_handle *nl, uint32_t vci_id, uint8_t *retval);

/**
 * GET - Status of CI.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested CI's id
 * @param retval Value of status of CI
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_get_CISTATE(struct nl_handle *nl, uint32_t vci_id, uint8_t *retval);

/**
 * GET - Minimum required user priority in order to be able to request cross-CI prioritization.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested CI's id
 * @param retval Value of CI's minimum required user priority
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_get_MINPRIOCROSSCI(struct nl_handle *nl, uint32_t vci_id, uint8_t *retval);

/**
 * GET - CCK- ID
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested CI's id
 * @param retval Value of CI's minimum required user priority
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_get_CCKID(struct nl_handle *nl, uint32_t vci_id, uint8_t *retval);

/**
 * GET - No descreption...
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested VCI's id
 * @param retval Value of VCI's IFINDEX
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_get_IFINDEX(struct nl_handle *nl, uint32_t vci_id, uint32_t *retval);

/**
 * GET - Uniquely assigned six byte MAC address of CI.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested VCI's id
 * @param mac MacAddress in octet string format
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_get_MACADDR(struct nl_handle *nl, uint32_t vci_id, unsigned char **mac);

/* Prototypes of NESTED GET FUNCTIONS */

/**
 * GET - Characteristics of beam
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested CI's / VCI's id
 * @param calm_dir (nested) structure of information of directivity
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_get_DIR(struct nl_handle *nl, uint32_t vci_id, struct calm_dir *dir);

/**
 * GET - RI data structure containing either the actually valid regulatory information, or a statement that no regulation is known or applicable.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested CI's id
 * @param state value of reginfo's state
 * @param ri value of reginfo's limits (string)
 * @param ri_len length of ri
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_get_REGINFO(struct nl_handle *nl, uint32_t vci_id, uint8_t *state, unsigned char **ri, int *ri_len);

/**
 * GET - Percentage of active usage of medium. Distinguishes between receive and transmit. Sliding window averaging. Observation time defined by MedUseObservationTime.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested CI's id
 * @param rx value of receive channel occupancy
 * @param tx value of transmit channel occupancy
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_get_MEDUSAGE(struct nl_handle *nl, uint32_t vci_id, uint8_t *rx, uint8_t *tx);

/**
 * GET - Threshold indicating the minimum level of usage of a transmit queue in a CI above which the IME shall be notified.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested CI's id
 * @param low value
 * @param high value
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_get_QUEUETHR(struct nl_handle *nl, uint32_t vci_id, uint8_t *low, uint8_t *high);

/**
 * Get list of parameters for automatic notification
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested CI's id
 * @param paramlist list of automatic notification
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_get_NOTIFY(struct nl_handle *nl, uint32_t vci_id, uint8_t **paramlist);

/**
 * Get CI's mac address and length of mac
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested CI's id
 * @param mac value of mac address
 * @param mac_len length of mac address
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_get_PEERMAC(struct nl_handle *nl, uint32_t vci_id, unsigned char **mac, int *mac_len);


/* Prototypes of DEFINED SET functions*/

/**
 * SET - Information on auxiliary channels in addition to control channel and service channel.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested VCI's id
 * @param Value of VCI's auxiliary channel
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_set_AUXCH(struct nl_handle *nl, uint32_t vci_id, uint8_t *retval);

/**
 * SET - Reference number for control channel.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested VCI's id
 * @param retval Value of VCI's control channel
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_set_CTRLCH(struct nl_handle *nl, uint32_t vci_id, uint8_t *retval);

/**
 * SET - Reference number for service channel.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested VCI's id
 * @param retval Value of VCI's service channel
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_set_SERVCH(struct nl_handle *nl, uint32_t vci_id, uint8_t *retval);

/**
 * SET - Medium specific reference number of RX sensitivity.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested VCI's id
 * @param retval Value of VCI's RX sensitivity
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_set_RXSENS(struct nl_handle *nl, uint32_t vci_id, uint8_t *retval);

/**
 * SET - Medium specific reference number of TX power.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested VCI's id
 * @param retval Value of VCI's TX power
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_set_TXPWR(struct nl_handle *nl, uint32_t vci_id, uint8_t *retval);

/**
 * SET - Data rate in the air in kbit/s.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested VCI's id
 * @param retval Value of VCI's Data rate
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_set_DATARATE(struct nl_handle *nl, uint32_t vci_id, uint32_t *retval);

/**
 * SET - Maximum length of LPDU
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested VCI's id
 * @param retval Value of VCI's Block length
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_set_BLOCKLEN(struct nl_handle *nl, uint32_t vci_id, uint16_t *retval);

/**
 * SET - Minimum value of user priority needed to use the VCI
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested VCI's id
 * @param retval Value of VCI's Minimum priority
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_set_MINPRIO(struct nl_handle *nl, uint32_t vci_id, uint8_t *retval);

/**
 * SET - Maximum allowed idle time for a RX-VCI, i.e. maximum allowed time without proper reception of a frame.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested VCI's id
 * @param retval Value of VCI's maximum allowed idle time
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_set_MAXINACT(struct nl_handle *nl, uint32_t vci_id, uint16_t *retval);

 /**
 * SET - Minimum user priority needed to suspend a current frame with lower priority from transmission. Default value: 255 (highest priority).
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested CI's id
 * @param retval Value of CI's minimum suspend priority
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_set_MINSUSPPRIO(struct nl_handle *nl, uint32_t vci_id, uint8_t *retval);

/**
 * SET - Gap between subsequent TDMA frames in ms
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested VCI's id
 * @param retval Value of VCI's free air time
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_set_FREEAIRTIME(struct nl_handle *nl, uint32_t vci_id, uint8_t *retval);

/**
 * SET - Observation time to calculate MediumUsage.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested CI's id
 * @param retval Value of CI's meduim usage ibservation time
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_set_MEDUSEOBSTIME(struct nl_handle *nl, uint32_t vci_id, uint16_t *retval);

/**
 * SET - Maximum length of a TDMA frame in ms.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested VCI's id
 * @param retval Value of VCI's maximum frame length
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_set_MAXFRAMELEN(struct nl_handle *nl, uint32_t vci_id, uint8_t *retval);

/**
 * SET - Minimum required user priority in order to be able to request cross-CI prioritization.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested CI's id
 * @param retval Value of CI's minimum required user priority
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_set_MINPRIOCROSSCI(struct nl_handle *nl, uint32_t vci_id, uint8_t *retval);

/**
 * SET - CCK-ID
 *
 * @param nl netlink handle for the communication
 * @param ci_id requested CI's id
 * @param val CCK-ID
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int calm_set_CCKID(struct nl_handle *nl, uint32_t ci_id, uint8_t *val);

/* prototypes of Nested SET functions */

/**
 * SET - Characteristics of beam
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested CI's / VCI's id
 * @param calm_dir (nested) structure of information of directivity
 *
 * @return Connection state (0: ok, -1: error)
 */
int calm_set_DIR(struct nl_handle *nl, uint32_t vci_id, struct calm_dir *dir);

/**
 * SET - RI data structure containing either the actually valid regulatory information, or a statement that no regulation is known or applicable.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested CI's id
 * @param state value of reginfo's state
 * @param ri value of reginfo's limits (string)
 * @param ri_len length of ri
 *
 * @return Connection state (0: ok, -1: error)
 */
int calm_set_REGINFO(struct nl_handle *nl, uint32_t vci_id, uint8_t state, unsigned char *ri, int ri_len);

/**
 * SET - Threshold indicating the minimum level of usage of a transmit queue in a CI above which the IME shall be notified.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested CI's id
 * @param low value
 * @param high value
 *
 * @return Connection state (0: ok, -1: error)
 */
int calm_set_QUEUETHR(struct nl_handle *nl, uint32_t vci_id, uint8_t low, uint8_t high);


/* Prototypes of CMD functions */

/**
 * CMD - Change of CI status.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested CI's id
 * @param retval new value of CI state
 *
 * @return Connection state (0: ok, -1: error)
 */
int calm_cmd_CISTATECMD(struct nl_handle *nl, uint32_t vci_id, uint8_t *retval);

/**
 * CMD - Start / stop wake up signal
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested CI's id
 * @param retval 0: stops transmission of wake-up signal / 1…255: starts repetitive transmission of wake-up signal with maximum interval in ms.
 *
 * @return Connection state (0: ok, -1: error)
 */
int calm_cmd_WAKEUP(struct nl_handle *nl, uint32_t vci_id, uint8_t *retval);

/**
 * CMD - Command to request creation, reset or deletion of a VCI.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested CI's id
 * @param retval 0: delete VCI if alive / 1: create VCI, if not existent, or reset it
 *
 * @return Connection state (0: ok, -1: error)
 */
int calm_cmd_VCI(struct nl_handle *nl, uint32_t vci_id, uint8_t *retval);


/**
 * CMD - Allows for a manufacturer specific access to the CI. Used e.g. for test and maintenance purposes.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested CI's id
 * @param data manufacturer specific octet string.
 * @param dlen length of data
 *
 * @return Connection state (0: ok, -1: error)
 */
int calm_cmd_VENDOR(struct nl_handle *nl, uint32_t vci_id, uint8_t *data, size_t dlen);

/**
 * CMD - Sequence of parameters of which change of value shall be notified.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested CI's id
 * @param param reference number of parameter to be monitored.
 * @param active 0: stop monitoring / 255: start monitoring
 *
 * @return Connection state (0: ok, -1: error)
 */
int calm_cmd_MONITOR(struct nl_handle *nl, uint32_t vci_id, uint8_t param, uint8_t active);

/**
 * CMD - Transmission request of a management data packet.
 *
 * @param nl netlink handle for the communication
 * @param vci_id requested CI's id
 * @param ssap source sap address
 * @param scckid source CCK
 * @param sciid source CI-ID
 * @param dsap destination SAP address
 * @param dcckid destination CCK
 * @param dciid destination CI-ID
 * @param prio priority
 * @param data data packet
 * @param dlen length of data
 * @param param parameter
 * @param plen length of parameter
 *
 * @return Connection state (0: ok, -1: error)
 */
int calm_cmd_UNITDATA(struct nl_handle *nl, uint32_t vci_id, uint8_t ssap, uint8_t scckid, uint32_t sciid, uint8_t dsap, uint8_t dcckid, uint32_t dciid, uint8_t prio, unsigned char *data, size_t dlen, unsigned char * param, size_t plen);

#endif
