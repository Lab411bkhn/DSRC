/*
 * $Id: constr_SEQUENCE.h $
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
#ifndef	_CONSTR_SEQUENCE_H_
#define	_CONSTR_SEQUENCE_H_

#include <asn_application.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct asn_SEQUENCE_specifics_s {
	/*
	 * Target structure description.
	 */
	int struct_size;	/* Size of the target structure. */
	int ctx_offset;		/* Offset of the asn_struct_ctx_t member */

	/*
	 * Tags to members mapping table (sorted).
	 */
	asn_TYPE_tag2member_t *tag2el;
	int tag2el_count;

	/*
	 * Optional members of the extensions root (roms) or additions (aoms).
	 * Meaningful for PER.
	 */
	int *oms;		/* Optional MemberS */
	int  roms_count;	/* Root optional members count */
	int  aoms_count;	/* Additions optional members count */

	/*
	 * Description of an extensions group.
	 */
	int ext_after;		/* Extensions start after this member */
	int ext_before;		/* Extensions stop before this member */
} asn_SEQUENCE_specifics_t;


/*
 * A set specialized functions dealing with the SEQUENCE type.
 */
asn_struct_free_f __LIBFAST__SEQUENCE_free;
asn_struct_print_f __LIBFAST__SEQUENCE_print;
asn_constr_check_f __LIBFAST__SEQUENCE_constraint;
ber_type_decoder_f __LIBFAST__SEQUENCE_decode_ber;
der_type_encoder_f __LIBFAST__SEQUENCE_encode_der;
xer_type_decoder_f __LIBFAST__SEQUENCE_decode_xer;
xer_type_encoder_f __LIBFAST__SEQUENCE_encode_xer;
per_type_decoder_f __LIBFAST__SEQUENCE_decode_uper;
per_type_encoder_f __LIBFAST__SEQUENCE_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _CONSTR_SEQUENCE_H_ */
