/*
 * $Id: asn_SEQUENCE_OF.h $
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
#ifndef	ASN_SEQUENCE_OF_H
#define	ASN_SEQUENCE_OF_H

#include <asn_SET_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * SEQUENCE OF is the same as SET OF with a tiny difference:
 * the delete operation preserves the initial order of elements
 * and thus MAY operate in non-constant time.
 */
#define	A_SEQUENCE_OF(type)	A_SET_OF(type)

#define	ASN_SEQUENCE_ADD(headptr, ptr)		\
	asn_sequence_add((headptr), (ptr))

/***********************************************
 * Implementation of the SEQUENCE OF structure.
 */

#define	asn_sequence_add	__LIBFAST__asn_set_add
#define	asn_sequence_empty	__LIBFAST__asn_set_empty

/*
 * Delete the element from the set by its number (base 0).
 * This is NOT a constant-time operation.
 * The order of elements is preserved.
 * If _do_free is given AND the (*free) is initialized, the element
 * will be freed using the custom (*free) function as well.
 */
void __LIBFAST__asn_sequence_del(void *asn_sequence_of_x, int number, int _do_free);

/*
 * Cope with different conversions requirements to/from void in C and C++.
 * This is mostly useful for support library.
 */
typedef A_SEQUENCE_OF(void) asn_anonymous_sequence_;
#define _A_SEQUENCE_FROM_VOID(ptr)	((asn_anonymous_sequence_ *)(ptr))
#define _A_CSEQUENCE_FROM_VOID(ptr) 	((const asn_anonymous_sequence_ *)(ptr))

#ifdef __cplusplus
}
#endif

#endif	/* ASN_SEQUENCE_OF_H */
