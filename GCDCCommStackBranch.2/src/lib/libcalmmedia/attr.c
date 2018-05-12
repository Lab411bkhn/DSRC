/*
 * $Id: attr.c $
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
 * @file attr.c
 * @brief Set/Get CALM attributes.
 */

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <ifaddrs.h>
#include <netdb.h>
#include <errno.h>
#include <time.h>
#include <net/if.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <stdlib.h>

#include <linux/unistd.h>
#include <linux/sysctl.h>
#include <sys/sysctl.h>

#include "calm.h"
#include "mininl.h"
#include <linux/calm.h>

//#define _LIBCALMMEDIA_DEBUG

#ifdef _LIBCALMMEDIA_DEBUG 
    #define debugging(...) \
        printf(__VA_ARGS__) 
#else 
    #define debugging(...)  
#endif

/**
 * Get CCK ID
 *
 * @return CCK ID
 */
int calm_get_cckid()
{
	int name[] =  {CTL_NET, NET_CALM, NET_CALM_CCKID };
	int cckid = 0;
	size_t cckidlen = sizeof(cckid);

	if (sysctl(name, 3, &cckid, &cckidlen, NULL, 0))
		return -1;

	return cckid;
}

/**
 * Set CCK ID
 *
 * @param cckid CCK-ID
 *
 * @return 0 if OK, or -1
 */
int calm_set_cckid(uint8_t cckid)
{
    int ret = 0;
	int name[] =  {CTL_NET, NET_CALM, NET_CALM_CCKID };
	int id = (int)cckid;

	ret = sysctl(name, 3, NULL, NULL, &id, sizeof(id));

    debugging("Set cckid to %u (erro code: %d)\n", cckid, ret);

    return ret;
}

/**
 * Get all IPv6 addresses from interface.
 *
 * @param if_index index of inerface
 * @param addrs array of IPv6 addresses
 * @param size number of element in addrs array
 *
 * @return Error code (0: ok)
 */
int calm_get_addrs(uint32_t if_index, struct in6_addr *addrs, int size)
{
	int ret = -1;
	struct ifaddrs *ifas = NULL, *ifa = NULL;
	char if_name[IF_NAMESIZE];
	int nr = 0;

	if (getifaddrs(&ifas) < 0) {
		debugging(" ! unable to get interface list.\n");
		return -1;
	}

	/**
	 * get interface name
	 */
	if (if_indextoname(if_index, if_name) == NULL) {
		debugging("if_indextoname(%u)\n", if_index);
		goto calm_vci_get_addresses_error;
	}

	/**
	 * get all IPv6 address from the interface
	 */
	struct sockaddr_in6 *sa6;

	for (ifa = ifas; ifa; ifa = ifa->ifa_next) {
		if ((strcmp(ifa->ifa_name, if_name) != 0)||(ifa->ifa_addr == NULL) || (ifa->ifa_addr->sa_family != AF_INET6))
			continue;

		socklen_t salen = sizeof (struct sockaddr_in6);
		sa6 = (struct sockaddr_in6 *)ifa->ifa_addr;
		if (IN6_IS_ADDR_LINKLOCAL(&sa6->sin6_addr))
			continue;
		memcpy(&addrs[nr++], &sa6->sin6_addr, salen);
		if (nr == size)
			break;
	}

	ret = nr;

calm_vci_get_addresses_error:
	if (ifas)
		freeifaddrs(ifas);
	return ret;
}

/**
 * Get CI list form the CALM device.
 *
 * @param nl netlink handle for the communication
 * @param list CI's list
 * @param nr number of CI
 *
 * @return Connection state (0: ok, -1: error)
 */
