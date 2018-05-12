/*
 * $Id: mininl.c $
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
 * @file mininl.c
 * @brief Mini netlink wrapper for libnl.
 */

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <ifaddrs.h>
#include <netdb.h>
#include <net/if.h>
#include <pthread.h>
#include <sys/time.h>

#include <errno.h>
#include <stdlib.h>

#include "mininl.h"
#include "calm.h"
#include <linux/calm.h>

#define PADDINGTO 4

//#define _MININL_DEBUG

#ifdef _MININL_DEBUG 
    #define debugging(...) \
        printf(__VA_ARGS__) 
#else 
    #define debugging(...)
#endif

uint8_t calm_policy[CALM_A_MAX + 1] = {
	[CALM_A_CILIST] = NLA_NESTED,
	[CALM_A_CILIST_CI] = NLA_U8,
	[CALM_A_VCILIST] = NLA_NESTED,
	[CALM_A_VCILIST_VCI] = NLA_U32,
	[CALM_A_AUXCH] = NLA_U8,
	[CALM_A_CTRLCH] = NLA_U8,
	[CALM_A_SERVCH] = NLA_U8,
	[CALM_A_RXSENS] = NLA_U8,
	[CALM_A_TXPWR] = NLA_U8,
	[CALM_A_DATARATE] = NLA_U32,
	[CALM_A_DIR] = NLA_NESTED,
	[CALM_A_DIR_MODE] = NLA_U8,
	[CALM_A_DIR_PREDEF] = NLA_U8,
	[CALM_A_DIR_BSAZIMUTH] = NLA_U16,
	[CALM_A_DIR_BSELEVATION] = NLA_U8,
	[CALM_A_DIR_OPENHORIZ] = NLA_U8,
	[CALM_A_DIR_OPENVERT] = NLA_U8,
    [CALM_A_RELIABILITY] = NLA_U8,
	[CALM_A_BLOCKLEN] = NLA_U16,
	[CALM_A_MINPRIO] = NLA_U8,
	[CALM_A_LASTRX] = NLA_NESTED,
	[CALM_A_LASTRX_SEC] = NLA_U32,
	[CALM_A_LASTRX_USEC] = NLA_U32,
	[CALM_A_MAXINACT] = NLA_U16,
	[CALM_A_PEERDIST] = NLA_U16,
	[CALM_A_CICLASS] = NLA_U8,
	[CALM_A_COMMRANGEREF] = NLA_U16,
	[CALM_A_MINSUSPPRIO] = NLA_U8,
	[CALM_A_CCKID] = NLA_U8,
	[CALM_A_MEDTYPE] = NLA_U8,
	[CALM_A_COMMODES] = NLA_U8,
	[CALM_A_CIACCESSCLASS] = NLA_U8,
	[CALM_A_REGINFO] = NLA_NESTED,
	[CALM_A_REGINFO_STATE] = NLA_U8,
	[CALM_A_REGINFO_LIMITS] = NLA_UNSPEC,
	[CALM_A_FREEAIRTIME] = NLA_U8,
	[CALM_A_MEDUSAGE] = NLA_NESTED,
	[CALM_A_MEDUSAGE_RX] = NLA_U8,
	[CALM_A_MEDUSAGE_TX] = NLA_U8,
	[CALM_A_MEDUSEOBSTIME] = NLA_U16,
	[CALM_A_SUSPSUPPORTED] = NLA_U8,
	[CALM_A_QUEUETHR] = NLA_NESTED,
	[CALM_A_QUEUETHR_LOW] = NLA_U8,
	[CALM_A_QUEUETHR_HIGH] = NLA_U8,
	[CALM_A_QUEUE] = NLA_NESTED,
	[CALM_A_QUEUE_PRIO] = NLA_U8,
	[CALM_A_QUEUE_LEVEL] = NLA_U8,
	[CALM_A_MACADDR] = NLA_UNSPEC,
	[CALM_A_MAXFRAMELEN] = NLA_U8,
	[CALM_A_CISTATE] = NLA_U8,
	[CALM_A_NOTIFY] = NLA_NESTED,
	[CALM_A_NOTIFY_PARAM] = NLA_U8,
	[CALM_A_MINPRIOCROSSCI] = NLA_U8,
	[CALM_A_PEERMAC] = NLA_NESTED,
	[CALM_A_PEERMAC_ADDR] = NLA_UNSPEC,
	[CALM_A_PEERMAC_LEN] = NLA_U8,
	[CALM_A_IFINDEX] = NLA_U32,
	[CALM_A_ERR] = NLA_NESTED,
	[CALM_A_ERR_ATTR] = NLA_U8,
	[CALM_A_ERR_CODE] = NLA_U8,
	[CALM_A_CISTATECMD] = NLA_U8,
	[CALM_A_WAKEUP] = NLA_U8,
	[CALM_A_VENDOR] = NLA_UNSPEC,
	[CALM_A_VCI] = NLA_U8,
	[CALM_A_MONITOR] = NLA_NESTED,
	[CALM_A_MONITOR_PARAM] = NLA_U8,
	[CALM_A_MONITOR_ACTIVE] = NLA_U8,
	[CALM_A_UNITDATA] = NLA_NESTED,
	[CALM_A_UNITDATA_SSAP] = NLA_U8,
	[CALM_A_UNITDATA_SRCCCK] = NLA_U8,
	[CALM_A_UNITDATA_SRCCIID] = NLA_U32,
	[CALM_A_UNITDATA_DSAP] = NLA_U8,
	[CALM_A_UNITDATA_DSTCCK] = NLA_U8,
	[CALM_A_UNITDATA_DSTCIID] = NLA_U32,
	[CALM_A_UNITDATA_PRIO] = NLA_U8,
	[CALM_A_UNITDATA_DATA] = NLA_UNSPEC,
	[CALM_A_UNITDATA_PARAM] = NLA_UNSPEC,
	[CALM_A_EVENT] = NLA_NESTED,
	[CALM_A_EVENT_TYPE] = NLA_U8,
	[CALM_A_EVENT_VAL] = NLA_U32,
};

