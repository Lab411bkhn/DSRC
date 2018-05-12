/*
 * $Id: ber_decoder.h $
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
#ifndef	_BER_DECODER_H_
#define	_BER_DECODER_H_

#include <asn_application.h>

#ifdef __cplusplus
extern "C" {
#endif

struct asn_TYPE_descriptor_s;	/* Forward declaration */
struct asn_codec_ctx_s;		/* Forward declaration */

/*
 * The BER decoder of any type.
 * This function may be invoked directly from the application.
 * The __LIBFAST__der_encode() function (der_encoder.h) is an opposite to __LIBFAST__ber_decode().
 */
asn_dec_rval_t __LIBFAST__ber_decode(struct asn_codec_ctx_s *opt_codec_ctx,
	struct asn_TYPE_descriptor_s *type_descriptor,
	void **struct_ptr,	/* Pointer to a target structure's pointer */
	const void *buffer,	/* Data to be decoded */
	size_t size		/* Size of that buffer */
	);

/*
 * Type of generic function which decodes the byte stream into the structure.
 */
typedef asn_dec_rval_t (ber_type_decoder_f)(
		struct asn_codec_ctx_s *opt_codec_ctx,
		struct asn_TYPE_descriptor_s *type_descriptor,
		void **struct_ptr, const void *buf_ptr, size_t size,
		int tag_mode);

/*******************************
 * INTERNALLY USEFUL FUNCTIONS *
 *******************************/

/*
 * Check that all tags correspond to the type definition (as given in head).
 * On return, last_length would contain either a non-negative length of the
 * value part of the last TLV, or the negative number of expected
 * "end of content" sequences. The number may only be negative if the
 * head->last_tag_form is non-zero.
 */
asn_dec_rval_t __LIBFAST__ber_check_tags(
		struct asn_codec_ctx_s *opt_codec_ctx,	/* codec options */
		struct asn_TYPE_descriptor_s *type_descriptor,
		asn_struct_ctx_t *opt_ctx,	/* saved decoding context */
		const void *ptr, size_t size,
		int tag_mode,		/* {-1,0,1}: IMPLICIT, no, EXPLICIT */
		int last_tag_form,	/* {-1,0:1}: any, primitive, constr */
		ber_tlv_len_t *last_length,
		int *opt_tlv_form	/* optional tag form */
	);

#ifdef __cplusplus
}
#endif

#endif	/* _BER_DECODER_H_ */