int calm_get_cis(struct nl_handle *nl, calm_ci_t **list, int *nr)
{
	int ret = CALM_ERR_OTHER;
	int cis = 0;
	int len;
	unsigned char *buf = NULL;
	calm_ci_t *ci_list = NULL;

	if ((list == NULL)||(nr == NULL)||(nl == NULL)) {
		debugging(" ! wrong parameters\n");
		goto calm_get_cis_error;
	}

	*nr = 0;
	if ( (ret = calm_get(nl, CALM_A_CILIST, 1, &buf, &len)) < 0) {
		debugging(" ! unable to send/receive datas to/from CALM\n");
		goto calm_get_cis_error;
	}

	mnl_attr_t *attr = NULL;
	while ((attr = mnl_nextattr(buf, len, attr))) {
		if ((attr->attr == CALM_A_CILIST_CI)&&(attr->mnl_uint8_t != 0))
			cis++;
	}
	free(attr);

	if (cis == 0) {
		debugging(" ! no CI found.\n");
		goto calm_get_cis_ok;
	}

	if ((ci_list = calloc(sizeof(calm_ci_t) * cis, 1)) == NULL) {
		debugging(" ! unable to allocate enough memory area.\n");
		goto calm_get_cis_error;
	}
	*list = ci_list;

	attr = NULL;
	while ((attr = mnl_nextattr(buf, len, attr))) {
		if ((attr->attr != CALM_A_CILIST_CI)||(attr->mnl_uint8_t == 0))
			continue;
		ci_list[(*nr)].ci_id = attr->mnl_uint8_t;

		/**
		 * get CI's interface index
		 */
		if ( (ret = calm_get_IFINDEX(nl, attr->mnl_uint8_t, (uint32_t *)&ci_list[(*nr)].if_index)) < 0) {
			debugging(" ! unable to get ifindex from CALM device.\n");
			free(attr);
			goto calm_get_cis_error;
		}

		/**
		 * get interface name
		 */
		if (if_indextoname(ci_list[(*nr)].if_index, ci_list[(*nr)].if_name) == NULL) {
			debugging("if_indextoname(%u)\n", ci_list[(*nr)].if_index);
			debugging(" - CI ID: 0x%08x\n", ci_list[(*nr)].ci_id);
			free(attr);
			goto calm_get_cis_error;
		}

		/**
		 * get MED_TYPE
		 */
		if ( (ret = calm_get_MEDTYPE(nl, attr->mnl_uint8_t, (uint8_t *)&ci_list[(*nr)].med_type)) < 0) {
			debugging(" ! unable to get MEDTYPE from CALM device.\n");
			free(attr);
			goto calm_get_cis_error;
		}
		
		/*
		 * get VCI list
		 */
		if ( (ret = calm_get_vcis(nl, attr->mnl_uint8_t, &ci_list[(*nr)].vci_list, &ci_list[(*nr)].nr_vci)) < 0) {
			debugging(" ! unable to get VCI datas from the CI.\n");
			free(attr);
			goto calm_get_cis_error;
		}

		(*nr)++;
	}
	free(attr);

calm_get_cis_ok:
	if (buf)
		free(buf);
	return 0;

calm_get_cis_error:
	if (buf)
		free(buf);
	if (ci_list)
		free(ci_list);
	*list = NULL;
	return ret;
}

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
int calm_get_vcis(struct nl_handle *nl, uint32_t ci_id, calm_dev_t **list, int *nr)
{
	int ret = CALM_ERR_OTHER;
	int vcis = 0;
	int len;
	unsigned char *buf = NULL;
	calm_dev_t *vci_list = NULL;
	int i;
	int sock;
	struct ifreq ifr;

	if ((list == NULL)||(nr == NULL)||(nl == NULL)||(ci_id == 0)) {
		debugging(" ! wrong parameter(s).\n");
		goto calm_get_vcis_error;
	}

	*nr = 0;
	if ( (ret = calm_get(nl, CALM_A_VCILIST, ci_id, &buf, &len)) < 0) {
		debugging(" ! unable to send/receive data to/from CALM\n");
		goto calm_get_vcis_error;
	}

	mnl_attr_t *attr = NULL;
	while ((attr = mnl_nextattr(buf, len, attr))) {
		if ((attr->attr == CALM_A_VCILIST_VCI)&&(attr->mnl_uint32_t != 0))
			vcis++;
	}
	free(attr);

	if (vcis == 0) {
//		debugging(" ! no VCI found.\n");
		goto calm_get_vcis_ok;
	}

	if ((vci_list = calloc(sizeof(calm_dev_t) * vcis, 1)) == NULL) {
		debugging(" ! unable to allocate enough memory area.\n");
		goto calm_get_vcis_error;
	}
	*list = vci_list;

	attr = NULL;
	while ((attr = mnl_nextattr(buf, len, attr))) {
		if ((attr->attr != CALM_A_VCILIST_VCI)||(attr->mnl_uint32_t == 0))
			continue;

		vci_list[(*nr)].ci_id = attr->mnl_uint32_t;

#if 0
		/*
		 * get bandwidth
		 */
		vci_list[(*nr)].avail_bandwidth = calm_get_DATARATE(nl, attr->mnl_uint32_t);
		if (vci_list[(*nr)].avail_bandwidth == -1) {
			free(attr);
			goto calm_get_vcis_error;
		}
#endif
		/**
		 * get VCI's interface index
		 */
		if ( (ret = calm_get_IFINDEX(nl, attr->mnl_uint32_t, (uint32_t *)&vci_list[(*nr)].if_index)) < 0) {
			debugging(" ! unable to get ifindex from CALM device.\n");
			free(attr);
			goto calm_get_vcis_error;
		}

		/**
		 * get interface name
		 */
		if (if_indextoname(vci_list[(*nr)].if_index, vci_list[(*nr)].if_name) == NULL) {
			debugging("if_indextoname(%u)\n", vci_list[(*nr)].if_index);
			debugging(" - VCI ID: 0x%08x\n", vci_list[(*nr)].ci_id);
			free(attr);
			goto calm_get_vcis_error;
		}

		if ((vci_list[(*nr)].nr_ipv6addr = calm_get_addrs(vci_list[(*nr)].if_index, vci_list[(*nr)].ipv6addr, CALM_MAX_INTF)) < 0) {
			debugging("calm_get_addresses(%u)\n", vci_list[(*nr)].if_index);
			free(attr);
			goto calm_get_vcis_error;
		}
		
		/**
		 * get MAC address
		 */
		if ( (sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
			debugging(" - Socket creation to get MAC addr failed.\n");
			free(attr);
			goto calm_get_vcis_error;
		}
		ifr.ifr_addr.sa_family = AF_INET;
		strncpy(ifr.ifr_name, vci_list[(*nr)].if_name, IFNAMSIZ - 1);
		if (ioctl(sock, SIOCGIFHWADDR, &ifr))  {
			debugging(" - Ioctl(SIOCGIFHWADDR)\n");
			free(attr);
			close(sock);
			goto calm_get_vcis_error;
		}
		close(sock);
		for(i = 0; i < 6; i++)
			vci_list[(*nr)].hwaddr[i] = (unsigned char)ifr.ifr_hwaddr.sa_data[i];

		/**
		 * get CCK-ID
		 */
		vci_list[(*nr)].cck_id = (uint8_t)calm_get_cckid();
	

        /**
		 * get directivity
		 */
		ret = calm_get_DIR(nl, vci_list[(*nr)].ci_id, &vci_list[(*nr)].dir);
		if (ret == CALM_ERR_NOTIMP) {
			memset(&vci_list[(*nr)].dir, 0, sizeof(vci_list[(*nr)].dir));
		} else if (ret < 0) {
			debugging(" ! unable to get DIR from CALM device.\n");
			free(attr);
			goto calm_get_vcis_error;
		}
		
        (*nr)++;
	}
	free(attr);

calm_get_vcis_ok:
	if (buf)
		free(buf);
//	if (ifas)
//		freeifaddrs(ifas);
	return 0;

calm_get_vcis_error:
	if (buf)
		free(buf);
	if (vci_list)
		free(vci_list);
	*list = NULL;
	return ret;
}

#define CALM_GET(xattr, xtype) \
int calm_get_##xattr(struct nl_handle *nl, uint32_t vci_id, xtype *retval) \
{ \
	int ret = CALM_ERR_OTHER; \
	int len; \
	unsigned char *buf = NULL; \
\
	if ((nl == NULL)||(vci_id == 0)) { \
		debugging(" ! wrong parameters.\n"); \
		goto err; \
	} \
\
	if ( (ret = calm_get(nl, CALM_A_##xattr, vci_id, &buf, &len)) < 0) { \
		debugging(" ! unable to send/receive data to/from CALM.\n"); \
		goto err; \
	} \
\
	ret = CALM_ERR_PARSE; \
	mnl_attr_t *attr = mnl_nextattr(buf, len, NULL); \
	if (attr == NULL) { \
		debugging(" ! unable to get requested attribute from the answer.\n"); \
		goto err; \
	} \
	*retval = attr->mnl_##xtype; \
	free(attr); \
	ret = 0; \
\
err: \
	if (buf) \
		free(buf); \
	return ret; \
}

CALM_GET(AUXCH, uint8_t);
CALM_GET(CTRLCH, uint8_t);
CALM_GET(SERVCH, uint8_t);
CALM_GET(RXSENS, uint8_t);
CALM_GET(TXPWR, uint8_t);
CALM_GET(DATARATE, uint32_t);
CALM_GET(RELIABILITY, uint8_t);
CALM_GET(BLOCKLEN, uint16_t);
CALM_GET(MINPRIO, uint8_t);
CALM_GET(MAXINACT, uint16_t);
CALM_GET(PEERDIST, uint16_t);
CALM_GET(CICLASS, uint8_t);
CALM_GET(COMMRANGEREF, uint16_t);
CALM_GET(MINSUSPPRIO, uint8_t);
CALM_GET(MEDTYPE, uint8_t);
CALM_GET(COMMODES, uint8_t);
CALM_GET(CIACCESSCLASS, uint8_t);
CALM_GET(FREEAIRTIME, uint8_t);
CALM_GET(MEDUSEOBSTIME, uint16_t);
CALM_GET(SUSPSUPPORTED, uint8_t);
CALM_GET(MAXFRAMELEN, uint8_t);
CALM_GET(CISTATE, uint8_t);
CALM_GET(MINPRIOCROSSCI, uint8_t);
CALM_GET(IFINDEX, uint32_t);
CALM_GET(CCKID, uint8_t);

int calm_get_DIR(struct nl_handle *nl, uint32_t vci_id, struct calm_dir *dir)
{
	int ret = CALM_ERR_OTHER;
	int len;
	unsigned char *buf = NULL;
	mnl_attr_t *attr = NULL;

	if ((nl == NULL) || (vci_id == 0)) {
		debugging(" ! wrong parameters.\n");
		goto err;
	}

	if ( (ret = calm_get(nl, CALM_A_DIR, vci_id, &buf, &len)) < 0) {
		debugging(" ! unable to send/receive data to/from CALM.\n");
		goto err;
	}

	ret = CALM_ERR_PARSE;
	//mnl_attr_t *attr = NULL;
	int attrs[6] = { 0, 0, 0, 0, 0, 0 };
	do {
		attr = mnl_nextattr(buf, len, attr);
		if (((attrs[0] != 1) || (attrs[1] != 1) || (attrs[2] != 1) ||
				(attrs[3] != 1) || (attrs[4] != 1) || (attrs[5] != 1)) &&
				(attr == NULL)) {
			debugging(" ! unable to get requested attribute from the answer.\n");
			goto err;
		}

		switch (attr->attr) {
			case CALM_A_DIR:
				break;

			case CALM_A_DIR_MODE:
				dir->mode = attr->mnl_uint8_t;
				attrs[0] = 1;
				break;

			case CALM_A_DIR_PREDEF:
				dir->predef = attr->mnl_uint8_t;
				attrs[1] = 1;
				break;

			case CALM_A_DIR_BSAZIMUTH:
				dir->bsazimuth = (__s16)attr->mnl_uint16_t;
				attrs[2] = 1;
				break;

			case CALM_A_DIR_BSELEVATION:
				dir->bselevation = (__s8)attr->mnl_uint8_t;
				attrs[3] = 1;
				break;

			case CALM_A_DIR_OPENHORIZ:
				dir->openhoriz = attr->mnl_uint8_t;
				attrs[4] = 1;
				break;

			case CALM_A_DIR_OPENVERT:
				dir->openvert = attr->mnl_uint8_t;
				attrs[5] = 1;
				break;

			default:
				debugging(" ! invalid attribute %d\n", attr->attr);
				goto err;
		}
	} while ((attrs[0] != 1) || (attrs[1] != 1) || (attrs[2] != 1) ||
			(attrs[3] != 1) || (attrs[4] != 1) || (attrs[5] != 1));

	ret = 0;

err:
	if (attr)
		free(attr);
	if (buf)
		free(buf);
	return ret;
}

int calm_get_LASTRX(struct nl_handle *nl, uint32_t vci_id, uint32_t *sec, uint32_t *usec)
{
	int ret = CALM_ERR_OTHER;
	int len;
	unsigned char *buf = NULL;
	mnl_attr_t *attr = NULL;

	if ((nl == NULL) || (vci_id == 0)) {
		debugging(" ! invalid parameters.\n");
		goto err;
	}

	if ( (ret = calm_get(nl, CALM_A_LASTRX, vci_id, &buf, &len)) < 0) {
		debugging(" ! unable to send/receive data to/from CALM.\n");
		goto err;
	}

	ret = CALM_ERR_PARSE;
	int attrs[2] = { 0, 0 };
	do {
		attr = mnl_nextattr(buf, len, attr);
		if (((attrs[0] != 1) || (attrs[1] != 1)) &&
				(attr == NULL)) {
			debugging(" ! unable to get requested attribute from the answer.\n");
			goto err;
		}

		switch (attr->attr) {
			case CALM_A_LASTRX:
				break;
			case CALM_A_LASTRX_SEC:
				*sec = attr->mnl_uint32_t;
				attrs[0] = 1;
				break;
			case CALM_A_LASTRX_USEC:
				*usec = attr->mnl_uint32_t;
				attrs[1] = 1;
				break;
			default:
				debugging(" ! invalid attribute %d\n", attr->attr);
				goto err;
		}
	} while ((attrs[0] != 1) || (attrs[1] != 1));

	ret = 0;

err:
	if (attr)
		free(attr);
	if (buf)
		free(buf);
	return ret;
}

int calm_get_REGINFO(struct nl_handle *nl, uint32_t vci_id, uint8_t *state, unsigned char **ri, int *ri_len)
{
	int ret = CALM_ERR_OTHER;
	int len;
	unsigned char *buf = NULL;
	mnl_attr_t *attr = NULL;

	if ((nl == NULL) || (vci_id == 0)) {
		debugging(" ! wrong parameters.\n");
		goto err;
	}

	if ( (ret = calm_get(nl, CALM_A_REGINFO, vci_id, &buf, &len)) < 0) {
		debugging(" ! unable to send/receive data to/from CALM.\n");
		goto err;
	}

	ret = CALM_ERR_PARSE;
	int attrs[2] = { 0, 0 };
	do {
		attr = mnl_nextattr(buf, len, attr);
		if (((attrs[0] != 1) || (attrs[1] != 1)) &&
				(attr == NULL)) {
			debugging(" ! unable to get requested attribute from the answer.\n");
			goto err;
		}

		switch (attr->attr) {
			case CALM_A_REGINFO:
				break;

			case CALM_A_REGINFO_STATE:
				*state = attr->mnl_uint8_t;
				attrs[0] = 1;
				break;

			case CALM_A_REGINFO_LIMITS:
				*ri_len = attr->len;
				*ri = calloc(1, *ri_len);
				if (!*ri) {
					debugging(" ! out of memory\n");
					goto err;
				}
				memcpy(*ri, attr->mnl_val, *ri_len);
				attrs[1] = 1;
				break;

			default:
				debugging(" ! invalid attribute %d\n", attr->attr);
				goto err;
		}
	} while ((attrs[0] != 1) || (attrs[1] != 1));

	ret = 0;

err:
	if (attr)
		free(attr);
	if (buf)
		free(buf);
	return ret;
}

int calm_get_MEDUSAGE(struct nl_handle *nl, uint32_t vci_id, uint8_t *rx, uint8_t *tx)
{
	int ret = CALM_ERR_OTHER;
	int len;
	unsigned char *buf = NULL;
	mnl_attr_t *attr = NULL;

	if ((nl == NULL) || (vci_id == 0)) {
		debugging(" ! wrong parameters.\n");
		goto err;
	}

	if ( (ret = calm_get(nl, CALM_A_MEDUSAGE, vci_id, &buf, &len)) < 0) {
		debugging(" ! unable to send/receive data to/from CALM.\n");
		goto err;
	}

	ret = CALM_ERR_PARSE;
	int attrs[2] = { 0, 0 };
	do {
		attr = mnl_nextattr(buf, len, attr);
		if (((attrs[0] != 1) || (attrs[1] != 1)) &&
				(attr == NULL)) {
			debugging(" ! unable to get requested attribute from the answer.\n");
			goto err;
		}

		switch (attr->attr) {

			case CALM_A_MEDUSAGE:
				break;

			case CALM_A_MEDUSAGE_RX:
				*rx = attr->mnl_uint8_t;
				attrs[0] = 1;
				break;

			case CALM_A_MEDUSAGE_TX:
				*tx = attr->mnl_uint8_t;
				attrs[1] = 1;
				break;

			default:
				debugging(" ! invalid attribute %d\n", attr->attr);
				goto err;
		}
	} while ((attrs[0] != 1) || (attrs[1] != 1));

	ret = 0;

err:
	if (attr)
		free(attr);
	if (buf)
		free(buf);
	return ret;
}

int calm_get_QUEUETHR(struct nl_handle *nl, uint32_t vci_id, uint8_t *low, uint8_t *high)
{
	int ret = CALM_ERR_OTHER;
	int len;
	unsigned char *buf = NULL;
	mnl_attr_t *attr = NULL;

	if ((nl == NULL) || (vci_id == 0)) {
		debugging(" ! wrong parameters.\n");
		goto err;
	}

	if ( (ret = calm_get(nl, CALM_A_QUEUETHR, vci_id, &buf, &len)) < 0) {
		debugging(" ! unable to send/receive data to/from CALM.\n");
		goto err;
	}

	ret = CALM_ERR_PARSE;
	int attrs[2] = { 0, 0 };
	do {
		attr = mnl_nextattr(buf, len, attr);
		if (((attrs[0] != 1) || (attrs[1] != 1)) &&
				(attr == NULL)) {
			debugging(" ! unable to get requested attribute from the answer.\n");
			goto err;
		}

		switch (attr->attr) {
			case CALM_A_QUEUETHR:
				break;

			case CALM_A_QUEUETHR_LOW:
				*low = attr->mnl_uint8_t;
				attrs[0] = 1;
				break;

			case CALM_A_QUEUETHR_HIGH:
				*high = attr->mnl_uint8_t;
				attrs[1] = 1;
				break;

			default:
				debugging(" ! invalid attribute %d\n", attr->attr);
				goto err;
		}
	} while ((attrs[0] != 1) || (attrs[1] != 1));

	ret = 0;

err:
	if (attr)
		free(attr);
	if (buf)
		free(buf);
	return ret;
}

int calm_get_NOTIFY(struct nl_handle *nl, uint32_t vci_id, uint8_t **paramlist)
{
	int ret = CALM_ERR_OTHER;
	int len;
	unsigned char *buf = NULL;
	mnl_attr_t *attr = NULL;
	int plen=0;

	if ((nl == NULL) || (vci_id == 0)) {
		debugging(" ! wrong parameters.\n");
		goto err;
	}

	if ( (ret = calm_get(nl, CALM_A_NOTIFY, vci_id, &buf, &len)) < 0) {
		debugging(" ! unable to send/receive data to/from CALM.\n");
		goto err;
	}

	ret = CALM_ERR_PARSE;
	for (;;) {
		attr = mnl_nextattr(buf, len, attr);
		if (attr == NULL)
			break;

		switch (attr->attr) {

			case CALM_A_NOTIFY:
				break;

			case CALM_A_NOTIFY_PARAM:
				plen++;
				break;

			default:
				debugging(" ! invalid attribute %d\n", attr->attr);
				goto err;
		}
	}
	if(plen != 0) {
        plen++;
		attr = NULL;
		*paramlist = calloc(1, plen);
		if (!*paramlist) {
			debugging(" ! out of memory\n");
			goto err;
		}
		int counter = 0;
		for (;;) {
			attr = mnl_nextattr(buf, len, attr);
			if (attr == NULL)
				break;

			switch (attr->attr) {
				case CALM_A_NOTIFY:
					break;

				case CALM_A_NOTIFY_PARAM:
					*((*paramlist) + counter++) = attr->mnl_uint8_t;
					break;

				default:
					debugging(" ! invalid attribute %d\n", attr->attr);
					goto err;
			}
		}
	}

	ret = 0;

err:
	if (attr)
		free(attr);
	if (buf)
		free(buf);
	return ret;
}


int calm_get_PEERMAC(struct nl_handle *nl, uint32_t vci_id, unsigned char **mac, int *mac_len)
{
	int ret = CALM_ERR_OTHER;
	int len;
	unsigned char *buf = NULL;
	mnl_attr_t *attr = NULL;

	if ((nl == NULL) || (vci_id == 0)) {
		debugging(" ! wrong parameters.\n");
		goto err;
	}

	if ( (ret = calm_get(nl, CALM_A_PEERMAC, vci_id, &buf, &len)) < 0) {
		debugging(" ! unable to send/receive data to/from CALM.\n");
		goto err;
	}

	ret = CALM_ERR_PARSE;
	*mac_len = 0;

	int attrs[2] = { 0, 0 };
	unsigned char *p = NULL;
	do {
		attr = mnl_nextattr(buf, len, attr);
		if (((attrs[0] != 1) || (attrs[1] != 1)) && (attr == NULL)) {
			debugging(" ! unable to get requested attribute from the answer.\n");
			goto err;
		}

		switch (attr->attr) {
			case CALM_A_PEERMAC:
				break;

			case CALM_A_PEERMAC_ADDR:
				if (*mac_len) {
					*mac = calloc(1, *mac_len);
					if (!*mac) {
						debugging(" ! out of memory\n");
						goto err;
					}
					memcpy(*mac, attr->mnl_val, *mac_len);
				} else
					p = attr->mnl_val;
				attrs[1] = 1;
				break;

			case CALM_A_PEERMAC_LEN:
				*mac_len = attr->mnl_uint8_t;
				if (p) {
					*mac = calloc(1, *mac_len);
					if (!*mac) {
						debugging(" ! out of memory\n");
						goto err;
					}
					memcpy(*mac, p, *mac_len);
				}
				attrs[0] = 1;
				break;

			default:
				debugging(" ! invalid attribute %d (type %d, len %d)\n",
						attr->attr, attr->type, attr->len);
				goto err;
		}
	} while ((attrs[0] != 1) || (attrs[1] != 1));

	ret = 0;

err:
	if (attr)
		free(attr);
	if (buf)
		free(buf);
	return ret;
}

int calm_get_MACADDR(struct nl_handle *nl, uint32_t vci_id, unsigned char **mac)
{
	int ret = CALM_ERR_OTHER;
	int len;
	unsigned char *buf = NULL;
	mnl_attr_t *attr =  NULL;

	if ((nl == NULL)||(vci_id == 0)) {
		debugging(" ! wrong parameters.\n");
		goto err;
	}

	if ( (ret = calm_get(nl, CALM_A_MACADDR, vci_id, &buf, &len)) < 0) {
		debugging(" ! unable to send/receive data to/from CALM.\n");
		goto err;
	}

	ret = CALM_ERR_PARSE;
	attr = mnl_nextattr(buf, len, NULL);
	if (attr == NULL) {
		debugging(" ! unable to get requested attribute from the answer.\n");
		goto err;
	}

	/* 6 byte long octet string (MAC ADDRESS) */
	*mac = calloc(1, 6);
	if (!*mac) {
		debugging(" ! out of memory\n");
		goto err;
	}
	memcpy(*mac, attr->mnl_val, 6);

	ret = 0;

err:
	if (attr)
		free(attr);
	if (buf)
		free(buf);
	return ret;
}

#define CALM_SET(xattr, xtype) \
int calm_set_##xattr(struct nl_handle *nl, uint32_t vci_id, xtype *retval) \
{ \
	int ret = CALM_ERR_OTHER; \
	int len; \
	unsigned char *buf = NULL; \
\
	if ((nl == NULL)||(vci_id == 0)) { \
		debugging(" ! wrong parameters.\n"); \
		goto err; \
	} \
\
	if ( (ret = calm_set(nl, CALM_A_##xattr, (void *)retval, vci_id, &buf, &len)) < 0) { \
		debugging(" ! unable to send/receive data to/from CALM.\n"); \
		goto err; \
	} \
\
	ret = CALM_ERR_PARSE; \
	mnl_attr_t *attr = mnl_nextattr(buf, len, NULL); \
	if (attr == NULL) { \
		debugging(" ! unable to get requested attribute from the answer.\n"); \
		goto err; \
	} \
	*retval = attr->mnl_##xtype; \
	free(attr); \
	ret = 0; \
\
err: \
	if (buf) \
		free(buf); \
	return ret; \
}

CALM_SET(AUXCH, uint8_t);
CALM_SET(CTRLCH, uint8_t);
CALM_SET(SERVCH, uint8_t);
CALM_SET(RXSENS, uint8_t);
CALM_SET(TXPWR, uint8_t);
CALM_SET(DATARATE, uint32_t);
CALM_SET(BLOCKLEN, uint16_t);
CALM_SET(MINPRIO, uint8_t);
CALM_SET(MAXINACT, uint16_t);
CALM_SET(MINSUSPPRIO, uint8_t);
CALM_SET(FREEAIRTIME, uint8_t);
CALM_SET(MEDUSEOBSTIME, uint16_t);
CALM_SET(MAXFRAMELEN, uint8_t);
CALM_SET(MINPRIOCROSSCI, uint8_t);
CALM_SET(CCKID, uint8_t);

int calm_set_DIR(struct nl_handle *nl, uint32_t vci_id, struct calm_dir *dir)
{
	int ret = CALM_ERR_CREATE;
	int hdr_len, len, buflen;
	unsigned char *msg, *buf = NULL, *nest;

	if ((nl == NULL)||(vci_id == 0)) {
		debugging(" ! wrong parameters.n");
		goto err;
	}

	if ((msg = mnl_generatemsghdr(CALM_C_SET, vci_id, &hdr_len)) == NULL)
		goto err;
	len = hdr_len;
	if (((msg = mnl_addattr(msg, CALM_A_DIR, 0, 0, &len, &nest)) == NULL) ||
			((msg = mnl_addattr(msg, CALM_A_DIR_MODE, &dir->mode, sizeof(dir->mode), &len, NULL)) == NULL) ||
			((msg = mnl_addattr(msg, CALM_A_DIR_PREDEF, &dir->predef, sizeof(dir->predef), &len, NULL)) == NULL) ||
			((msg = mnl_addattr(msg, CALM_A_DIR_BSAZIMUTH, &dir->bsazimuth, sizeof(dir->bsazimuth), &len, NULL)) == NULL) ||
			((msg = mnl_addattr(msg, CALM_A_DIR_BSELEVATION, &dir->bselevation, sizeof(dir->bselevation), &len, NULL)) == NULL) ||
			((msg = mnl_addattr(msg, CALM_A_DIR_OPENHORIZ, &dir->openhoriz, sizeof(dir->openhoriz), &len, NULL)) == NULL) ||
			((msg = mnl_addattr(msg, CALM_A_DIR_OPENVERT, &dir->openvert, sizeof(dir->openvert), &len, NULL)) == NULL))
		goto err;

	mnl_end(msg, hdr_len, len);

	ret =  calm_sndrcv(nl, vci_id, msg, len, &buf, &buflen);

err:
	return ret;
}

int calm_set_REGINFO(struct nl_handle *nl, uint32_t vci_id, uint8_t state, unsigned char *ri, int ri_len)
{
	int ret = CALM_ERR_CREATE;
	int len, hdr_len, buflen;
	unsigned char *msg, *buf = NULL, *nest;

	if ((nl == NULL)||(vci_id == 0)) {
		debugging(" ! wrong parameters.n");
		goto err;
	}

	if ((msg = mnl_generatemsghdr(CALM_C_SET, vci_id, &hdr_len)) == NULL)
		goto err;
	len = hdr_len;
	if (((msg = mnl_addattr(msg, CALM_A_REGINFO, 0, 0, &len, &nest)) == NULL) ||
			((msg = mnl_addattr(msg, CALM_A_REGINFO_STATE, &state, sizeof(state), &len, NULL)) == NULL) ||
			((msg = mnl_addattr(msg, CALM_A_REGINFO_LIMITS, ri, ri_len, &len, NULL)) == NULL))
		goto err;

	mnl_end(msg, hdr_len, len);

	ret =  calm_sndrcv(nl, vci_id, msg, len, &buf, &buflen);

err:
	return ret;
}

int calm_set_QUEUETHR(struct nl_handle *nl, uint32_t vci_id, uint8_t low, uint8_t high)
{
	int ret = CALM_ERR_CREATE;
	int len, hdr_len, buflen;
	unsigned char *msg, *buf = NULL, *nest;

	if ((nl == NULL)||(vci_id == 0)) {
		debugging(" ! wrong parameters.n");
		goto err;
	}


	if ((msg = mnl_generatemsghdr(CALM_C_SET, vci_id, &hdr_len)) == NULL)
		goto err;
	len = hdr_len;
	if (((msg = mnl_addattr(msg, CALM_A_QUEUETHR, 0, 0, &len, &nest)) == NULL) ||
			((msg = mnl_addattr(msg, CALM_A_QUEUETHR_LOW, &low, sizeof(low), &len, NULL)) == NULL) ||
			((msg = mnl_addattr(msg, CALM_A_QUEUETHR_HIGH, &high, sizeof(high), &len, NULL)) == NULL))
		goto err;

	mnl_end(msg, hdr_len, len);

	ret =  calm_sndrcv(nl, vci_id, msg, len, &buf, &buflen);

err:
	return ret;
}

#define CALM_CMD(xattr, xtype) \
int calm_cmd_##xattr(struct nl_handle *nl, uint32_t vci_id, xtype *retval) \
{ \
	int ret = CALM_ERR_OTHER; \
	int len; \
	unsigned char *buf = NULL; \
\
	if ((nl == NULL)||(vci_id == 0)) { \
		debugging(" ! wrong parameters.\n"); \
		goto err; \
	} \
\
	if ( (ret = calm_cmd(nl, CALM_A_##xattr, (void *)retval, vci_id, &buf, &len)) < 0) { \
		debugging(" ! unable to send/receive data to/from CALM.\n"); \
		goto err; \
	} \
\
	ret = CALM_ERR_PARSE; \
	mnl_attr_t *attr = mnl_nextattr(buf, len, NULL); \
	if (attr == NULL) { \
		debugging(" ! unable to get requested attribute from the answer.\n"); \
		goto err; \
	} \
	*retval = attr->mnl_##xtype; \
	free(attr); \
	ret = 0; \
\
err: \
	if (buf) \
		free(buf); \
	return ret; \
}

CALM_CMD(CISTATECMD, uint8_t);
CALM_CMD(WAKEUP, uint8_t);
CALM_CMD(VCI, uint8_t);

int calm_cmd_VENDOR(struct nl_handle *nl, uint32_t vci_id, uint8_t *data, size_t dlen)
{
	int ret = CALM_ERR_CREATE;
	int len, hdr_len, buflen;
	unsigned char *msg, *buf = NULL;
//	unsigned char *nest;

	if ((nl == NULL)||(vci_id == 0)) {
		debugging(" ! wrong parameters.n");
		goto err;
	}

	if ((msg = mnl_generatemsghdr(CALM_C_SET, vci_id, &hdr_len)) == NULL)
		goto err;
	len = hdr_len;
	if ((msg = mnl_addattr(msg, CALM_A_VENDOR, data, dlen, &len, NULL)) == NULL)
		goto err;

	mnl_end(msg, hdr_len, len);

	ret =  calm_sndrcv(nl, vci_id, msg, len, &buf, &buflen);

err:
	return ret;
}

int calm_cmd_MONITOR(struct nl_handle *nl, uint32_t vci_id, uint8_t param, uint8_t active)
{
	int ret = CALM_ERR_CREATE;
	int len, hdr_len, buflen;
	unsigned char *msg, *buf = NULL, *nest;

	if ((nl == NULL)||(vci_id == 0)) {
		debugging(" ! wrong parameters.n");
		goto err;
	}

	if ((msg = mnl_generatemsghdr(CALM_C_CMD, vci_id, &hdr_len)) == NULL)
		goto err;
	len = hdr_len;
	if (((msg = mnl_addattr(msg, CALM_A_MONITOR, 0, 0, &len, &nest)) == NULL) ||
			((msg = mnl_addattr(msg, CALM_A_MONITOR_PARAM, &param, sizeof(param), &len, NULL)) == NULL) ||
			((msg = mnl_addattr(msg, CALM_A_MONITOR_ACTIVE, &active, sizeof(active), &len, NULL)) == NULL))
		goto err;

	mnl_end(msg, hdr_len, len);

	/*
	int i;
	unsigned char *m = msg;
	for (i = 0; i < len; i++)
		printf("%02x", m[i]);
	printf("\n");
	*/

	ret =  calm_sndrcv(nl, vci_id, msg, len, &buf, &buflen);

err:
	return ret;
}

int calm_cmd_UNITDATA(struct nl_handle *nl, uint32_t vci_id, uint8_t ssap, uint8_t scckid, uint32_t sciid, uint8_t dsap, uint8_t dcckid, uint32_t dciid, uint8_t prio, unsigned char *data, size_t dlen, unsigned char * param, size_t plen)
{
	int ret = CALM_ERR_CREATE;
	int len, hdr_len, buflen;
	unsigned char *msg, *buf = NULL, *nest;

	if ((nl == NULL)||(vci_id == 0)) {
		debugging(" ! wrong parameters.n");
		goto err;
	}

	if ((msg = mnl_generatemsghdr(CALM_C_CMD, vci_id, &hdr_len)) == NULL)
		goto err;
	len = hdr_len;
	if (((msg = mnl_addattr(msg, CALM_A_UNITDATA, 0, 0, &len, &nest)) == NULL) ||
			((msg = mnl_addattr(msg, CALM_A_UNITDATA_SSAP, &ssap, sizeof(ssap), &len, NULL)) == NULL) ||
			((msg = mnl_addattr(msg, CALM_A_UNITDATA_SRCCCK, &scckid, sizeof(scckid), &len, NULL)) == NULL) ||
			((msg = mnl_addattr(msg, CALM_A_UNITDATA_SRCCIID, &sciid, sizeof(sciid), &len, NULL)) == NULL) ||
			((msg = mnl_addattr(msg, CALM_A_UNITDATA_DSAP, &dsap, sizeof(dsap), &len, NULL)) == NULL) ||
			((msg = mnl_addattr(msg, CALM_A_UNITDATA_DSTCCK, &dcckid, sizeof(dcckid), &len, NULL)) == NULL) ||
			((msg = mnl_addattr(msg, CALM_A_UNITDATA_DSTCIID, &dciid, sizeof(dciid), &len, NULL)) == NULL) ||
			((msg = mnl_addattr(msg, CALM_A_UNITDATA_PRIO, &prio, sizeof(prio), &len, NULL)) == NULL) ||
			((msg = mnl_addattr(msg, CALM_A_UNITDATA_DATA, data, dlen, &len, NULL)) == NULL) ||
			((msg = mnl_addattr(msg, CALM_A_UNITDATA_PARAM, &param, plen, &len, NULL)) == NULL))
		goto err;

	mnl_end(msg, hdr_len, len);

	ret =  calm_sndrcv(nl, vci_id, msg, len, &buf, &buflen);

err:
	return ret;
}