char calm_errstr[__CALM_ERRCODE_MAX][256] = {
	[CALM_ERRCODE_SUCCESS] = { "Success." },
	[CALM_ERRCODE_UNSPEC] = { "Unspecified failure." },
	[CALM_ERRCODE_INVALID_PARAM] = { "Invalid parameter." },
	[CALM_ERRCODE_INVALID_PARAMVAL] = { "Invalid parameter value." },
	[CALM_ERRCODE_RI_VIOLATION] = { "RI violation." },
	[CALM_ERRCODE_INVALID_CMD] = { "Invalid command or request." },
	[CALM_ERRCODE_INVALID_CMDVAL] = { "Invalid command or request value." },
	[CALM_ERRCODE_ACCESS_VIOLATION] = { "Access violation." },
	[CALM_ERRCODE_INVALID_CIID] = { "Invalid CI-ID." },
};

int last_nlmsg_error;

int mininl_get_last_nlmsg_error()
{
    return last_nlmsg_error;
}


/**
 * Get error string corresponding to a specific error code.
 *
 * @param errcode CALM error code
 *
 * @return error string
 */
char *calm_get_errstr(int errcode)
{
	if ((errcode < 0) || (errcode > CALM_ERRCODE_MAX))
		return NULL;
	else
		return calm_errstr[errcode];
}

/**
 * Allocate new netlink socket handle.
 *
 * @return Newly allocated netlink socket handle or NULL.
 */
struct nl_handle * mnl_handle_alloc()
{
	struct nl_handle * handle = NULL;

	if (!(handle = (struct nl_handle*) calloc(1, sizeof(*handle))))
	{
		errno = ENOMEM;
		debugging("calloc for netlink handle failed\n");
		return NULL;
	}

	handle->h_local.nl_family = AF_NETLINK;
	handle->h_peer.nl_family = AF_NETLINK;
	
	static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
	static int counter = 0;
	
	pthread_mutex_lock(&lock);
	int c = counter++;
	if (counter > 127)
		counter = 0;
	pthread_mutex_unlock(&lock);
	
	handle->h_local.nl_pid = (pthread_self() << 24 | getpid() << 8) + c;

	handle->h_seq_expect = handle->h_seq_next = time(0);
	return handle;
}

/**
 * Destroy netlink handler.
 *
 * @param h netlink handler.
 */
void mnl_handle_destroy(struct nl_handle *h)
{
	if (h == NULL)
		return;
	free(h);
}

/**
 * Connect to CALM device.
 *
 * @param nl netlink handle for the communication
 * @param groups -
 *
 * @return Connection state (0: ok, -1: error)
 */
int mnl_connect(struct nl_handle *nl, int groups)
{
	socklen_t addrlen;

	if (nl == NULL)
		return CALM_ERR_COMM;

	if (groups)
		nl->h_local.nl_groups = groups;

	if ((nl->h_fd = socket(nl->h_local.nl_family, SOCK_RAW, NETLINK_GENERIC)) < 0) {
		debugging("socket(AF_NETLINK, ...) failed\n");
		return CALM_ERR_COMM;
	}
	
	if (bind(nl->h_fd, (struct sockaddr*) &nl->h_local, sizeof(nl->h_local)) < 0) {
		debugging("bind() failed\n");
		return CALM_ERR_COMM;
	}

	addrlen = sizeof(nl->h_local);
	if (getsockname(nl->h_fd, (struct sockaddr *) &nl->h_local, &addrlen) < 0) {
		debugging("getsockname failed\n");
		return CALM_ERR_COMM;
	}

	if (addrlen != sizeof(nl->h_local)) {
		errno = EADDRNOTAVAIL;
		debugging("Invalid address length\n");
		return CALM_ERR_COMM;
	}

	if (nl->h_local.nl_family != AF_NETLINK) {
		errno = EPFNOSUPPORT;
		debugging("Address format not supported\n");
		return CALM_ERR_COMM;
	}

	nl->h_proto = NETLINK_GENERIC;

	return 0;
}

