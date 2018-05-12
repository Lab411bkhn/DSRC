/*
 * $Id: NativeInteger.h $
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
/*
 * This type differs from the standard INTEGER in that it is modelled using
 * the fixed machine type (long, int, short), so it can hold only values of
 * limited length. There is no type (i.e., NativeInteger_t, any integer type
 * will do).
 * This type may be used when integer range is limited by subtype constraints.
 */
#ifndef	_NativeInteger_H_
#define	_NativeInteger_H_

#include <asn_application.h>
#include <INTEGER.h>

#ifdef __cplusplus
extern "C" {
#endif

extern asn_TYPE_descriptor_t asn_DEF_NativeInteger;

asn_struct_free_f  __LIBFAST__NativeInteger_free;
asn_struct_print_f __LIBFAST__NativeInteger_print;
ber_type_decoder_f __LIBFAST__NativeInteger_decode_ber;
der_type_encoder_f __LIBFAST__NativeInteger_encode_der;
xer_type_decoder_f __LIBFAST__NativeInteger_decode_xer;
xer_type_encoder_f __LIBFAST__NativeInteger_encode_xer;
per_type_decoder_f __LIBFAST__NativeInteger_decode_uper;
per_type_encoder_f __LIBFAST__NativeInteger_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _NativeInteger_H_ */
