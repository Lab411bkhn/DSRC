/*
 * $Id: constr_SET_OF.h $
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
#ifndef	_CONSTR_SET_OF_H_
#define	_CONSTR_SET_OF_H_

#include <asn_application.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct asn_SET_OF_specifics_s {
	/*
	 * Target structure description.
	 */
	int struct_size;	/* Size of the target structure. */
	int ctx_offset;		/* Offset of the asn_struct_ctx_t member */

	/* XER-specific stuff */
	int as_XMLValueList;	/* The member type must be encoded like this */
} asn_SET_OF_specifics_t;

/*
 * A set specialized functions dealing with the SET OF type.
 */
asn_struct_free_f __LIBFAST__SET_OF_free;
asn_struct_print_f __LIBFAST__SET_OF_print;
asn_constr_check_f __LIBFAST__SET_OF_constraint;
ber_type_decoder_f __LIBFAST__SET_OF_decode_ber;
der_type_encoder_f __LIBFAST__SET_OF_encode_der;
xer_type_decoder_f __LIBFAST__SET_OF_decode_xer;
xer_type_encoder_f __LIBFAST__SET_OF_encode_xer;
per_type_decoder_f __LIBFAST__SET_OF_decode_uper;
per_type_encoder_f SET_OF_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _CONSTR_SET_OF_H_ */