/**
 * Generate netlink message.
 *
 * @param cmd CALM command
 * @param attr CALM attribute. if you OR attr and 0x100, you may insert whatever you like in a nested attribute
 * @param val attribute's value
 * @param ci_id requested CI's id
 * @param msg_len size of netlink's message buffer. If attr type is unspec, you must save length of unspec data in this variable as well
 *
 * @return netlink message
 */
unsigned char *mnl_generatemsg(int cmd, int attr, void *val, unsigned int ci_id, int *msg_len)
{
	struct nlmsghdr *msg = NULL;
	struct genlmsghdr *hdr = NULL;
	struct calm_head *chdr = NULL;
	struct nlattr *nla = NULL;
	int attrs_len = 0;
	int unspec_len = 0;
	int nested_plus_formatting = (attr <= 0xff);

	attr = (attr & 0xff);

	if (msg_len == NULL) {
		debugging(" ! wrong parameters.\n");
		return NULL;
	}

	/* calculate size of attributes */
	attrs_len += sizeof(uint16_t) + /* size of attribtes struct */
			     sizeof(uint16_t);  /* size of attribute */

	switch (calm_policy[attr]) {
		case NLA_NESTED:
		  	if(!nested_plus_formatting) {
				unspec_len = *msg_len;
				break;
		  	}
			attrs_len += sizeof(struct nlattr);
		  	switch (calm_policy[attr + 1]) {
			  	case NLA_U8:  attrs_len += sizeof(uint8_t); break;
			  	case NLA_U16: attrs_len += sizeof(uint16_t); break;
			  	case NLA_U32: attrs_len += sizeof(uint32_t); break;
			  	case NLA_UNSPEC: unspec_len = *msg_len; break;
			  	default: printf("mnl_generatemsg: Unable to handle this type!\n");
			}
		  	break;
		case NLA_U8:  attrs_len += sizeof(uint8_t); break;
		case NLA_U16: attrs_len += sizeof(uint16_t); break;
		case NLA_U32: attrs_len += sizeof(uint32_t); break;
		case NLA_UNSPEC: unspec_len = *msg_len; break;
		default: printf("mnl_generatemsg: Unable to handle this type!\n");
	}

	if(unspec_len) {
	  attrs_len += unspec_len;
	}

	/* padding */
	if (attrs_len % PADDINGTO)
		attrs_len += PADDINGTO - (attrs_len % PADDINGTO);

	*msg_len = sizeof(struct nlmsghdr) + sizeof(struct genlmsghdr) + sizeof(struct calm_head) + attrs_len;

	if ((msg = calloc(1, *msg_len)) == NULL) {
		debugging(" ! not enough memory.\n");
		return NULL;
	}

	/* add netlink header */
	msg->nlmsg_len = *msg_len;
	msg->nlmsg_type = CALM_FAMILY;
	msg->nlmsg_flags = NLM_F_REQUEST;
	msg->nlmsg_seq = 0;
	msg->nlmsg_pid = getpid();

	/* add generic netlink header */
	hdr = (struct genlmsghdr *)(((unsigned char *)msg) + sizeof(struct nlmsghdr));
	hdr->cmd = cmd;
	hdr->version = CALM_VERSION;

	/* add CALM header */
	chdr = (struct calm_head *)(((unsigned char *)msg) + sizeof(struct nlmsghdr) + sizeof(struct genlmsghdr));
	chdr->ci_id = ci_id;

	/* add attributes */
	nla = (struct nlattr *)(((unsigned char *)msg) + sizeof(struct nlmsghdr) + sizeof(struct genlmsghdr) + sizeof(struct calm_head));
	nla->nla_len = attrs_len;
	nla->nla_type = attr;
	nla++;

	switch (calm_policy[attr]) {
		case NLA_NESTED:
		  	if(nested_plus_formatting) {
				nla->nla_len = (calm_policy[attr + 1] == NLA_UNSPEC ?
					unspec_len : 4); //0x05;
				nla->nla_type = attr + 1;
				nla++;
				switch (calm_policy[attr + 1]) {
					case NLA_U8:  memcpy((unsigned char *)nla, val, sizeof(uint8_t)); break;
					case NLA_U16: memcpy((unsigned char *)nla, val, sizeof(uint16_t)); break;
					case NLA_U32: memcpy((unsigned char *)nla, val, sizeof(uint32_t)); break;
					case NLA_UNSPEC: memcpy((unsigned char*) nla, val, unspec_len); break;
				}
		  	}
		  	else {
				memcpy((unsigned char*) nla, val, unspec_len);
		  	}
		  	break;
		case NLA_U8:  memcpy((unsigned char *)nla, val, sizeof(uint8_t)); break;
		case NLA_U16: memcpy((unsigned char *)nla, val, sizeof(uint16_t)); break;
		case NLA_U32: memcpy((unsigned char *)nla, val, sizeof(uint32_t)); break;
		case NLA_UNSPEC: memcpy((unsigned char*) nla, val, unspec_len); break;
	}

	return (unsigned char *)msg;
}

