/*
 * $Id: xer_encoder.h $
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
#ifndef	_XER_ENCODER_H_
#define	_XER_ENCODER_H_

#include <asn_application.h>

#ifdef __cplusplus
extern "C" {
#endif

struct asn_TYPE_descriptor_s;	/* Forward declaration */

/* Flags used by the __LIBFAST__xer_encode() and (*xer_type_encoder_f), defined below */
enum xer_encoder_flags_e {
	/* Mode of encoding */
	XER_F_BASIC	= 0x01,	/* BASIC-XER (pretty-printing) */
	XER_F_CANONICAL	= 0x02	/* Canonical XER (strict rules) */
};

/*
 * The XER encoder of any type. May be invoked by the application.
 */
asn_enc_rval_t __LIBFAST__xer_encode(struct asn_TYPE_descriptor_s *type_descriptor,
		void *struct_ptr,	/* Structure to be encoded */
		enum xer_encoder_flags_e xer_flags,
		asn_app_consume_bytes_f *consume_bytes_cb,
		void *app_key		/* Arbitrary callback argument */
	);

/*
 * The variant of the above function which dumps the BASIC-XER (XER_F_BASIC)
 * output into the chosen file pointer.
 * RETURN VALUES:
 * 	 0: The structure is printed.
 * 	-1: Problem printing the structure.
 * WARNING: No sensible errno value is returned.
 */
int __LIBFAST__xer_fprint(FILE *stream, struct asn_TYPE_descriptor_s *td, void *sptr);

/*
 * Type of the generic XER encoder.
 */
typedef asn_enc_rval_t (xer_type_encoder_f)(
		struct asn_TYPE_descriptor_s *type_descriptor,
		void *struct_ptr,	/* Structure to be encoded */
		int ilevel,		/* Level of indentation */
		enum xer_encoder_flags_e xer_flags,
		asn_app_consume_bytes_f *consume_bytes_cb,	/* Callback */
		void *app_key		/* Arbitrary callback argument */
	);

#ifdef __cplusplus
}
#endif

#endif	/* _XER_ENCODER_H_ */
