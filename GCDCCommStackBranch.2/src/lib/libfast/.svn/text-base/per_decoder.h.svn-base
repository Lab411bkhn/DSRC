/*
 * $Id: per_decoder.h $
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
 * Copyright (c) 2005, 2007 Lev Walkin <vlm@lionet.info>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_PER_DECODER_H_
#define	_PER_DECODER_H_

#include <asn_application.h>
#include <per_support.h>

#ifdef __cplusplus
extern "C" {
#endif

struct asn_TYPE_descriptor_s;	/* Forward declaration */

/*
 * Unaligned PER decoder of a "complete encoding" as per X.691#10.1.
 * On success, this call always returns (.consumed >= 1), as per X.691#10.1.3.
 */
asn_dec_rval_t __LIBFAST__uper_decode_complete(struct asn_codec_ctx_s *opt_codec_ctx,
	struct asn_TYPE_descriptor_s *type_descriptor,	/* Type to decode */
	void **struct_ptr,	/* Pointer to a target structure's pointer */
	const void *buffer,	/* Data to be decoded */
	size_t size		/* Size of data buffer */
	);

/*
 * Unaligned PER decoder of any ASN.1 type. May be invoked by the application.
 * WARNING: This call returns the number of BITS read from the stream. Beware.
 */
asn_dec_rval_t __LIBFAST__uper_decode(struct asn_codec_ctx_s *opt_codec_ctx,
	struct asn_TYPE_descriptor_s *type_descriptor,	/* Type to decode */
	void **struct_ptr,	/* Pointer to a target structure's pointer */
	const void *buffer,	/* Data to be decoded */
	size_t size,		/* Size of data buffer */
	int skip_bits,		/* Number of unused leading bits, 0..7 */
	int unused_bits		/* Number of unused tailing bits, 0..7 */
	);


/*
 * Type of the type-specific PER decoder function.
 */
typedef asn_dec_rval_t (per_type_decoder_f)(asn_codec_ctx_t *opt_codec_ctx,
		struct asn_TYPE_descriptor_s *type_descriptor,
		asn_per_constraints_t *constraints,
		void **struct_ptr,
		asn_per_data_t *per_data
	);

#ifdef __cplusplus
}
#endif

#endif	/* _PER_DECODER_H_ */