/**
 * Generate netlink message header.
 *
 * @param cmd CALM command
 * @param ci_id requested CI's id
 * @param msg_len size of netlink's message buffer
 *
 * @return netlink message
 *
 * @see mnl_end
 */
unsigned char *mnl_generatemsghdr(int cmd, unsigned int ci_id, int *msg_len)
{
	struct nlmsghdr *msg = NULL;
	struct genlmsghdr *hdr = NULL;
	struct calm_head *chdr = NULL;
	//struct nlattr *nla = NULL;

	if (msg_len == NULL) {
		debugging(" ! wrong parameters.\n");
		return NULL;
	}

	*msg_len = sizeof(struct nlmsghdr) + sizeof(struct genlmsghdr) + sizeof(struct calm_head);

	if ((msg = calloc(1, *msg_len)) == NULL) {
		debugging(" ! not enough memory.\n");
		return NULL;
	}

	/* add netlink header */
	msg->nlmsg_len = *msg_len;
	msg->nlmsg_type = CALM_FAMILY;
	msg->nlmsg_flags = NLM_F_REQUEST;
	msg->nlmsg_seq = 0;
	msg->nlmsg_pid = getpid();

	/* add generic netlink header */
	hdr = (struct genlmsghdr *)(((unsigned char *)msg) + sizeof(struct nlmsghdr));
	hdr->cmd = cmd;
	hdr->version = CALM_VERSION;

	/* add CALM header */
	chdr = (struct calm_head *)(((unsigned char *)msg) + sizeof(struct nlmsghdr) + sizeof(struct genlmsghdr));
	chdr->ci_id = ci_id;

	return (unsigned char *)msg;
}

/**
 * Add attribute to a netlink message.
 *
 * @param m netlink message
 * @param attr CALM attribute
 * @param val attribute's value
 * @param sz size of val
 * @param msg_len size of netlink's message buffer
 * @param nest deprecated, use NULL
 *
 * @return netlink message
 *
 * @see mnl_generatemsghdr
 * @see mnl_end
 */
unsigned char *mnl_addattr(unsigned char *m, int attr, void *val, size_t sz, int *msg_len, unsigned char **nest)
{
	struct nlmsghdr *msg = (struct nlmsghdr *)m;
	struct nlattr *nla = NULL;
	int attrs_len = 0;

	*msg_len = msg->nlmsg_len;

	/* calculate size of attributes */
	attrs_len += sizeof(uint16_t) + /* size of attribtes struct */
			     sizeof(uint16_t);  /* size of attribute */

	switch (calm_policy[attr]) {
		case NLA_NESTED:
			break;
		case NLA_U8:  attrs_len += sizeof(uint8_t); break;
		case NLA_U16: attrs_len += sizeof(uint16_t); break;
		case NLA_U32: attrs_len += sizeof(uint32_t); break;
		case NLA_UNSPEC: attrs_len += sz; break;
		default:
			debugging(" ! unknown policy type %d\n", calm_policy[attr]);
			free(msg);
			return NULL;
	}
	if (attrs_len % PADDINGTO)
		attrs_len += PADDINGTO - (attrs_len % PADDINGTO); /* padding */

	*msg_len += attrs_len;

	if ((msg = realloc(msg, *msg_len)) == NULL) {
		debugging(" ! not enough memory.\n");
		return NULL;
	}

	/* add attributes */
	nla = (struct nlattr *)(((unsigned char *)msg) + msg->nlmsg_len);

	/* update netlink header */
	msg->nlmsg_len = *msg_len;

	nla->nla_len = attrs_len;
	nla->nla_type = attr;
	if (calm_policy[attr] == NLA_NESTED)
		*nest = (unsigned char *)nla;

	nla++;
	switch (calm_policy[attr]) {
		case NLA_NESTED:
			break;

		case NLA_U8:
			if (sz != sizeof(uint8_t)) {
				debugging(" ! size mismatch %u\n", sz);
				free(msg);
				return NULL;
			}
			memcpy((unsigned char *)nla, val, sizeof(uint8_t));
			break;

		case NLA_U16:
			if (sz != sizeof(uint16_t)) {
				debugging(" ! size mismatch %u\n", sz);
				free(msg);
				return NULL;
			}
			memcpy((unsigned char *)nla, val, sizeof(uint16_t));
			break;

		case NLA_U32:
			if (sz != sizeof(uint32_t)) {
				debugging(" ! size mismatch %u\n", sz);
				free(msg);
				return NULL;
			}
			memcpy((unsigned char *)nla, val, sizeof(uint32_t));
			break;

		case NLA_UNSPEC:
			memcpy((unsigned char *)nla, val, sz);
			break;

		default:
			debugging(" ! unknown policy type %d\n", calm_policy[attr]);
			free(msg);
			return NULL;
	}

	return (unsigned char *)msg;
}

