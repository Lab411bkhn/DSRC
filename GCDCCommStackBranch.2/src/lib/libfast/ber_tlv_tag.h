/*
 * $Id: ber_tlv_tag.h $
 *
 * This file is part of the CALM FAST Message Library.
 * 
 * Author: Andras Takacs <andras.takacs@ramsys.hu>
 *
 * Copyright 2006-2009 Ramsys Zrt
 *
 * CALM FAST Message Library is free software; you can redistribute
 * it and/or modify it under the terms of the GNU LEsser General Public
 * License as published by the Free Software Foundation; version 3 of
 * the License.
 *
 * CALM FAST Message Library is distributed in the hope that it will
 * be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with CALM FAST Message Library; if not, write to the Free
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307 USA.
 */

/*-
 * Copyright (c) 2003, 2004 Lev Walkin <vlm@lionet.info>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_BER_TLV_TAG_H_
#define	_BER_TLV_TAG_H_

#ifdef __cplusplus
extern "C" {
#endif

enum asn_tag_class {
	ASN_TAG_CLASS_UNIVERSAL		= 0,	/* 0b00 */
	ASN_TAG_CLASS_APPLICATION	= 1,	/* 0b01 */
	ASN_TAG_CLASS_CONTEXT		= 2,	/* 0b10 */
	ASN_TAG_CLASS_PRIVATE		= 3	/* 0b11 */
};
typedef unsigned ber_tlv_tag_t;	/* BER TAG from Tag-Length-Value */

/*
 * Tag class is encoded together with tag value for optimization purposes.
 */
#define	BER_TAG_CLASS(tag)	((tag) & 0x3)
#define	BER_TAG_VALUE(tag)	((tag) >> 2)
#define	BER_TLV_CONSTRUCTED(tagptr)	(((*(const uint8_t *)tagptr)&0x20)?1:0)

#define	BER_TAGS_EQUAL(tag1, tag2)	((tag1) == (tag2))

/*
 * Several functions for printing the TAG in the canonical form
 * (i.e. "[PRIVATE 0]").
 * Return values correspond to their libc counterparts (if any).
 */
ssize_t __LIBFAST__ber_tlv_tag_snprint(ber_tlv_tag_t tag, char *buf, size_t buflen);
ssize_t __LIBFAST__ber_tlv_tag_fwrite(ber_tlv_tag_t tag, FILE *);
char *__LIBFAST__ber_tlv_tag_string(ber_tlv_tag_t tag);


/*
 * This function tries to fetch the tag from the input stream.
 * RETURN VALUES:
 * 	 0:	More data expected than bufptr contains.
 * 	-1:	Fatal error deciphering tag.
 *	>0:	Number of bytes used from bufptr. tag_r will contain the tag.
 */
ssize_t __LIBFAST__ber_fetch_tag(const void *bufptr, size_t size, ber_tlv_tag_t *tag_r);

/*
 * This function serializes the tag (T from TLV) in BER format.
 * It always returns number of bytes necessary to represent the tag,
 * it is a caller's responsibility to check the return value
 * against the supplied buffer's size.
 */
size_t __LIBFAST__ber_tlv_tag_serialize(ber_tlv_tag_t tag, void *bufptr, size_t size);

#ifdef __cplusplus
}
#endif

#endif	/* _BER_TLV_TAG_H_ */
