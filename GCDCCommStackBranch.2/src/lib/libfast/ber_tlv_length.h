/*
 * $Id: ber_tlv_length.h $
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
 * Copyright (c) 2003 Lev Walkin <vlm@lionet.info>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_BER_TLV_LENGTH_H_
#define	_BER_TLV_LENGTH_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef ssize_t ber_tlv_len_t;

/*
 * This function tries to fetch the length of the BER TLV value and place it
 * in *len_r.
 * RETURN VALUES:
 *	 0:	More data expected than bufptr contains.
 *	-1:	Fatal error deciphering length.
 *	>0:	Number of bytes used from bufptr.
 * On return with >0, len_r is constrained as -1..MAX, where -1 mean
 * that the value is of indefinite length.
 */
ssize_t __LIBFAST__ber_fetch_length(int _is_constructed, const void *bufptr, size_t size,
	ber_tlv_len_t *len_r);

/*
 * This function expects bufptr to be positioned over L in TLV.
 * It returns number of bytes occupied by L and V together, suitable
 * for skipping. The function properly handles indefinite length.
 * RETURN VALUES:
 * 	Standard {-1,0,>0} convention.
 */
ssize_t __LIBFAST__ber_skip_length(
	struct asn_codec_ctx_s *opt_codec_ctx,	/* optional context */
	int _is_constructed, const void *bufptr, size_t size);

/*
 * This function serializes the length (L from TLV) in DER format.
 * It always returns number of bytes necessary to represent the length,
 * it is a caller's responsibility to check the return value
 * against the supplied buffer's size.
 */
size_t __LIBFAST__der_tlv_length_serialize(ber_tlv_len_t len, void *bufptr, size_t size);

#ifdef __cplusplus
}
#endif

#endif	/* _BER_TLV_LENGTH_H_ */
