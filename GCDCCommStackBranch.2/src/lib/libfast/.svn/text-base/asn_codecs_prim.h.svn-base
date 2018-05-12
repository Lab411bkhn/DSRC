/*
 * $Id: asn_codecs_prim.h $
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
 * Copyright (c) 2004 Lev Walkin <vlm@lionet.info>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	ASN_CODECS_PRIM_H
#define	ASN_CODECS_PRIM_H

#include <asn_application.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ASN__PRIMITIVE_TYPE_s {
	uint8_t *buf;	/* Buffer with consecutive primitive encoding bytes */
	int size;	/* Size of the buffer */
} ASN__PRIMITIVE_TYPE_t;	/* Do not use this type directly! */

asn_struct_free_f __LIBFAST__ASN__PRIMITIVE_TYPE_free;
ber_type_decoder_f __LIBFAST__ber_decode_primitive;
der_type_encoder_f __LIBFAST__der_encode_primitive;

/*
 * A callback specification for the __LIBFAST__xer_decode_primitive() function below.
 */
enum xer_pbd_rval {
	XPBD_SYSTEM_FAILURE,	/* System failure (memory shortage, etc) */
	XPBD_DECODER_LIMIT,	/* Hit some decoder limitation or deficiency */
	XPBD_BROKEN_ENCODING,	/* Encoding of a primitive body is broken */
	XPBD_NOT_BODY_IGNORE,	/* Not a body format, but safe to ignore */
	XPBD_BODY_CONSUMED	/* Body is recognized and consumed */
};
typedef enum xer_pbd_rval (xer_primitive_body_decoder_f)
	(asn_TYPE_descriptor_t *td, void *struct_ptr,
		const void *chunk_buf, size_t chunk_size);

/*
 * Specific function to decode simple primitive types.
 * Also see __LIBFAST__xer_decode_general() in xer_decoder.h
 */
asn_dec_rval_t __LIBFAST__xer_decode_primitive(asn_codec_ctx_t *opt_codec_ctx,
	asn_TYPE_descriptor_t *type_descriptor,
	void **struct_ptr, size_t struct_size,
	const char *opt_mname,
	const void *buf_ptr, size_t size,
	xer_primitive_body_decoder_f *prim_body_decoder
);

#ifdef __cplusplus
}
#endif

#endif	/* ASN_CODECS_PRIM_H */