/**
 * Fix the attr_len value in tzhe netlink header.
 *
 * It will be important, if you use mnl_generatemsghdr and mnl_addattr insted of mnl_generatemsg.
 *
 * @param m netlink message
 * @param hdr_len netlink message's header length (msg_len parameter of mnl_generatemsghdr)
 * @param msg_len netlink message length (msg_len parameter of the last mnl_addattr)
 *
 * @see mnl_generatemsghdr
 * @see mnl_addattr
 */
void mnl_end(unsigned char *m, int hdr_len, int msg_len)
{
	struct nlattr * nla = (struct nlattr *)(m + NLMSG_HDRLEN + GENL_HDRLEN + CALM_HDRLEN);

	nla->nla_len = msg_len - hdr_len;
	//debugging("nest nla_len: 0x%x (%d)\n", nla->nla_len, nla->nla_len);
}

/**
 * Send raw data over netlink socket.
 * @arg handle		Netlink handle.
 * @arg buf		Data buffer.
 * @arg size		Size of data buffer.
 * @return Number of characters written on success or a negative error code.
 */
int mnl_sendto(struct nl_handle *handle, void *buf, size_t size)
{
	int ret;
	struct nlmsghdr * nlhdr = (struct nlmsghdr *)buf;

	nlhdr->nlmsg_seq = handle->h_seq_expect = handle->h_seq_next++;


	if ((ret= sendto(handle->h_fd, buf, size, 0, (struct sockaddr *) &handle->h_peer, sizeof(handle->h_peer))) < 0) {
		errno = -errno;
		return errno;
	}

	return ret;
}

/**
 * Receive netlink message from netlink socket.
 * @arg handle		Netlink handle.
 * @arg nla		Destination pointer for peer's netlink address.
 * @arg buf		Destination pointer for message content.
 * @arg creds		Destination pointer for credentials.
 *
 * Receives a netlink message, allocates a buffer in \c *buf and
 * stores the message content. The peer's netlink address is stored
 * in \c *nla. The caller is responsible for freeing the buffer allocated
 * in \c *buf if a positive value is returned.  Interruped system calls
 * are handled by repeating the read. The input buffer size is determined
 * by peeking before the actual read is done.
 *
 * A non-blocking sockets causes the function to return immediately if
 * no data is available.
 *
 * @return Number of octets read, 0 on EOF or a negative error code.
 */
int mnl_recv(struct nl_handle *handle, struct sockaddr_nl *nla,
	    unsigned char **buf, struct ucred **creds)
{
	socklen_t addrlen = sizeof(handle->h_peer);

	*buf = calloc(2048, sizeof(unsigned char));
	int ret = recvfrom(handle->h_fd, *buf, 2048, 0, (struct sockaddr*)&handle->h_peer, &addrlen);
	return ret;
}


/**
 * Send a netlink message, and receive the reply
 *
 * @param nl netlink handle
 * @param msg netlink message
 * @param msg_len netlink message length
 * @param buf reply buffer
 * @param len size of reply buffer
 *
 * @return
 */
int mnl_send(struct nl_handle *nl, unsigned char *msg, int msg_len, unsigned char **buf, int *len)
{
	int ret = CALM_ERR_OTHER;
	struct ucred *creds = NULL;

	if (mnl_sendto(nl, msg, msg_len) < 0) {
		debugging("unable to send message to the kernel.\n");
		return CALM_ERR_COMM;
	}
	//debugging("waiting for the answer.\n");
	if ((*len = mnl_recv(nl, NULL, buf, &creds)) < 0) {
		debugging("error in message receiving.\n");
		return CALM_ERR_COMM;
	}
	//debugging("check answer.\n");
	if ( (ret = mnl_checkmsg(*buf, 0)) < 0) {
		debugging("maybe error in message checking: %d\n", ret);
		return ret;
	}

	return 0;
}

/**
 * Check sequence
 *
 * @param h NL handle
 * @param buf answer's buffer
 *
 * @retun error code (0: ok)
 */
int mnl_checkseq(struct nl_handle * h, unsigned char * buf)
{
	struct nlmsghdr * nlhdr = (struct nlmsghdr *)buf;

	return (nlhdr->nlmsg_seq != h->h_seq_expect);
}

/**
 * Check answer.
 *
 * @param buf answer's buffer
 * @param ci_id CI IDD
 *
 * @return error code (0: ok)
 */
