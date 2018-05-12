/*
 * $Id: mininl.h $
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
 * @file mininl.h
 * @brief Header for mini netlink wrapper.
 */

#ifndef __LIBCALMMEDIA_MININLLIB_H_
#define __LIBCALMMEDIA_MININLLIB_H_

#include <sys/socket.h>
#include <linux/types.h>
#include <linux/netlink.h>
#include <linux/genetlink.h>

int mininl_get_last_nlmsg_error();

/**
 * Netlink handle
 */
struct nl_handle
{
	/** Local socket address */
	struct sockaddr_nl	h_local;

	/** Destination socket address */
	struct sockaddr_nl	h_peer;

	/** File descriptor of the socket */
	int					h_fd;

	/** Protocoll (NETLINK_GENERIC) */
	int					h_proto;

	unsigned int		h_seq_next;
	unsigned int		h_seq_expect;

	/** Flags */
	int					h_flags;
};

#ifndef LIBCALMMEDIA_NO_NLA_ENUM
/**
  * Standard attribute types to specify validation policy
  */
enum {
	NLA_UNSPEC,	/**< Unspecified type */
	NLA_U8,		/**< 8bit integer */
	NLA_U16,	/**< 16bit integer */
	NLA_U32,	/**< 32bit integer */
	NLA_U64,	/**< 64bit integer */
	NLA_STRING,	/**< character string */
	NLA_FLAG,	/**< flag */
	NLA_MSECS,	/**< micro seconds (64bit) */
	NLA_NESTED,	/**< nested attributes */
	__NLA_TYPE_MAX,
};

/**
 * attribute validation policy
 *
 * Policies are defined as arrays of this struct, the array must
 * be accessible by attribute type up to the highest identifier
 * to be expected.
 */
struct nla_policy {
	/** Type of attribute or NLA_UNSPEC */
	uint16_t	type;

	/** Minimal length of payload required to be available */
	uint16_t	minlen;

	/** Maximal length of payload required to be available */
	uint16_t	maxlen;
};
#endif

/**
 * Netlink attribute
 */
typedef struct {
	uint32_t attr;  /**< CALM attribute */
	uint32_t type;  /**< NLA attribute type */
	uint32_t len;   /**< NLA attribute length */
	uint32_t ci_id; /**< VCI/CI id */
	uint8_t *value; /**< pointer to the value */
	union {
		uint8_t u8;     /**< u8 value */
		uint16_t u16;   /**< u16 value */
		uint32_t u32;   /**< u32 value */
	} u;
#define mnl_val value
#define mnl_uint8_t u.u8
#define mnl_uint16_t u.u16
#define mnl_uint32_t u.u32

	/* internal variables */
	uint32_t mnl_attr_pos; /**< internal variable for mnl_netattr(), position to the next attribute */
} mnl_attr_t;

extern char calm_errstr[][256];
extern uint8_t calm_policy[];

/**
 * Get error string corresponding to a specific error code.
 *
 * @param errcode CALM error code
 *
 * @return error string
 */
extern char *calm_get_errstr(int errcode);

/**
 * Allocate new netlink socket handle.
 *
 * @return Newly allocated netlink socket handle or NULL.
 */
struct nl_handle * mnl_handle_alloc();

/**
 * Destroy netlink handler.
 *
 * @param h Netlink handler.
 */
void mnl_handle_destroy(struct nl_handle *h);

/**
 * Connect to CALM device.
 *
 * @param nl netlink handle for the communication
 * @param groups -
 *
 * @return Connection state (0: ok, -1: error)
 */
extern int mnl_connect(struct nl_handle *nl, int groups);

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
extern unsigned char *mnl_generatemsg(int cmd, int attr, void *val, unsigned int ci_id, int *msg_len);

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
extern unsigned char *mnl_generatemsghdr(int cmd, unsigned int ci_id, int *msg_len);

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
extern unsigned char *mnl_addattr(unsigned char *m, int attr, void *val, size_t sz, int *msg_len, unsigned char **nest);

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
extern void mnl_end(unsigned char *m, int hdr_len, int msg_len);

/**
 * Send raw data over netlink socket.
 * @arg handle		Netlink handle.
 * @arg buf		Data buffer.
 * @arg size		Size of data buffer.
 * @return Number of characters written on success or a negative error code.
 */
extern int mnl_sendto(struct nl_handle *handle, void *buf, size_t size);

/**
 * Receive netlink message from netlink socket.
 * @param handle Netlink handle.
 * @param nla Destination pointer for peer's netlink address.
 * @param buf Destination pointer for message content.
 * @param creds	Destination pointer for credentials.
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
extern int mnl_recv(struct nl_handle *handle, struct sockaddr_nl *nla, unsigned char **buf, struct ucred **creds);

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
extern int mnl_send(struct nl_handle *nl, unsigned char *msg, int msg_len, unsigned char **buf, int *len);

/**
 * Check sequence
 *
 * @param h NL handle
 * @param buf answer's buffer
 *
 * @retun error code (0: ok)
 */
int mnl_checkseq(struct nl_handle * h, unsigned char * buf);

/**
 * Check answer.
 *
 * @param buf answer's buffer
 * @param ci_id CI IDD
 *
 * @return error code (0: ok)
 */
extern int mnl_checkmsg(unsigned char *buf, uint32_t ci_id);

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

extern int mnl_checkmsg2(unsigned char *buf, uint32_t ci_id);

/**
 * Extract attributes from the answer.
 *
 * @param buf answer's buffer
 * @param len length of buf
 * @param attr pointer to the current attribute
 *
 * @return pointer to the next attribute
 */
extern mnl_attr_t *mnl_nextattr(unsigned char *buf, size_t len, mnl_attr_t *attr);

/**
 * Close/Disconnect netlink socket and free handle
 * @arg handle		Netlink handle
 */
extern void mnl_close(struct nl_handle *handle);

/**
 * Dump the buffer to strout in hex.
 *
 * @param buf buffer
 * @param len size of buffer
 */
extern void mnl_dumpmsg(unsigned char *buf, size_t len);

/**
 * iterate over a stream of attributes
 *
 * @arg pos		loop counter, set to current attribute
 * @arg head	head of attribute stream
 * @arg len		length of attribute stream
 * @arg rem		initialized to len, holds bytes currently remaining in stream
 */
#define nla_for_each_attr(pos, head, len, rem) \
	for (pos = head, rem = len; \
	     rem >= sizeof(*pos) && pos->nla_len >= sizeof(*pos) && pos->nla_len <= rem; \
	     (pos = (struct nlattr*)((char *)pos + NLA_ALIGN(pos->nla_len)), (rem -= NLA_ALIGN(pos->nla_len))))

/**
 * iterate over a stream of nested attributes
 *
 * @arg pos	loop counter, set to current attribute
 * @arg nla	attribute containing the nested attributes
 * @arg rem	initialized to len, holds bytes currently remaining in stream
 */
#define nla_for_each_nested(pos, nla, rem) \
	for (pos = nla + NLA_HDRLEN, rem = nla->nla_len - NLA_HDRLEN; \
	     rem >= sizeof(*pos) && pos->nla_len >= sizeof(*pos) && pos->nla_len <= rem; \
	     (pos = (struct nlattr*)((char *)pos + NLA_ALIGN(pos->nla_len)), (rem -= NLA_ALIGN(pos->nla_len))))

/**
 * Validate a stream of attributes
 *
 * @arg head		head of attribute stream
 * @arg len			length of attribute stream
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
int nla_validate(struct nlattr *head, int len, int maxtype, struct nla_policy *policy);


#endif
