/*
 * $Id: INTEGER.h $
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
 * Copyright (c) 2003, 2005 Lev Walkin <vlm@lionet.info>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_INTEGER_H_
#define	_INTEGER_H_

#include <asn_application.h>
#include <asn_codecs_prim.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef ASN__PRIMITIVE_TYPE_t INTEGER_t;

extern asn_TYPE_descriptor_t asn_DEF_INTEGER;

/* Map with <tag> to integer value association */
typedef struct asn_INTEGER_enum_map_s {
	long		 nat_value;	/* associated native integer value */
	size_t		 enum_len;	/* strlen("tag") */
	const char	*enum_name;	/* "tag" */
} asn_INTEGER_enum_map_t;

/* This type describes an enumeration for INTEGER and ENUMERATED types */
typedef struct asn_INTEGER_specifics_s {
	asn_INTEGER_enum_map_t *value2enum;	/* N -> "tag"; sorted by N */
	unsigned int *enum2value;		/* "tag" => N; sorted by tag */
	int map_count;				/* Elements in either map */
	int extension;				/* This map is extensible */
	int strict_enumeration;			/* Enumeration set is fixed */
	int field_width;			/* Size of native integer */
	int field_unsigned;			/* Signed=0, unsigned=1 */
} asn_INTEGER_specifics_t;

asn_struct_print_f __LIBFAST__INTEGER_print;
ber_type_decoder_f INTEGER_decode_ber;
der_type_encoder_f __LIBFAST__INTEGER_encode_der;
xer_type_decoder_f __LIBFAST__INTEGER_decode_xer;
xer_type_encoder_f __LIBFAST__INTEGER_encode_xer;
per_type_decoder_f __LIBFAST__INTEGER_decode_uper;
per_type_encoder_f __LIBFAST__INTEGER_encode_uper;

/***********************************
 * Some handy conversion routines. *
 ***********************************/

/*
 * Returns 0 if it was possible to convert, -1 otherwise.
 * -1/EINVAL: Mandatory argument missing
 * -1/ERANGE: Value encoded is out of range for long representation
 * -1/ENOMEM: Memory allocation failed (in __LIBFAST__asn_long2INTEGER()).
 */
int __LIBFAST__asn_INTEGER2long(const INTEGER_t *i, long *l);
int __LIBFAST__asn_INTEGER2ulong(const INTEGER_t *i, unsigned long *l);
int __LIBFAST__asn_long2INTEGER(INTEGER_t *i, long l);
int __LIBFAST__asn_ulong2INTEGER(INTEGER_t *i, unsigned long l);

/*
 * Convert the integer value into the corresponding enumeration map entry.
 */
const asn_INTEGER_enum_map_t *__LIBFAST__INTEGER_map_value2enum(asn_INTEGER_specifics_t *specs, long value);

#ifdef __cplusplus
}
#endif

#endif	/* _INTEGER_H_ */