int mnl_checkmsg(unsigned char *buf, uint32_t ci_id)
{
	struct nlmsghdr *msg = (struct nlmsghdr *)buf;
	struct nlmsgerr *err = (struct nlmsgerr *)(buf + sizeof(struct nlmsghdr));
	//struct calm_head *hdr = (struct calm_head *)(buf + sizeof(struct nlmsghdr) + sizeof(struct genlmsghdr));

	if (buf == NULL) {
		debugging(" ! wrong parameters.\n");
		return CALM_ERR_PARSE;
	}

	if (msg->nlmsg_type == NLMSG_ERROR) {
		debugging(" ! nlmsg error %d\n", err->error);
        last_nlmsg_error = err->error;
		return CALM_ERR_LOW;
	}

	if (msg->nlmsg_type != CALM_FAMILY) {
		debugging(" ! message type mismatch.\n");
		return CALM_ERR_FAMILY;
	}

	/*if (ci_id && (ci_id != hdr->ci_id)) {
		debugging(" ! ci_id mismatch\n");
		return -1;
	}*/

	uint32_t *len = (uint32_t *)buf;
	mnl_attr_t *attr = mnl_nextattr(buf, *len, NULL);
	if (attr == NULL) {
		debugging(" ! unable to extract first attribute from the answer.\n");
		return CALM_ERR_PARSE;
	}
	if (attr->attr == CALM_A_ERR) {
		int e_code = 0;
		int e_attr = 0;

		attr = mnl_nextattr(buf, *len, attr);
		if (attr == NULL) {
			debugging(" ! unable to extract 2. attribute from the answer.\n");
			return CALM_ERR_PARSE;
		}

		if (attr->attr == CALM_A_ERR_ATTR) {
			e_attr = attr->mnl_uint8_t;
		} else if (attr->attr == CALM_A_ERR_CODE) {
			e_code = attr->mnl_uint8_t;
		}

		attr = mnl_nextattr(buf, *len, attr);
		if (attr == NULL) {
			debugging(" ! unable to extract 3. attribute from the answer.\n");
			return CALM_ERR_PARSE;
		}

		if (attr->attr == CALM_A_ERR_ATTR) {
			e_attr = attr->mnl_uint8_t;
		} else if (attr->attr == CALM_A_ERR_CODE) {
			e_code = attr->mnl_uint8_t;
		}

		char *e_str;
		if (e_code >= 0)
			e_str = calm_get_errstr(e_code);
		else
			e_str = strerror(-e_code);
		debugging(" ! error in answer, code: 0x%x (%s), attr: 0x%x\n", e_code, e_str, e_attr);

		free(attr);
		if ( (e_code == CALM_ERRCODE_INVALID_PARAM) || (e_code == CALM_ERRCODE_INVALID_CMD) )
			return CALM_ERR_NOTIMP;
        else if ( (e_code == CALM_ERRCODE_INVALID_PARAMVAL) || (e_code == CALM_ERRCODE_INVALID_CMDVAL) )
            return CALM_ERR_VALUE;
		else if (e_code == CALM_ERRCODE_INVALID_CIID)
            return CALM_ERR_NOCI;
        else {
            last_nlmsg_error = err->error;
			return CALM_ERR_LOW;
        }
	}
	free(attr);

	return 0;
}

/**
 * Check answer.
 *
 * Don't check the content of the message (CALM_A_ERR attribute)
 *
 * @param buf answer's buffer
 * @param ci_id CI IDD
 *
 * @return error code (0: ok)
 */
int mnl_checkmsg2(unsigned char *buf, uint32_t ci_id)
{
	struct nlmsghdr *msg = (struct nlmsghdr *)buf;
	struct nlmsgerr *err = (struct nlmsgerr *)(buf + sizeof(struct nlmsghdr));
	//struct calm_head *hdr = (struct calm_head *)(buf + sizeof(struct nlmsghdr) + sizeof(struct genlmsghdr));

	if (buf == NULL) {
		debugging(" ! wrong parameters.\n");
		return CALM_ERR_PARSE;
	}

	if (msg->nlmsg_type == NLMSG_ERROR) {
		debugging(" ! nlmsg error %d (%s)\n", err->error, strerror(-1 * err->error));
        last_nlmsg_error = err->error;
		return CALM_ERR_LOW;
	}

	if (msg->nlmsg_type != CALM_FAMILY) {
		debugging(" ! message type mismatch.\n");
		return CALM_ERR_FAMILY;
	}

	/*if (ci_id && (ci_id != hdr->ci_id)) {
		debugging(" ! ci_id mismatch\n");
		return -1;
	}*/

	uint32_t *len = (uint32_t *)buf;
	mnl_attr_t *attr = mnl_nextattr(buf, *len, NULL);
	if (attr == NULL) {
		debugging(" ! unable to extract first attribute from the answer.\n");
		return CALM_ERR_PARSE;
	}
	free(attr);

	return 0;
}

