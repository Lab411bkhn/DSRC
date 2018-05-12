/*
 * $Id: der_encoder.h $
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
#ifndef	_DER_ENCODER_H_
#define	_DER_ENCODER_H_

#include <asn_application.h>

#ifdef __cplusplus
extern "C" {
#endif

struct asn_TYPE_descriptor_s;	/* Forward declaration */

/*
 * The DER encoder of any type. May be invoked by the application.
 * The __LIBFAST__ber_decode() function (ber_decoder.h) is an opposite of __LIBFAST__der_encode().
 */
asn_enc_rval_t __LIBFAST__der_encode(struct asn_TYPE_descriptor_s *type_descriptor,
		void *struct_ptr,	/* Structure to be encoded */
		asn_app_consume_bytes_f *consume_bytes_cb,
		void *app_key		/* Arbitrary callback argument */
	);

/* A variant of __LIBFAST__der_encode() which encodes data into the pre-allocated buffer */
asn_enc_rval_t __LIBFAST__der_encode_to_buffer(
		struct asn_TYPE_descriptor_s *type_descriptor,
		void *struct_ptr,	/* Structure to be encoded */
		void *buffer,		/* Pre-allocated buffer */
		size_t buffer_size	/* Initial buffer size (maximum) */
	);

/*
 * Type of the generic DER encoder.
 */
typedef asn_enc_rval_t (der_type_encoder_f)(
		struct asn_TYPE_descriptor_s *type_descriptor,
		void *struct_ptr,	/* Structure to be encoded */
		int tag_mode,		/* {-1,0,1}: IMPLICIT, no, EXPLICIT */
		ber_tlv_tag_t tag,
		asn_app_consume_bytes_f *consume_bytes_cb,	/* Callback */
		void *app_key		/* Arbitrary callback argument */
	);


/*******************************
 * INTERNALLY USEFUL FUNCTIONS *
 *******************************/

/*
 * Write out leading TL[v] sequence according to the type definition.
 */
ssize_t __LIBFAST__der_write_tags(
		struct asn_TYPE_descriptor_s *type_descriptor,
		size_t struct_length,
		int tag_mode,		/* {-1,0,1}: IMPLICIT, no, EXPLICIT */
		int last_tag_form,	/* {0,!0}: prim, constructed */
		ber_tlv_tag_t tag,
		asn_app_consume_bytes_f *consume_bytes_cb,
		void *app_key
	);

#ifdef __cplusplus
}
#endif

#endif	/* _DER_ENCODER_H_ */
