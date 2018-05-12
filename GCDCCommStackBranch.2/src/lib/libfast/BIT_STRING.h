/*
 * $Id: BIT_STRING.h $
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
#ifndef	_BIT_STRING_H_
#define	_BIT_STRING_H_

#include <OCTET_STRING.h>	/* Some help from OCTET STRING */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct BIT_STRING_s {
	uint8_t *buf;	/* BIT STRING body */
	int size;	/* Size of the above buffer */

	int bits_unused;/* Unused trailing bits in the last octet (0..7) */

	asn_struct_ctx_t _asn_ctx;	/* Parsing across buffer boundaries */
} BIT_STRING_t;

extern asn_TYPE_descriptor_t asn_DEF_BIT_STRING;

asn_struct_print_f __LIBFAST__BIT_STRING_print;	/* Human-readable output */
asn_constr_check_f __LIBFAST__BIT_STRING_constraint;
xer_type_encoder_f __LIBFAST__BIT_STRING_encode_xer;

#ifdef __cplusplus
}
#endif

#endif	/* _BIT_STRING_H_ */