/**
 * Extract attributes from the answer.
 *
 * @param buf answer's buffer
 * @param len length of buf
 * @param attr pointer to the current attribute
 *
 * @return pointer to the next attribute
 */
mnl_attr_t *mnl_nextattr(unsigned char *buf, size_t len, mnl_attr_t *attr)
{
	struct nlattr *nla = NULL;

	if (attr == NULL) {
		if ((attr = calloc(1, sizeof(mnl_attr_t))) == NULL) {
			return NULL;
		}
		attr->mnl_attr_pos = sizeof(struct nlmsghdr) + sizeof(struct genlmsghdr);
		attr->ci_id = ((struct calm_head *)(buf + attr->mnl_attr_pos))->ci_id;

		if (attr->ci_id == 0) {
			debugging(" ! CI ID is NULL?\n");
			debugging(" ! sizeof(struct nlmsghdr) = %d, sizeof(struct genlmsghdr) = %d, summ = %d\n", sizeof(struct nlmsghdr), sizeof(struct genlmsghdr), attr->mnl_attr_pos);
			mnl_dumpmsg(buf, len);
		}

		attr->mnl_attr_pos += sizeof(struct calm_head);
	} else {
		if (attr->mnl_attr_pos >= len) {
			free(attr);
			return NULL;
		}
	}

	nla = (struct nlattr *)(buf + attr->mnl_attr_pos);

	//debugging(" ! nla start at %d, attr = %d, len = %d, type = %d, value start at %d\n", attr->mnl_attr_pos, nla->nla_type, nla->nla_len, calm_policy[attr->attr].type, attr->mnl_attr_pos + NLA_HDRLEN);

	attr->mnl_val = NULL;
	attr->mnl_uint8_t = attr->mnl_uint16_t = attr->mnl_uint32_t = 0;
	attr->attr = nla->nla_type;
	attr->len = nla->nla_len;
	attr->type = calm_policy[attr->attr];

	if (attr->type == NLA_NESTED) {
		attr->mnl_attr_pos += sizeof(struct nlattr);
		//debugging(" ! NESTED\n");
	} else {
		unsigned char *val = attr->mnl_val = (unsigned char*)(buf + attr->mnl_attr_pos + NLA_HDRLEN);
		switch (attr->type) {
			case NLA_U8:
				attr->mnl_uint8_t = *((uint8_t *)val);
				break;
			case NLA_U16:
				attr->mnl_uint16_t = *((uint16_t *)val);
				break;
			case NLA_U32:
				attr->mnl_uint32_t = *((uint32_t *)val);
				break;
			case NLA_UNSPEC:
				break;
			default:
				debugging("! invalid attr->type %d\n", attr->type);
				return NULL;
				break;
		}
		attr->mnl_attr_pos += NLA_ALIGN(nla->nla_len);
	}

	return attr;
}

/**
 * Dump the buffer to strout in hex.
 *
 * @param buf buffer
 * @param len size of buffer
 */
void mnl_dumpmsg(unsigned char *buf, size_t len)
{
	int i, c;

	if ((buf == NULL)||(len <= 0))
		return;

	c = len - (len % 4);

	char tmp[512];
	debugging(" --- %p dumping, size is %d bytes ---\n", buf, len);
	sprintf(tmp, "%08x : ", 0);
	for (i = 0;i < c;i++) {
		sprintf(tmp + strlen(tmp), "%02x ", buf[i]);
		if ( i && (i % 4 == 3) && (i % 16 < 15) && (i < len - 2))
			strcat(tmp, "| ");
		if (i && (i % 16 == 15) && (i != c - 1)) {
			debugging("%s\n", tmp);
			sprintf(tmp, "%08x : ", i);
		}
	}
	if (len % 4) {
		for (;i < len;i++)
			sprintf(tmp + strlen(tmp), "%02x ", buf[i]);
	}
	debugging("%s\n", tmp);
	debugging(" ---\n");
}

/**
 * Close/Disconnect netlink socket and free handle
 * @arg handle		Netlink handle
 */
void mnl_close(struct nl_handle *handle)
{
	if (handle->h_fd >= 0) {
		close(handle->h_fd);
		handle->h_fd = -1;
	}

	handle->h_proto = 0;
}

static int validate_nla(struct nlattr *nla, int maxtype, struct nla_policy *policy)
{
	static uint16_t nla_attr_minlen[__NLA_TYPE_MAX] = {
		[NLA_U8]	= sizeof(uint8_t),
		[NLA_U16]	= sizeof(uint16_t),
		[NLA_U32]	= sizeof(uint32_t),
		[NLA_U64]	= sizeof(uint64_t),
		[NLA_STRING]	= 1,
		[NLA_NESTED]	= NLA_HDRLEN,
	};

	struct nla_policy *pt;
	int minlen = 0;

	if (nla->nla_type <= 0 || nla->nla_type > maxtype)
		return 0;

	pt = &policy[nla->nla_type];

	//if (pt->type > NLA_TYPE_MAX)
	//	BUG();

	if (pt->minlen)
		minlen = pt->minlen;
	else if (pt->type != NLA_UNSPEC)
		minlen = nla_attr_minlen[pt->type];

	if (pt->type == NLA_FLAG && nla->nla_len - NLA_HDRLEN > 0) {
		errno = ERANGE;
		return ERANGE;
	}

	if (nla->nla_len - NLA_HDRLEN < minlen) {
		errno = ERANGE;
		return ERANGE;
	}

	if (pt->maxlen && nla->nla_len - NLA_HDRLEN > pt->maxlen) {
		errno = ERANGE;
		return ERANGE;
	}

	if (pt->type == NLA_STRING) {
		char *data = (char*)(nla + NLA_HDRLEN);
		if (data[nla->nla_len - NLA_HDRLEN - 1] != '\0') {
			errno = EINVAL;
			return EINVAL;
		}
	}

	return 0;
}

/**
 * Validate a stream of attributes
 *
 * @arg head		head of attribute stream
 * @arg len		length of attribute stream
 * @arg maxtype		maximum attribute type to be expected
 * @arg policy		validation policy
 *
 * Validates all attributes in the specified attribute stream
 * against the specified policy. Attributes with a type exceeding
 * maxtype will be ignored. See documenation of struct nla_policy
 * for more details.
 *
 * @return 0 on success or a negative error code.
 */
int nla_validate(struct nlattr *head, int len, int maxtype, struct nla_policy *policy)
{
	struct nlattr *nla;
	int rem, err;

	nla_for_each_attr(nla, head, len, rem) {
		err = validate_nla(nla, maxtype, policy);
		if (err < 0)
			goto errout;
	}

	err = 0;
errout:
	return err;
}

#ifdef __MININLLIB__TEST__
int main(void)
{
	struct nl_handle *nl = mnl_handle_alloc();

	printf("! opening connection.\n");

	/* opening connection */
	if (mnl_connect(nl, 0) < 0) {
		debugging(" ! connection error.\n");
		return 1;
	}

	unsigned char buf[512];
	int len;
	int val = 1;
	unsigned char *msg = NULL;

	printf("! generate message...\n");

	/* generate message */
	memset(buf, 0, sizeof(buf));
	if ((msg = mnl_generatemsg(CALM_C_GET, CALM_A_CILIST, &val, 1, &len)) == NULL) {
		debugging(" ! unable to allocate enough memory area.\n");
		return 1;
	}
	printf(" - len: %d\n", len);
	mnl_dumpmsg(msg, len);

	printf("\n");
	printf("! sending message.\n");

	/* send message to the CALM intf */
	if (mnl_sendto(nl, msg, len) < 0) {
		debugging("mnl_send()\n");
	} else printf(" - ok.\n");

	printf("\n");
	printf("! waiting for answer.\n");

	/* recv message from CALM intf */
	unsigned char *recvbuf = NULL;
	struct ucred *creds = NULL;
	if ((len = mnl_recv(nl, NULL, &recvbuf, &creds)) < 0) {
		debugging("mnl_recv()\n");
		return 1;
	}
	printf(" - len: %d\n", len);
	mnl_dumpmsg(recvbuf, len);

	printf("\n");
	printf("! checking answer\n");

	/* check message */
	if (mnl_checkmsg(recvbuf, 1) < 0) {
		debugging(" ! received answer isn't good. :-)\n");
		return 1;
	} else printf(" - ok.\n");

	printf("\n");
	printf("! walking in the tree.\n");

	/* parsing attributes */
	mnl_attr_t *attr = NULL;

	char *attr_names[] = {
		[CALM_A_CILIST] = "CALM_A_CILIST",
		[CALM_A_CILIST_CI] = "CALM_A_CILIST_CI",
		[CALM_A_VCILIST] = "CALM_A_VCILIST",
		[CALM_A_VCILIST_VCI] = "CALM_A_VCILIST_VCI",
	};

	while ((attr = mnl_nextattr(recvbuf, len, attr))) {
		printf(" - attr: 0x%x\n", attr->attr);
		printf("   - name: '%s'\n", attr_names[attr->attr] );
		switch (attr->type) {
			case NLA_U8:
				printf("   - type: u8, value: 0x%02x\n", attr->mnl_uint8_t);
				break;
			case NLA_U16:
				printf("   - type: u16, value: 0x%04x\n", attr->mnl_uint16_t);
				break;
			case NLA_U32:
				printf("   - type: u32, value: 0x%08x\n", attr->mnl_uint32_t);
				break;
		}
	}
	free(attr);

	printf("\n");
	printf("! closing connection\n");

	/* closing connection */
	mnl_close(nl);

	return 0;
}
#endif
